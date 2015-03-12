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
#include <errno.h>

#define CHUNK_SIZE         (255)

/**#define MAXPENDING 5 */

void HandleTCPClient(int clntSocket);   /* TCP client handling function */

/* receive_basic
credit given to Silver Moon
http://www.binarytides.com/receive-full-data-with-recv-socket-function-in-c/
*/
char *receive_basic(int s)
{
    int size_recv , total_size= 0;
    char *chunk = malloc(CHUNK_SIZE);      

    do 
    {
        memset(chunk ,0 , CHUNK_SIZE);  
        size_recv = 0;
        size_recv =  recv(s , chunk , CHUNK_SIZE , 0);

        if (size_recv <= 0) {
            break;
        }

        total_size  += size_recv;


        
        return chunk;

    }
    while (size_recv > 0);

    return "out of do while loop";

}

char* itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}

int gen_cookie(char * client_ip){  
    char **pch = &client_ip;
    char * val;
    int total = 0;
    int count = 0;
    while ( (val = strsep(pch, ".")) && count < 4){
        total = total + atoi(val);
        count = count + 1;
    }
    return (total * 13) % 1111;
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

int main(int argc, char *argv[])
{
    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Clent address */
    unsigned short echoServPort;     /* Server port */
    unsigned int clntLen;            /* Length of client address data structure */

    

    /*struct hostent * hostname;*/
    /*char buffer[CHUNK_SIZE];*/
	

    /* Test for correct number of arguments */
    if (argc == 1)  /* No Port specified */
    {             
	    echoServPort = SERVER_PORT;
        
    } else if (argc == 2){ /* Port specified */           
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

    for (;;) /* Run forever */
    {
		char *client_hello = malloc(CHUNK_SIZE);
        char *pch;
        int counter = 1;
        char *server_status;
        int cookie;
        char *cookie_str; 
        char *client_bye;
        char *server_bye = malloc(255);
        char *loginid = malloc(255);
        char *name = malloc(255);
        /* Set the size of the in-out parameter */
        clntLen = sizeof(echoClntAddr);

        /* Wait for a client to connect */
        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, 
                               &clntLen)) < 0){
            printf("accept() Failed");
            exit(1);
		}
        /* clntSock is connected to a client! 

        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr)); */

    	/*ssize_t numBytesRcvd = recv(clntSock, buffer, BUFSIZE, 0);*/


        /* Client HELLO */
	    client_hello = receive_basic(clntSock);
        printf("%s", client_hello);

        pch = strtok(client_hello, " ");        
        while (pch != NULL){                        
            
            if (counter == 1){
                if (strcmp(pch, MAGIC_STRING) != 0){
                    printf("%s, %s", pch, MAGIC_STRING);
                    printf("Magic Strings are not the same");
                    return 0;                    
                } else {
                    server_status = pch;
                }
            }

            if (counter == 2){
                if (strcmp(pch, "HELLO") != 0){
                    printf("Badd hello message from client");
                    return 0;
                }
            }    

            if (counter == 3){
                strcpy(loginid,pch);
            }

            if (counter == 4){
                int len = strlen(pch);
                pch[len-1] = '\0';
                strcpy(name,pch);

            }

            if (counter >= 4){
                break;
            }

            
            counter = counter + 1;
            
            pch = strtok (NULL, " ");
        }   


        cookie = gen_cookie(inet_ntoa(echoClntAddr.sin_addr));

        cookie_str = itoa(cookie, 10);

        server_status = strcat(strcat(server_status," STATUS "),cookie_str);

        server_status = strcat(strcat(strcat(strcat(server_status, " "),  inet_ntoa(echoClntAddr.sin_addr)), ":"), itoa(echoServPort, 10));

        Writeline(clntSock, server_status, strlen(server_status));

	    client_bye = receive_basic(clntSock);
        
        counter = 1;
        pch = strtok (client_bye, " ");        
        while (pch != NULL){
            if (counter == 1){
                if (strcmp(pch, MAGIC_STRING) != 0){
                    printf("%s, %s", pch, MAGIC_STRING);
                    printf("Magic Strings are not the same");
                    return 0;                    
                } else {
                    server_status = pch;
                }
            }

            if (counter == 2){
                if (strcmp(pch, "CLIENT_BYE") != 0){
                    printf("Badd bye message from client");
                    return 0;
                }
            }    
    
            if (counter == 3){
                if (atoi(pch) != cookie){
                    printf("%s, %d", pch, cookie);
                    printf("Client sent back a baddddd COOOKIE");
                    return 0;
                }
            }

            if (counter >=3){
                break;
            }

            
            counter = counter + 1;
            pch = strtok (NULL, " ");
        
        }        

        strcpy(server_bye, MAGIC_STRING);

        strcat(server_bye, " SERVER_BYE");            
   
        Writeline(clntSock, server_bye, strlen(server_bye));
     
        /* output -->  cookie loginid firstname ip:port */  
        printf("%s", client_hello);
        printf("%d %s from %s:%d", cookie, loginid, inet_ntoa(echoClntAddr.sin_addr), echoServPort);                   
        

    }
    /* NOT REACHED */
}

