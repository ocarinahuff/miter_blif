/* 
 * File:   main.c
 * Author: ocari_000
 *
 * Created on September 27, 2014, 8:38 PM
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

// store the input variable.
/*
struct NETS {
    int inputcount;
    int outputcount;
    char **inputs;
    char **outputs;
};

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
    char buffer[BUF_SIZE];
                
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
            char *cptr;
            /*
             * state = 0: non-name line.
             * state = 1: name line.
             * state = 2: end line.
             */
            int state = 0;
            for(ptr = lines1->next->next->next; ptr != NULL; ptr = ptr->next) {
                strcpy(buffer, ptr->line);
                for(cptr = strtok(buffer, " \t\r\n\v\f"); cptr != NULL; cptr = strtok(NULL, " \t\r\n\v\f")) {
                    if(!strcmp(cptr, ".names")) {
                        fprintf(file3, ".names");
                        state = 1;
                        continue;
                    }
                    if(!strcmp(cptr, ".end")) {
                        state = 2;
                        break;
                    }
                    if(state == 1) {
                        fprintf(file3, " %s_1", cptr);
                    }
                }
                if(state == 0) {
                    fprintf(file3, "%s", ptr->line);
                } else if(state == 2) {
                    state = 0;
                } else {
                    state = 0;
                    fprintf(file3, "\n");
                }
            }
            for(ptr = lines2->next->next->next; ptr != NULL; ptr = ptr->next) {
                strcpy(buffer, ptr->line);
                for(cptr = strtok(buffer, " \t\r\n\v\f"); cptr != NULL; cptr = strtok(NULL, " \t\r\n\v\f")) {
                    if(!strcmp(cptr, ".names")) {
                        fprintf(file3, ".names");
                        state = 1;
                        continue;
                    }
                    if(!strcmp(cptr, ".end")) {
                        state = 2;
                        break;
                    }
                    if(state == 1) {
                        fprintf(file3, " %s_2", cptr);
                    }
                }
                if(state == 0) {
                    fprintf(file3, "%s", ptr->line);
                } else if(state == 2) {
                    state = 0;
                } else {
                    state = 0;
                    fprintf(file3, "\n");
                }
            }
            // build miter circuit.
            
            // close blif with '.end'.
            fprintf(file3, ".end\n");
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

