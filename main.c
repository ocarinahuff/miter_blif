/* 
 * File:   main.c
 * Author: ocari_000
 *
 * Created on September 27, 2014, 8:38 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 255
#define MAX_STR_LEN 255

struct LINES {
    char *line;
    struct LINES *next;
};

// store the input variable.
struct NETS {
    int inputcount;
    int outputcount;
    char **inputs;
    char **outputs;
};

/*
 * Return a linked list of lines from a file
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
/*
void freenets(struct NETS nets) {
    int i;
    for(i = 0; i < nets.inputcount; i++)
        free(nets.inputs[i]);
    for(i = 0; i < nets.outputcount; i++)
        free(nets.outputs[i]);
    free(nets.inputs);
    free(nets.outputs);
}*/

/*
 * 
 */
int main(int argc, char** argv) {
    FILE *file1, *file2, *file3;
    // char buffer[BUF_SIZE];
                
    struct LINES *lines1, *lines2;
    // display an error if an incorrect number of arguments are entered.
    if(argc != 3) {
        printf("USAGE: miter_blif.exe file1.blif file2.blif\n");
    }
    else {
        // open the files.
        file1 = fopen(argv[1], "rt");
        file2 = fopen(argv[2], "rt");
        // display an error if one or both of the files fail to open.
        if(file1 == NULL || file2 == NULL) {
            printf("The file(s) could not be opened.\n");
        }
        else {            
            // store lines from files in 2D char array, then close files.
            lines1 = fgetlines(file1);
            lines2 = fgetlines(file2);
            fclose(file1);
            fclose(file2);
            
            // write lines to file.
            file3 = fopen("miter.blif", "wt");
            fprintf(file3, ".model miter\n");
            fprintf(file3, lines1->next->line);
            struct LINES *ptr;
            for(ptr = lines1->next->next->next; ptr != NULL; ptr = ptr->next) {
                fprintf(file3, "%s", ptr->line);
            }
            for(ptr = lines2->next->next->next; ptr != NULL; ptr = ptr->next) {
                fprintf(file3, "%s", ptr->line);
            }
            fclose(file3);
                    
            // deallocate memory from lines1 & lines2
            freelines(lines1);
            freelines(lines2);
            
            // deallocate memory from net1 & net2
            //freenets(net1);
            //freenets(net2);
        }
    }
    return (EXIT_SUCCESS);
}

