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




#ifdef	__cplusplus
}
#endif

#endif	/* LINES_H */

struct LINES {
    char *line;
    struct LINES *next;
};

/**
 * 
 * @param file
 * @return 
 */
struct LINES *fgetlines(FILE *file);

/**
 * 
 * @param lines
 */
void freelines(struct LINES *lines);