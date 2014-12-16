#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miter.h"

#define MAX_NETS 100

char **getnets(char *line) {
    char buffer[BUF_SIZE];
    strcpy(buffer, line);
    char *cptr;
    char **nets;
    char netbuffer[MAX_NETS][BUF_SIZE];
    int i = 0;
    for(cptr = strtok(buffer, " \t\r\n"); 
            cptr != NULL; cptr = strtok(NULL, " \t\r\n")) {
        strcpy(netbuffer[i++],cptr);
    }
    // store count of nets, plus one, at beginning of 
    // 2D pointer array.
    nets = (char **)malloc(i*sizeof(char *));
    char netcount[BUF_SIZE];
    sprintf(netcount, "%d", i);
    nets[0] = (char *)malloc((strlen(netcount)+1)*sizeof(char));
    strcpy(nets[0], netcount);
    int j;
    for(j = 1; j < i; j++) {
        nets[j] = (char *)malloc((strlen(netbuffer[j])+1)*sizeof(char));
        strcpy(nets[j], netbuffer[j]);
    }
    return nets;
}

void freenets(char **nets) {
    int i, netcount = atoi(nets[0]);
    for(i = 0; i < netcount; i++) {
        free(nets[i]);
    }
    free(nets);
}

int checknets(char *line, char **nets) {
    int i, result = 0;
    for(i = 1; i < atoi(nets[0]); i++) {
        if(result = !!strstr(line, nets[i]))
            break;
    }
    return result;
}
