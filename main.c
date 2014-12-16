/* 
 * File:   main.c
 * Author: ocari_000
 *
 * Created on September 27, 2014, 8:38 PM
 * The purpose of miter_blif is to take two blif files, and miter them 
 * together for the purpose of SAT checking.  A miter is a series of xor
 * gates and an or gate.  Each xor gate compares an output from the two
 * functions represented in the two blif files.  The or will return a 1 if
 * functions do not match, and 0 if the functions match.  A separate SAT solver
 * will be used to check if the miter.blif function returns a 1 or a 0.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miter.h"

int main(int argc, char** argv) {
    FILE *file1, *file2, *file3;
                
    struct LINES *lines1, *lines2;
    
    char **inputs, **outputs;
    // display an error if an incorrect number of arguments are entered.
    if(argc != 3) {
        printf("USAGE: miter_blif.exe file1.blif file2.blif\n");
        return 1;
    }

    // display an error if one or both of the files fail to open.
    if((file1 = fopen(argv[1], "rt")) == NULL || (file2 = fopen(argv[2], "rt")) == NULL) {
        fclose(file1);
        fclose(file2);
        printf("The file(s) could not be opened.\n");
        return 1;
    }          
    // store lines from files in a linked list, then close files.
    lines1 = fgetlines(file1);
    lines2 = fgetlines(file2);
    fclose(file1);
    fclose(file2);
    // extract inputs from lines1.  We assume inputs in lines1 and 
    // lines2 are the same.
    inputs = getnets(lines1->next->line);
    // extract outputs from lines1.  We assume outputs in lines1 and
    // lines2 are the same.
    outputs = getnets(lines1->next->next->line);
    // write lines to file.
    file3 = fopen("miter.blif", "wt");
    // create model name line.
    fprintf(file3, ".model miter\n");\
    // copy input line
    fprintf(file3, lines1->next->line);
    // create output line
    fprintf(file3, ".outputs");
    int id, i, outcount;
    outcount = atol(outputs[0]);
    for(id = 1; id < 3; id++) {
        for(i = 1; i < outcount; i++) {
            fprintf(file3, " %s_%d", outputs[i], id);
        }
    }
    fprintf(file3, "\n");
    processlines(file3, lines1, "_1", inputs);
    processlines(file3, lines2, "_2", inputs);

    // build miter circuit.
    // create series of xor gates.
    for(i = 1; i < outcount; i++) {
        fprintf(file3, ".names %s_1 %s_2 out%d\n", outputs[i], outputs[i], i);
        fprintf(file3, "01 1\n");
        fprintf(file3, "10 1\n");
    }
    // combine xor gates with an or gate.
    fprintf(file3, ".names");
    for(i = 1; i < outcount; i++) {
        fprintf(file3, " out%d", i);
    }
    fprintf(file3, " out\n");
    char temp[outcount-1];
    memset(temp, '-', outcount-1);
    for(i = 1; i < outcount; i++) {
        temp[i-1] = '1';
        fprintf(file3, "%s 1\n", temp);
        temp[i-1] = '-';
    }
    // close blif with '.end'.
    fprintf(file3, ".end\n");
    fclose(file3);

    // deallocate memory from lines1 & lines2
    freelines(lines1);
    freelines(lines2);

    // deallocate memory from inputs & outputs
    freenets(inputs);
    freenets(outputs);
       
    return 0;
}

