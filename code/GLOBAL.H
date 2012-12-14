#ifndef _GLOBAL_H
#define _GLOBAL_H

#include "filelist.h"
#include "sets.h"
#include "defaults.h"

extern int top_line_size;				/*title line*/
extern int top_gap;				   	/* gap between title and windows */
extern int mid_window_titles;			/* titles of windows */
extern int mid_window_bottom;			/* bottom */
extern int middle_gap;				/* gap between that and the other window*/
extern int bot_window_title;
extern int bot_window_bottom;
extern int bottom_gap;
extern int bottom_line_size;			/* size of bottom lines */
extern int extra_lines;

extern int left_border;
extern int right_border;
extern int auto_accs_gap;
extern int accs_sets_gap;

extern int title_row;
extern int mid_window_title_row;
extern int mid_window_first_item_row;
extern int other_window_title_row;
extern int other_window_first_item_row;
extern int bottom_title_row;

extern int auto_menu_col;
extern int accs_menu_col;
extern int sets_menu_col;


extern int total_accs;
extern int total_sets;
extern int total_progs;
extern int total_others;

extern int logical_progs_cursor;
extern int logical_accs_cursor;
extern int logical_sets_cursor;
extern int logical_other_cursor;

extern int progs_cursor;
extern int accs_cursor;
extern int sets_cursor;
extern int other_cursor;

extern int old_progs_cursor;
extern int old_accs_cursor;
extern int old_sets_cursor;
extern int old_other_cursor;

extern int current_window;
extern int old_window;

extern int first_prog_on_screen;
extern int first_acc_on_screen;
extern int first_set_on_screen;
extern int first_other_on_screen;

/* Date */
/* current time */
extern char altime[];
extern char aldate[];

extern DEFAULTS prog_defaults;
extern RES_DEF	resolutions[];

extern char *line_buffer;

extern FILELIST *prgs;
extern FILELIST *accs;
extern SET *sets;
extern SET *curr_set;

extern int conset( void );
extern void get_key(int *, int *, int *);
extern int conunset( void );

#endif