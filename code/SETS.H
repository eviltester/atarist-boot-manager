#ifndef _SETS_H
#define _SETS_H

#include <stdio.h>
#include "vt52.h"

extern void sets_window( void );
extern void print_sets_in_window( SET * );
extern void print_sets_title( int );
extern void sets_up_arrow( void );
extern void sets_down_arrow( void );
extern int	sets_main_loop( int * );
extern void  sets_bottom_title( void );
extern void set_progs_on_off_from_set( SET *, FILELIST *);
extern SMALLFILE *append_smallfile( SMALLFILE *, SMALLFILE *);
extern void set_set_from_progs( SET *, FILELIST *);
extern void set_set_from_accs( SET *, FILELIST *);
extern int prog_in_set( char *, SET *);
extern void set_accs_on_off_from_set( SET *, FILELIST *);
extern int acc_in_set( char *, SET *);
extern SET *create_set( void );
extern SET *append_set_to_list( SET *, SET *);
extern SET *new_set_key( SET * );
extern void edit_set( void );
extern SET *delete_set( SET *, int );
extern SET *dlte_set( SET *, SET * );
extern void sets_paging( void );
extern void sets_paging_up( void );





#endif







