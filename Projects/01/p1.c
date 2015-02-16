/***
Author: Dylan Zingler
Date: 02-02-2015
Purpose: TCP client side socket
Usage: $ ./p1 <host> <port>
Then enter a message to echo
Example: $ echo GET / | ./p1 www.google.com 80
***/

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
#include <netdb.h>
#include <netinet/in.h>

/*  Global constants  */
#define MAX_LINE           (2000)
#define CHUNK_SIZE         (32768)

/* receive_basic
credit given to Silver Moon
http://www.binarytides.com/receive-full-data-with-recv-socket-function-in-c/
*/
int receive_basic(int s)
{
    int size_recv , total_size= 0;
    /*int CHUNK_SIZE = 512;*/
    char chunk[CHUNK_SIZE]; 
     
    /*loop*/
    while(1)
    {
        memset(chunk ,0 , CHUNK_SIZE);  
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

/* 
credit given to Paul Griffiths 
http://www.paulgriffiths.net/program/c/echoclnt.php
Some of this code was taken from his echoclnt.c */
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

/* 
credit given to Paul Griffiths 
http://www.paulgriffiths.net/program/c/echoclnt.php
Some of this code was modeled off his echoclnt.c */
int main (int argc, char *argv[]) {

    int       conn_s;                /*  connection socket         */
    short int port;                  /*  port number               */
    struct    sockaddr_in servaddr, sa;  /*  socket address structure  */
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
    
    /* Checking if Address is Dotted Quad */
    if (inet_pton(AF_INET, szAddress, &(sa.sin_addr)) != 1){
    
        /* Following code block modeled from book 
        TCP/IP Sockets in C 
        (GetAddrInfo.c and PrintSocketAddr() function)
         */
        void *numericAddress;        
        char addrBuffer[INET6_ADDRSTRLEN];   
    
        struct addrinfo addrCriteria;
        memset(&addrCriteria, 0, sizeof(addrCriteria));
        addrCriteria.ai_family = AF_INET;
        addrCriteria.ai_socktype = SOCK_STREAM;
        addrCriteria.ai_protocol = IPPROTO_TCP;
        
        struct addrinfo *addrList;
        int rtnVal = getaddrinfo(szAddress, szPort, &addrCriteria, &addrList);
        
        if (rtnVal != 0){
            printf("getaddrinfo() did not work properly");
            exit(1);
        }
        
        for (struct addrinfo *addr = addrList; addr != NULL; addr = addr->ai_next){
            numericAddress = &((struct sockaddr_in *) addr->ai_addr)->sin_addr;
            
            if (inet_ntop(addr->ai_addr->sa_family, numericAddress, addrBuffer, sizeof(addrBuffer)) == NULL)
                printf("invalid address could not convert");
            else {
                /*printf("address is: %s", addrBuffer);*/
                szAddress = addrBuffer;
                break;                
            }
        }
    }
    
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
        /* printf("shutdown successful");*/
    } else{
        /* printf("Shutdown unsuccessful");*/
    }
    
    exit(0);
    return EXIT_SUCCESS;
}

