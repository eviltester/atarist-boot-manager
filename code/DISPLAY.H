#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdio.h>
#include "vt52.h"

extern void print_cursor(int ,char ,char , int );
extern void remove_cursor(int , int );
extern void draw_cursor(int , int );
extern void print_at_from(int , int , int , int , char *);
extern void at(int , int );
extern void draw_old_window_title( int );
extern void draw_screen( void );
extern void centre_text(char *,char *,int,char);
extern void startup_screen( void );
extern void help_screen( void );
extern void draw_new_window_title( int );

#endif