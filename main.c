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
    int wordcount;
    char **words;
};

struct NETS {
    int inputcount;
    int outputcount;
    char **inputs;
    char **outputs;
};

int swordcount(char *line) {
    char buffer[255];
    strcpy(buffer,line);
    char *ptr = strtok(buffer, " ");
    int count = 0;
    while(ptr != NULL) {
        count++;
        ptr = strtok(NULL, " ");
    }
    return count;
}

/*
 * Return the number of lines in a file.
 */
int fcountlines(FILE *file) {
    char buffer[BUF_SIZE];
    int count = 0;
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }
    return count;
}

/*
 * Return a 2D char array of lines from a file
 */
struct LINES *fgetlines(FILE *file, int fsize) {
    char buffer[BUF_SIZE];
    char *ptr;
    int i, j;
    struct LINES *lines = (struct LINES *)malloc(fsize*sizeof(struct LINES));
    for(i = 0; i < fsize; i++) {
        fgets(buffer, sizeof(buffer), file);
        lines[i].wordcount = swordcount(buffer);
        lines[i].words = (char **)malloc((lines[i].wordcount)*sizeof(char *));
        ptr = strtok(buffer, " ");
        for(j = 0; ptr != NULL; j++) {
            lines[i].words[j] = (char *)malloc((strlen(ptr)+1)*sizeof(char));
            strcpy(lines[i].words[j],ptr);
            ptr = strtok(NULL, " ");
        }
    }
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
    FILE *file1, *file2;
    int M, N, i, j;
    // char buffer[BUF_SIZE];
                
    struct LINES *lines1;
    struct LINES *lines2;
    // display an error if an incorrect number of arguments are entered.
    if(argc != 3) {
        printf("Please type in both filenames.\n");
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
            
            // print test output to stdout.
            printf("\n");
            for(i = 0; i < M; i++) {
                printf("%s", lines1[i].words[0]);
                for(j = 1; j < lines1[i].wordcount; j++) {
                    printf(" %s", lines1[i].words[j]);
                }
            }
            printf("\n");
            for(i = 0; i < N; i++) {
                printf("%s", lines2[i].words[0]);
                for(j = 1; j < lines2[i].wordcount; j++) {
                    printf(" %s", lines2[i].words[j]);
                }
            }
            printf("\n");
            
            // count number of inputs
            struct NETS net1;
            for(i = 0; i < M; i++) {
                if(!strcmp(lines1[i].words[0],".inputs")) {
                    net1.inputcount = lines1[i].wordcount - 1;
                    printf("Number of inputs in function1: %d\n", net1.inputcount);
                    net1.inputs = (char **)malloc((net1.inputcount)*sizeof(char *));
                    for(j = 1; j < lines1[i].wordcount; j++) {
                        net1.inputs[j-1] = (char *)malloc((strlen(lines1[i].words[j])+1)*sizeof(char));
                        strcpy(net1.inputs[j-1],lines1[i].words[j]);
                    }
                }
                if(!strcmp(lines1[i].words[0],".outputs")) {
                    net1.outputcount = lines1[i].wordcount - 1;
                    printf("Number of outputs in function1: %d\n", net1.outputcount);
                    net1.outputs = (char **)malloc((net1.outputcount)*sizeof(char *));
                    for(j = 1; j < lines1[i].wordcount; j++) {
                        net1.outputs[j-1] = (char *)malloc((strlen(lines1[i].words[j])+1)*sizeof(char));
                        strcpy(net1.outputs[j-1], lines1[i].words[j]);
                    }
                }
            }
            struct NETS net2;
            for(i = 0; i < N; i++) {
                if(!strcmp(lines2[i].words[0],".inputs")) {
                    net2.inputcount = lines2[i].wordcount - 1;
                    printf("Number of inputs in function2: %d\n", net2.inputcount);
                    net2.inputs = (char **)malloc((net2.inputcount)*sizeof(char *));
                    for(j = 1; j < lines2[i].wordcount; j++) 
                        net2.inputs[j-1] = (char *)malloc((strlen(lines2[i].words[j])+1)*sizeof(char));                        
                        strcpy(net2.inputs[j-1], lines2[i].words[j]);
                    }
                }
                if(!strcmp(lines2[i].words[0],".outputs")) {
                    net2.outputcount = lines2[i].wordcount - 1;
                    printf("Number of outputs in function2: %d\n", net2.outputcount);
                    net2.outputs = (char **)malloc((net2.outputcount)*sizeof(char *));
                    for(j = 1; j < lines2[i].wordcount; j++) {
                        net2.outputs[j-1] = (char *)malloc((strlen(lines2[i].words[j])+1)*sizeof(char));
                        strcpy(net2.outputs[j-1], lines2[i].words[j]);
                    }
                }
            }
            
            // count number of intermediate nets
            
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

