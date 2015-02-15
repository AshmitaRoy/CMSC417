#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/time.h>

/*  Global constants  */
#define MAX_LINE           (2000)
#define CHUNK_SIZE         (32768)

/***
Author: Dylan Zingler
Date: 02-02-2015
Purpose: TCP client side socket

Credit to Paul Griffiths, 1999
***/

/* 
called by using
./p1 <host> <port>
Then a message must be piped to the function to echo it

 */

int receive_basic(int s)
{
    int size_recv , total_size= 0;
    /*int CHUNK_SIZE = 512;*/
    char chunk[CHUNK_SIZE]; 
     
    //loop
    while(1)
    {
        memset(chunk ,0 , CHUNK_SIZE);  //clear the variable
        if((size_recv =  recv(s , chunk , CHUNK_SIZE , 0) ) <= 0)
        {
            break;
        }
        else
        {
            total_size += size_recv;
            printf("%s" , chunk);
        }
    }
     
    return total_size;
}

/*  Write a line to a socket  */
ssize_t Writeline(int sockd, const void *vptr, size_t n) {
    size_t      nleft;
    ssize_t     nwritten;
    const char *buffer;

    buffer = vptr;
    nleft  = n;

    while ( nleft > 0 ) {
	if ( (nwritten = write(sockd, buffer, nleft)) <= 0 ) {
	    if ( errno == EINTR )
		nwritten = 0;
	    else
		return -1;
	}
	nleft  -= nwritten;
	buffer += nwritten;
    }

    return n;
}

int main (int argc, char *argv[]) {

    int       conn_s;                /*  connection socket         */
    short int port;                  /*  port number               */
    struct    sockaddr_in servaddr;  /*  socket address structure  */
    char      buffer[MAX_LINE];      /*  character buffer          */
    char     *szAddress;             /*  Holds remote IP address   */
    char     *szPort;                /*  Holds remote port         */
    char     *endptr;                /*  for strtol()              */           

    /* Argument count must be 3 */
    if (argc != 3) {
        printf("usage %s hostname port\n", argv[0]);
        exit(0);
    }
    
    /* Setting command line args */
    szAddress = argv[1];
    szPort = argv[2];
    
    /* Setting the remote port */
    port = strtol(szPort, &endptr, 0);
    if (*endptr){
        printf("ECHO CLIENT: Invalid port. Exiting.\n");
        exit(EXIT_FAILURE);
    }
    
    /* Create the Listening Socket */
    if ((conn_s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf( "ECHO CLIENT: Error creating listening socket.\n");
        exit(EXIT_FAILURE);
    }
    
    /* Set all bytes in socket address structure to zero, and fill in the relevant data */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    
    /* Set the remote IP address */
    if (inet_aton(szAddress, &servaddr.sin_addr) <= 0){
        printf("ECHO CLIENT: Invalid Remote IP Address.\n");
        exit(EXIT_FAILURE);
    }
    
    /* connect() to the remote echo server */
    if (connect(conn_s, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
        printf("ECHO CLIENT: Error Calling connect.\n");
        exit(EXIT_FAILURE);
    }    
    
    /* Get string to echo from user */   
    fgets(buffer, MAX_LINE, stdin);
    
    /* Send string to echo server, and retrieve response */
    Writeline(conn_s, buffer, strlen(buffer));
    receive_basic(conn_s);

    /* Shutting down socket */
    if (shutdown(conn_s, 2) == 0){
        /*printf("shutdown successful");*/
    } else{
/*        printf("Shutdown unsuccessful");*/
    }
    
    return EXIT_SUCCESS;
}

