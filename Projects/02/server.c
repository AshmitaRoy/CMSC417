/***
Project: 02 server.c
Author: Dylan Zingler
Date: 03-09-2015
Purpose: TCP client side socket
Usage:
***/

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <netdb.h>
#include "common.h"	/* for Given Variables from common file */

#define CHUNK_SIZE         (32768)

/**#define MAXPENDING 5 */

void HandleTCPClient(int clntSocket);   /* TCP client handling function */

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
        if((size_recv =  recv(s , chunk , CHUNK_SIZE , 0) ) <= 0){
            break;
        } else {
            total_size += size_recv;
            printf("%s" , chunk);
        }
    }
    return total_size;
}

int main(int argc, char *argv[])
{
    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
    unsigned short echoServPort;     /* Server port */
    unsigned int clntLen;            /* Length of client address data structure */

    /*struct hostent * hostname;*/
    /*char buffer[CHUNK_SIZE];*/
	

    /* Test for correct number of arguments */
    if (argc == 1)  /* No Port specified */
    {
        printf("Using Default Server Port %d\n", SERVER_PORT);       
	    echoServPort = SERVER_PORT;
        
    } else if (argc == 2){ /* Port specified */
        printf("custom port"  );    
        echoServPort = atoi(argv[1]);  /* First arg:  local port */
    } else {
        printf("errorr");
        exit(1);
    }    

    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        printf("socket() failed");
        exit(1);
	}      

    printf("SERVER UP AND Farting...");

    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(echoServPort);      /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0){
        printf("bind() failed");
        exit(1);
	}
            
    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0)   {
        printf("listen() failed");
        exit(1);
	}

    printf("SERVER UP AND RUNNING...");

    for (;;) /* Run forever */
    {
		int msg_size = 0;
        /* Set the size of the in-out parameter */
        clntLen = sizeof(echoClntAddr);

        /* Wait for a client to connect */
        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, 
                               &clntLen)) < 0){
            printf("accept() Failed");
            exit(1);
		}
        /* clntSock is connected to a client! */

        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

    	/*ssize_t numBytesRcvd = recv(clntSock, buffer, BUFSIZE, 0);*/
		msg_size = receive_basic(clntSock);
        printf("Message size is: %d", msg_size);

        


    }
    /* NOT REACHED */
}

