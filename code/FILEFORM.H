#ifndef _FILEFORM_H
#define _FILEFORM_H

#include <stdio.h>
#include "vt52.h"

extern int get_token( FILE *, char * );
extern void skip_to_eol( FILE *);
extern int get_block_type(FILE *);
extern char *read_name(FILE *, char );
extern SET *load_sets( FILE *);
extern void save_sets( FILE *);




#endif