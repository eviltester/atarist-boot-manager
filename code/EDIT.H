#ifndef _EDIT_H
#define _EDIT_H

#include <stdio.h>
#include "vt52.h"

extern int valid_filename_char(char );	
extern void edit_bottom_title( void );
extern void edit_at(int , int , int , int , char *, char , int , int (*)( char ), int);
extern void print_date_at( int, int, char *);
extern void edit_date_at(int, int, int *, int *, int *);
extern void print_time_at( int, int, char *);
extern void edit_time_at(int, int, int *, int *, int *);
#endif





