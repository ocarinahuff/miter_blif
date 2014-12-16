/* 
 * File:   lines.h
 * Author: ocarinahuff
 *
 * Created on December 14, 2014, 11:44 PM
 */

#ifndef LINES_H
#define	LINES_H

#ifdef	__cplusplus
extern "C" {
#endif

#define BUF_SIZE 255
#define MAX_STR_LEN 255

/*
 * This is a linked list structure used to store lines from a file.
 * Each node in the list represents a line from a file.
 */    
struct LINES {
    char *line;
    struct LINES *next;
};

/**
 * Extract variables from a line, and store them in a 2D dynamic array.  The 
 * first element of this array contains a count of variables, plus one, stored 
 * as a string.  The rest of the elements are variables stored as a string.
 * @param line
 * @return a 2D dynamic array of string variables.
 */
char **getnets(char *line);

/**
 * Free allocated memory from net.
 * @param net
 */
void freenets(char **net);

/**
 * Read lines from a file, and store them in a linked list structure.
 * @param file
 * @return a linked list structure, stores lines from file.
 */
struct LINES *fgetlines(FILE *file);

/**
 * Free allocated memory from lines.
 * @param lines
 */
void freelines(struct LINES *lines);

/**
 * Process each line in lines, and write them to file.
 * @param file, the file to write to.
 * @param lines, the set of lines to process.
 * @param label, the label string to affix to end of variables.
 * @param inputs, the set of inputs to check against variables.  Inputs will
 * not have labels affixed to the end of it.
 */
void processlines(FILE *file, struct LINES *lines, char *label, char **inputs);

/**
 * Check if the string line is contained in the array of strings nets.
 * Returns an int 1 if a match is found, and zero otherwise.
 * @param line
 * @param nets
 * @return 1 if a match is found, 0 otherwise.
 */
int checknets(char *line, char **nets);

#ifdef	__cplusplus
}
#endif

#endif	/* LINES_H */