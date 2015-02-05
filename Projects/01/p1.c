#include <stdio.h>

/***
Author: Dylan Zingler
Date: 02-02-2015
Purpose: TCP client side socket

***/

/* 
called by using
./p1 argument1 argument2

 */

int main (int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }

    int i=0;
    /*printf("\ncmdline args count=%s", argc);*/

    /* First argument is executable name only */ 
    printf("\nexe name=%s", argv[0]);

    for (i=1; i< argc; i++) {
    printf("\narg%d=%s", i, argv[i]);

    }

    printf("\n");
    return 0;




}
