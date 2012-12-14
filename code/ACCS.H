#ifndef _ACCS_H
#define _ACCS_H

#include <stdio.h>
#include "vt52.h"

extern void accs_window( void );
extern void print_accs_title( int cursor_on );
extern void accs_up_arrow( void );
extern void accs_down_arrow( void );
extern void accs_right_arrow( void );
extern void accs_left_arrow( void );
extern void accs_paging( void );
extern void accs_paging_up( void );
extern int accs_main_loop( int * );
extern void accs_bottom_title( void );

#endif





