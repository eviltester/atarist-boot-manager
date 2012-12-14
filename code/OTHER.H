#ifndef _OTHER_H
#define _OTHER_H

#include <stdio.h>
#include "vt52.h"

extern void other_window( void );
extern int other_main_loop( int * );
extern void other_bottom_title( void );
extern OTHER_FILES *create_other( void );
extern OTHER_FILES *new_other_key( OTHER_FILES * );
extern OTHER_FILES *append_other_to_list( OTHER_FILES *, OTHER_FILES *);
extern void print_others_in_window( OTHER_FILES * );
extern void print_others_title( int );
extern OTHER_FILES *delete_other( OTHER_FILES *, int );
extern OTHER_FILES *dlte_other( OTHER_FILES *, OTHER_FILES *);
extern void other_up_arrow( void );
extern void other_down_arrow( void );
extern void other_paging( void );
extern void other_paging_up( void );
extern void edit_other( void );
extern void set_other_counts( void );




#endif



