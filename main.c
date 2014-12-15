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
    int linecount;
    char **lines;
};

struct NETS {
    int inputcount;
    int outputcount;
    char **inputs;
    char **outputs;
};

/*
 * Return a 2D char array of lines from a file
 */
struct LINES *fgetlines(FILE *file) {
    char buffer[BUF_SIZE];
    int linecount;
    struct LINES *lines = (struct LINES *)malloc(sizeof(struct LINES));
    for(linecount = 0; fgets(buffer, sizeof(buffer), file) != NULL; linecount++) {
        lines->lines = (char **)malloc((strlen(buffer)+1)*sizeof(char *));
        strcpy(buffer,lines->lines);
    }
    lines->linecount = linecount;
    return lines;
}

void freelines(struct LINES *lines, int linecount) {
    int i, j;
    for(i = 0; i < linecount; i++) {
        for(j = 0; j < lines[i].wordcount; j++) {
            free(lines[i].words[j]);
        }
        free(lines[i].words);
    }
    free(lines);
}

void freenets(struct NETS nets) {
    int i;
    for(i = 0; i < nets.inputcount; i++)
        free(nets.inputs[i]);
    for(i = 0; i < nets.outputcount; i++)
        free(nets.outputs[i]);
    free(nets.inputs);
    free(nets.outputs);
}

/*
 * 
 */
int main(int argc, char** argv) {
    FILE *file1, *file2, *file3;
    int M, N, i, j;
    // char buffer[BUF_SIZE];
                
    struct LINES *lines1, *lines2;
    struct NETS net1, net2;
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
            // count the number of lines in the files
            M = fcountlines(file1);
            N = fcountlines(file2);
            
            // return pointers to beginning of files.
            fseek(file1,0,SEEK_SET);
            fseek(file2,0,SEEK_SET);
            
            // store lines from files in 2D char array, then close files.
            lines1 = fgetlines(file1, M);
            lines2 = fgetlines(file2, N);
            fclose(file1);
            fclose(file2);
            
            // write lines to file.
            file3 = fopen("miter.blif", "wt");
            fprintf(".model miter\n");
            
            fclose(file3);
                    
            // deallocate memory from lines1 & lines2
            freelines(lines1, M);
            freelines(lines2, N);
            
            // deallocate memory from net1 & net2
            freenets(net1);
            freenets(net2);
        }
    }
    return (EXIT_SUCCESS);
}

