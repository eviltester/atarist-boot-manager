#ifndef _VT52_H
#define _VT52_H

#include <stdio.h>
#include <dos.h>
#include <osbind.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <vdi.h>
#include <stdlib.h>

#define ESC					Bconout(2,'\033');
#define Bc(X)				Bconout(2,X);

/* VT52 # defines */
#define CUP					"\033A"		/* cursor up 1 line, no wrap*/
#define CURSOR_UP			{ESC Bc('A')} /*printf("%s",CUP)*/

#define CUD			 		"\033B"		/* cursor down 1, no wrap*/
#define CURSOR_DOWN 		{ESC Bc('B')} /*printf("%s",CUD)*/

#define CUR				 	"\033C"		/* right 1 pos, no wrap */
#define CURSOR_RIGHT 	{ESC Bc('C')} /*printf("%s",CUR)*/

#define CUL			 		"\033D"		/* left 1 pos, no wrap */
#define CURSOR_LEFT 		{ESC Bc('A')} /*printf("%s",CUL)*/

#define CLS					"\033E"		/* clear screen & home to 0,0 */
#define CLEAR_SCREEN		{ESC Bc('E')} /*printf("%s",CLS)*/

#define HME					"\033H"		/* home to 0,0 */
#define HOME				{ESC Bc('H')} /*printf("%s",HME)*/

#define CUPS				"\033I"		/* up 1, scroll */
#define CURSOR_UP_SCRL	{ESC Bc('I')} /*printf("%s",CUPS)*/

#define EEOP				"\033J"		/* erase to end of page cursor pos included */
#define ERASE_EOP			{ESC Bc('J')} /*printf("%s",EEOP)*/

#define CLR_EOL			"\033K"		/* clear to end of line from pos */
#define CLEAR_EOL			{ESC Bc('K')} /*printf("%s",CLR_EOL)*/

#define INS_LINE			"\033L"		/* insert line above */
#define INSERT_LINE		{ESC Bc('L')} /*printf("%s",INS_LINE)*/

#define DEL_LINE			"\033M"		/* delete line and move rest up */
#define DELETE_LINE		{ESC Bc('M')} /*printf("%s",DEL_LINE)*/

#define ESOP				"\033d"		/* erase to start of page including pos */
#define ERASE_SOP			{ESC Bc('d')} /*printf("%s",ESOP)*/

#define SHOW_C				"\033e"		/* show cursor */
#define SHOW_CURSOR		{ESC Bc('e')} /*printf("%s",SHOW_C)*/

#define HIDE_C				"\033f"		/* hide cursor */
#define HIDE_CURSOR		{ESC Bc('f')} /*printf("%s",HIDE_C)*/

#define SAVE_C				"\033j"		/* save cursor */
#define SAVE_CURSOR		{ESC Bc('j')} /*printf("%s",SAVE_C)*/

#define RESTORE_C			"\033k"		/* restore saved pos */
#define RESTORE_CURSOR	{ESC Bc('k')} /*printf("%s",RESTORE_C)*/

#define ELINE				"\033l"		/* erase line and move cursor left edge */
#define ERASE_LINE		{ESC Bc('l')} /*printf("%s",ELINE)*/

#define ESOL				"\033o"		/* erase to start of line including cursor*/
#define ERASE_SOL			{ESC Bc('o')} /*printf("%s",ESOL)*/

#define REV_VID			"\033p"		/* reverse video */
#define REVERSE_VIDEO	{ESC Bc('p')} /*printf("%s",REV_VID)*/

#define NORM_VID			"\033q"		/* normal video */
#define NORMAL_VIDEO		{ESC Bc('q')} /*printf("%s",NORM_VID)*/

#define WEOL				"\033v"		/* wrap at end of line and scroll up */
#define WRAP_EOL			{ESC Bc('v')} /*printf("%s",WEOL)*/

#define DIS_EOL			"\033w"		/* overprint line end char with next char */
#define DISCARD_EOL		{ESC Bc('w')} /*printf("%s",DIS_EOL)*/

/* atari chars */
#define BLL					"\007"
#define BELL				{Bc('\007')} /*printf("%s",BLL)*/

#define BKSP				"\008"
#define BACKSPACE			{Bc('\008')} /*printf("%s",BKSP)*/

#define TB					"\009"
#define TAB					{Bc('\009')} /*printf("%s",TB)*/

#define LF					"\010"
#define LINEFEED			{Bc('\010')} /*printf("%s",LF)*/

#define VTAB				"\011"
#define VERTICAL_TAB		{Bc('\011')} /*printf("%s",VTAB)*/

#define FF					"\012"
#define FORM_FEED			{Bc('\012')} /*printf("%s",FF)*/

