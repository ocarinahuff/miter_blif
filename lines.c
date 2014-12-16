/*
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miter.h"

/**
 * Return a linked list of lines from a file
 * @param file
 * @return 
 */
struct LINES *fgetlines(FILE *file) {
    char buffer[BUF_SIZE];
    struct LINES *lines = (struct LINES *)malloc(sizeof(struct LINES));
    lines->next = NULL;
    struct LINES *ptr = lines;
    char *line = fgets(buffer, sizeof(buffer), file);
    while(line != NULL) {
        ptr->line = (char *)malloc((strlen(buffer)+1)*sizeof(char));
        strcpy(ptr->line, buffer);
        if((line = fgets(buffer, sizeof(buffer), file)) != NULL) {
            ptr = ptr->next = (struct LINES *)malloc(sizeof(struct LINES));
            ptr->next = NULL;
        }
    }
    return lines;
}

/**
 * 
 * @param lines
 */
void freelines(struct LINES *lines) {
    struct LINES *head, *ptr;
    head = ptr = lines;
    while(ptr != NULL) {
        ptr = ptr->next;
        free(head->line);
        free(head);
        head = ptr;
    }
}

void processlines(FILE *file, struct LINES *lines, char *label, char **inputs) {
    struct LINES *ptr;
    char *cptr;
    char buffer[BUF_SIZE];
    enum states {NON_NAME, NAME, END};
    int state = NON_NAME;
    for(ptr = lines->next->next->next; ptr != NULL; ptr = ptr->next) {
        strcpy(buffer, ptr->line);
        for(cptr = strtok(buffer, " \t\r\n"); cptr != NULL; cptr = strtok(NULL, " \t\r\n")) {
            if(!strcmp(cptr, ".names")) {
                fprintf(file, ".names");
                state = NAME;
                continue;
            }
            if(!strcmp(cptr, ".end")) {
                state = END;
                break;
            }
            if(state == NAME) {
                fprintf(file, " %s%s", cptr, checknets(cptr, inputs) ? "" : label);
            }
        }
        if(state == NON_NAME) {
            fprintf(file, "%s", ptr->line);
        } else if(state == END) {
            state = NON_NAME;
        } else {
            state = NON_NAME;
            fprintf(file, "\n");
        }
    }
}