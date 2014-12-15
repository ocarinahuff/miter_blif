/*
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lines.h"
#ifndef BUF_SIZE
#define BUF_SIZE 255
#endif
#ifndef MAX_STR_LEN
#define MAX_STR_LEN 255
#endif

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