#define CR					"\013"		/* carraige return */
#define CARRAIGE_RETURN	{Bc('\013')} /*printf("%s",CR)*/


extern	void	at( int, int);			/* row, col */	

#define AT(Y,X)			{Bc('\033') Bc('Y') Bc(Y+32) Bc(X+32)}



/* prog defines */

/*extern void set_defaults( void );
extern void calculate_screen_sizes( void );
extern void draw_screen( void );
extern void centre_text(char *, char *, int, char);
extern void startup_screen( void );
*/
/*extern void auto_window( void );*/
/*extern void accs_window( void );
extern void sets_window( void );
extern void other_window( void );
*/ 

/* prog globals */

#define SETS_NAME_SIZE	12
#define PROG_NAME_SIZE	8
#define ARROW_BORDER		1
#define LINE_BORDER		1

typedef struct{
					int resolution;
					int rows;
					int columns;
					int progs_win;	/* size of progs win without titles etc */
					int other_win; /* size of other win without titles etc */
					int progs_win_width; /* maximum width in terms of columns */
					int accs_win_width;	/* accs max width */
				}RES_DEF;

typedef struct{
					int resolution;
					int rows;
					int columns;
					int progs_win;	/* size of progs win without titles etc */
					int other_win; /* size of other win without titles etc */
					int progs_win_width; /* maximum width in terms of columns */
					int accs_win_width;	/* accs max width */

					int bypass_time;
					int new_progs_flag;	/* 1 = ON, 2 = OFF, 3 = SAME */
					int new_accs_flag;
					int auto_paging;		/* 1 = paging, 2 = scrolling */
					int accs_paging;
					int sets_paging;
					int other_paging;
					int mouse_keys;
					int bypass_key_shift;
					int bypass_key_high;
					int bypass_key_low;
					char bypass_key_text[6];
					int abort_key_shift;
					int abort_key_high;
					int abort_key_low;
					char abort_key_text[6];
					int page_key_shift;
					int page_key_high;
					int page_key_low;
					char page_key_text[6];
					int toggle_key_shift;
					int toggle_key_high;
					int toggle_key_low;
					char toggle_key_text[6];
					int switch_key_shift;
					int switch_key_high;
					int switch_key_low;
					char switch_key_text[6];
					int help_key_shift;
					int help_key_high;
					int help_key_low;
					char help_key_text[6];
					int options_key_shift;
					int options_key_high;
					int options_key_low;
					char options_key_text[6];
					int new_key_shift;
					int new_key_high;
					int new_key_low;
					char new_key_text[6];
					int delete_key_shift;
					int delete_key_high;
					int delete_key_low;
					char delete_key_text[6];
					char auto_path[FILENAME_MAX];
					char accs_path[FILENAME_MAX];
			}DEFAULTS;

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


/* file stuff */

typedef struct{
					struct FILELIST *left;
					char name[FNSIZE];
					char ext[6];
					struct FILELIST *right;
					int on_off;
					char attr;
					}FILELIST;

extern FILELIST *prgs;
extern FILELIST *accs;

typedef struct{
					struct SMALLFILE *left;
					char name[9];
					struct SMALLFILE *right;
				}SMALLFILE;

typedef struct{
					struct OTHER *left;
					char *from;
					char *to;
					struct OTHER *right;
					}OTHER_FILES;

extern OTHER_FILES *others;
extern OTHER_FILES *curr_other;

#define PAGING 1
#define SCROLLING 2
#define AUTO 1
#define ACCS 2
#define SETS 3
#define OTHER 4
/* SETS */

typedef struct{
					struct SET *left;
					char set_name[17];
					SMALLFILE *progs;
					SMALLFILE *accs;
					OTHER_FILES *others;
					struct SET *right;
				}SET;


extern SET *sets;
extern SET *curr_set;

extern int conset( void );
extern int conunset( void );
extern int main_loop( void );

#define PROGS_WINDOW_TYPE	1
#define SETS_WINDOW_TYPE	2
#define OTHER_WINDOW_TYPE	3

typedef struct{
				struct WINDOW_LIST *left;
				char *name;
				int x;
				int y;
				int cols;
				int depth;
				int name_at_top;
				int nums_at_top;
				int type; 		
				void *other_info;
				struct WINDOW_LIST *right;
				} WINDOW_LIST;

typedef struct{
				char *path;
				char good_extension[4];
				char bad_extension[4];
				FILELIST *files;
			}PROGS_WINDOW_DETAILS;
			
typedef struct{
				OTHER_FILES *others;
			}OTHER_FILES_DETAILS;
			
typedef struct{
				SET *sets;
			}SET_DETAILS;
			
#endif
