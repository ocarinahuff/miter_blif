miter_blif
==========

A structural miter of two blif files in C, using dynamic arrays.

This file is intended for educational purposes.  It is part of an attempt to explore concepts learned in a C programming course offered by cppinstitute.org.

This is an attempt to solve a problem proposed by an instructor in Digital Testing and Verification; one of creating a structural miter between two functions, each specificed in separate blif files.  The miter is then used in verification tools such as ABC or VIS to test for SAT or UNSAT.

This project was created using Netbeans 8.0.1 on a Windows platform, using the MinGW C/C++ compiler environment.

The problem is the number of lines in the blif files is unknown to the program.  Thus, static char arrays cannot be effectively used to store lines from the file since the size of the array needs to be declared in advance.  Another alternative is to use a singly linked list designed from structures in C.  This approach will be explored separately.

I chose to go with dynamic arrays first, using malloc to allocate memory once the number of lines is deduced using a for loop.  The disadvantage is the need to loop through the file twice, once to get the count, and again to copy the lines from the file into memory.
