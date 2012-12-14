#ifndef _FILELIST_H
#define _FILELIST_H

#include <stdio.h>
#include "vt52.h"

extern void print_progs( FILELIST *, SET *, int );
extern void print_accs( FILELIST *, SET *, int );
extern FILELIST *build_list(char *, char *, short);
extern void rename_progs_and_accs( int );
extern void copy_file(FILE *, FILE *, char *, int );
extern void process_others(int);
extern void consistency_check( SET *, FILELIST *, int );


#endif


