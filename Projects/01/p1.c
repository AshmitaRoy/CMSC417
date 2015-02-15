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
#define CHUNK_SIZE         (8192)

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

/*  Function declarations  */
ssize_t Readline(int fd, void *vptr, size_t maxlen);
ssize_t Writeline(int sockd, const void *vptr, size_t n);
ssize_t ReadSock(int sockd, void *vptr);

/*  Read a line from a socket  */
ssize_t Readline(int sockd, void *vptr, size_t maxlen) {
    ssize_t n, rc;
    char    c, *buffer;

    buffer = vptr;

    for ( n = 1; n < maxlen; n++ ) {
	    if ( (rc = read(sockd, &c, 1)) == 1 ) {
	        *buffer++ = c;
    	    if ( c == EOF )
	    	    break;
	    } else if ( rc == 0 ) {
	        if ( n == 1 )
	    	    return 0;
	        else
	    	    break;
	    } else {
	        if ( errno == EINTR )
	    	    continue;
	        return -1;
	    }
    }

    *buffer = 0;
    return n;
}


ssize_t ReadSock(int sockd, void *vptr) {
    ssize_t n, rc;
    char    c, *buffer;
    
    buffer = vptr;
    n = 1;        
    
    /* Good loop */
    while (1){
        rc = read(sockd, &c, 1);
        /*printf("%s", rc);        */
        
        /* Read Value was zero, server done sending message */	    	    
        if (rc == 0){
            if ( n == 1 ){
                *buffer = 0;            
	    	    return 0;
	        } else
	    	    break;
        } else if (rc != 1) {
	        /*if ( errno == EINTR )
	    	    continue;*/
	    	*buffer = 0;
	        return -1;
	        
        /* Read Value was Good   */	    
	    } else if (rc == 1) {   
            *buffer++ = c;
            printf("%s" , &c);                      
        }
	    n++;          
    }        
    
    *buffer = 0;
    return n;
}

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


int recv_timeout(int s , int timeout)
{
    int size_recv , total_size= 0;
    struct timeval begin , now;
    char chunk[CHUNK_SIZE];
    double timediff;
     
    //make socket non blocking
    fcntl(s, F_SETFL, O_NONBLOCK);
     
    //beginning time
    gettimeofday(&begin , NULL);
     
    while(1)
    {
        gettimeofday(&now , NULL);
         
        //time elapsed in seconds
        timediff = (now.tv_sec - begin.tv_sec) + 1e-6 * (now.tv_usec - begin.tv_usec);
         
        //if you got some data, then break after timeout
        if( total_size > 0 && timediff > timeout )
        {
            break;
        }
         
        //if you got no data at all, wait a little longer, twice the timeout
        else if( timediff > timeout*2)
        {
            break;
        }
         
        memset(chunk ,0 , CHUNK_SIZE);  //clear the variable
        if((size_recv =  recv(s , chunk , CHUNK_SIZE , 0) ) < 0)
        {
            //if nothing was received then we want to wait a little before trying again, 0.1 seconds
            usleep(100000);
        }
        else
        {
            total_size += size_recv;
            printf("%s" , chunk);
            //reset beginning time
            gettimeofday(&begin , NULL);
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
    
    int i=0;   

    /* Argument count must be 3 */
    if (argc != 3) {
        printf("usage %s hostname port\n", argv[0]);
        exit(0);
    }

    /* Printing command line args */

    /* First argument is executable name */ 
    printf("\nexe name=%s", argv[0]);
    for (i=1; i< argc; i++) {
       printf("\narg%d=%s", i, argv[i]);
    }
    printf("\n");
    
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
    
    /* Get string to ech from user */
    printf("Enter the String to Echo: ");
    fgets(buffer, MAX_LINE, stdin);
    
    /* Send string to echo server, and retrieve response */
    Writeline(conn_s, buffer, strlen(buffer));
/*    Readline(conn_s, buffer, MAX_LINE-1);*/
/*    ReadSock(conn_s, buffer);   */
/*    SockReader(conn_s, buffer);*/
    receive_basic(conn_s);
/*    recv_timeout(conn_s, 4);*/
    
    /* Output echoed String */
    printf("Echo Response: %s\n", buffer);
    
    /* Shutting down socket */
    if (shutdown(conn_s, 2) == 0){
        printf("shutdown successful");
    } else{
        printf("Shutdown unsuccessful");
        }
    
    return EXIT_SUCCESS;

}

