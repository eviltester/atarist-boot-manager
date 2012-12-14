#ifndef _OPTIONS_H
#define _OPTIONS_H

#include <stdio.h>
#include "vt52.h"

extern void print_on_off_same(int , int , int );
extern void options_bottom_title(void );
extern void print_paging_scrolling(int , int , int );
extern void print_option(int , int , int , int );
extern void remove_extension( char * );
extern void options_screen( void );


#endif


