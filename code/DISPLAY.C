#include "display.h"
#include "progs.h"
#include "sets.h"
#include "other.h"
#include "accs.h"
#include "filelist.h"
#include <stdlib.h>


void print_cursor(int window,char l,char r, int cursor)
{
	int phys_curs;
	int phys_col;
	int y;
	int x;

/*	at(2,5);
	printf("pl %d, pp %d, cur %d ",logical_progs_cursor, progs_cursor, cursor);
*/
	switch(window)
	{
	case AUTO:	/* progs */

			phys_col=(cursor-1)/prog_defaults.progs_win;
			phys_curs=(cursor-1)%prog_defaults.progs_win;
			y=phys_curs+mid_window_first_item_row;
			x=auto_menu_col+1+(phys_col*9);
			AT(y,x)

			Bconout(2,l);
			AT(y,x+9)

			Bconout(2,r);
			break;

	case ACCS:	/* accs */

			phys_col=(cursor-1)/prog_defaults.progs_win;
			phys_curs=(cursor-1)%prog_defaults.progs_win;
			y=phys_curs+mid_window_first_item_row;
			x=accs_menu_col+1+(phys_col*9);


			AT(y,x)
			Bconout(2,l);

			AT(y,x+9)
			Bconout(2,r);
			break;
		case SETS:
			phys_col=0;
			phys_curs=(cursor-1)%prog_defaults.progs_win;
			y=phys_curs+mid_window_first_item_row;
			x=sets_menu_col+1;
			AT(y,x)

			Bconout(2,l);
			AT(y,x+13)

			Bconout(2,r);
			break;
		case OTHER:
			phys_col=0;
			phys_curs=(cursor-1)%prog_defaults.other_win;
			y=phys_curs+other_window_first_item_row;
			x=1;
			AT(y,x)

			Bconout(2,l);
			AT(y,prog_defaults.columns-2)

			Bconout(2,r);
			break;

		default:
			break;
	}
}
				


void remove_cursor(int window, int cursor)
{
	if(cursor!=0)
	print_cursor(window,' ',' ',cursor);
}

void draw_cursor(int window, int cursor)
{
	if(cursor!=0)
	print_cursor(window,'>','<', cursor);
}


void print_at_from(int row, int col, int from, int screen_length, char *string_to_show)
{

	int loop;

	AT(row,col)

	for(loop=from;loop<from+screen_length && string_to_show[loop]!='\0';loop++)
	{
		Bconout(2,string_to_show[loop]);
	}
}

void at(int row, int col)
{
	int r,c;
	
	r=32+row;
	c=32+col;

/*	printf("\033Y%c%c",r,c);*/
	Bconout(2,'\033');
	Bconout(2,'Y');
	Bconout(2,r);
	Bconout(2,c);
}

void draw_old_window_title( int window )
{
	int width;
	char total[4];


	switch(window)
	{
		case 1:
				width=(prog_defaults.progs_win_width*
							(PROG_NAME_SIZE+ARROW_BORDER))+
							ARROW_BORDER+
							LINE_BORDER+
							LINE_BORDER;
				centre_text("AUTO",line_buffer,width,' ');
				AT(mid_window_title_row,auto_menu_col)
				printf("%s",line_buffer);
				break;
		case 2:
				width=(prog_defaults.accs_win_width*
						(PROG_NAME_SIZE+ARROW_BORDER))+
						ARROW_BORDER+
						LINE_BORDER+
						LINE_BORDER;

				centre_text("ACCS",line_buffer,width,' ');
				AT(mid_window_title_row,accs_menu_col)
				printf("%s",line_buffer);
				break;
		case 3:
				width=SETS_NAME_SIZE+
						ARROW_BORDER+
						ARROW_BORDER+
						LINE_BORDER+
						LINE_BORDER;

				centre_text("SETS",line_buffer,width,' ');
				AT(mid_window_title_row,sets_menu_col)
				printf("%s",line_buffer);
				break;
		case 4:
				width=prog_defaults.columns;

				centre_text("OTHER",line_buffer,width,'-');
				AT(other_window_title_row,0)
				line_buffer[0]='+';
				line_buffer[width-1]='+';
				printf("%s",line_buffer);

				sprintf(total,"%d",total_others);
				AT(other_window_title_row,width-2-strlen(total))
				printf("%s",total);
				AT(other_window_title_row,2)
				printf("%d",logical_other_cursor);
				break;
		}
}

void draw_new_window_title( int window )
{
	int width;
	char *cp;
	char total[4];

	switch(window)
	{
		case 1:
				width=(prog_defaults.progs_win_width*
							(PROG_NAME_SIZE+ARROW_BORDER))+
							ARROW_BORDER+
							LINE_BORDER+
							LINE_BORDER;
				centre_text("AUTO",line_buffer,width,' ');
				AT(mid_window_title_row,auto_menu_col)
				cp=line_buffer;
				while(*cp==' ')
				{
					Bconout(2,*cp);
					cp++;
				}
				REVERSE_VIDEO
				while(*cp!=' ')
				{
					Bconout(2,*cp);
					cp++;
				}
				NORMAL_VIDEO
				while(*cp!='\0')
				{
					Bconout(2,*cp);
					cp++;
				}
				break;
		case 2:
				width=(prog_defaults.accs_win_width*
						(PROG_NAME_SIZE+ARROW_BORDER))+
						ARROW_BORDER+
						LINE_BORDER+
						LINE_BORDER;

				centre_text("ACCS",line_buffer,width,' ');
				AT(mid_window_title_row,accs_menu_col)
				cp=line_buffer;
				while(*cp==' ')
				{
					Bconout(2,*cp);
					cp++;
				}
				REVERSE_VIDEO
				while(*cp!=' ')
				{
					Bconout(2,*cp);
					cp++;
				}
				NORMAL_VIDEO
				while(*cp!='\0')
				{
					Bconout(2,*cp);
					cp++;
				}

				break;
		case 3:
				width=SETS_NAME_SIZE+
						ARROW_BORDER+
						ARROW_BORDER+
						LINE_BORDER+
						LINE_BORDER;

				centre_text("SETS",line_buffer,width,' ');
				AT(mid_window_title_row,sets_menu_col)
				cp=line_buffer;
				while(*cp==' ')
				{
					Bconout(2,*cp);
					cp++;
				}
				REVERSE_VIDEO
				while(*cp!=' ')
				{
					Bconout(2,*cp);
					cp++;
				}
				NORMAL_VIDEO
				while(*cp!='\0')
				{
					Bconout(2,*cp);
					cp++;
				}

				break;
		case 4:
				width=prog_defaults.columns;

				centre_text("OTHER",line_buffer,width,'-');
				AT(other_window_title_row,0)
				line_buffer[0]='+';
				line_buffer[width-1]='+';
				cp=line_buffer;
				while(*cp=='-' || *cp=='+')
				{
					Bconout(2,*cp);
					cp++;
				}
				REVERSE_VIDEO
				while(*cp!='-')
				{
					Bconout(2,*cp);
					cp++;
				}
				NORMAL_VIDEO
				while(*cp!='\0')
				{
					Bconout(2,*cp);
					cp++;
				}
				sprintf(total,"%d",total_others);
				AT(other_window_title_row,width-2-strlen(total))
				printf("%s",total);
				AT(other_window_title_row,2)
				printf("%d",logical_other_cursor);

				break;
		}
}

void draw_screen( void )
{

	CLEAR_SCREEN
	
	DISCARD_EOL

	AT(title_row,0)
	REVERSE_VIDEO
	centre_text("ALs BOOTY",line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);
	NORMAL_VIDEO

	auto_window();
	print_progs(prgs,curr_set,first_prog_on_screen);
	print_auto_title(logical_progs_cursor);
	
	accs_window();
	print_accs(accs,curr_set,first_acc_on_screen);
	print_accs_title(logical_accs_cursor);

	sets_window();
	print_sets_in_window( sets );
	print_sets_title(logical_sets_cursor);

	other_window();
	print_others_in_window( others );


	draw_new_window_title(current_window);

	switch(current_window)
	{
		case 1:
					draw_cursor(current_window,progs_cursor);
					progs_bottom_title();
					break;	
		case 2:
					draw_cursor(current_window,accs_cursor);
	AT(bottom_title_row,0)
	REVERSE_VIDEO
	centre_text("XXX",line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);
	AT(bottom_title_row+1,0)
	REVERSE_VIDEO
	centre_text("XXX",line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);
					break;	
		case 3:
					draw_cursor(current_window,sets_cursor);
					break;	
		case 4:
					draw_cursor(current_window,other_cursor);
					break;	
	}
	

/*	AT(bottom_title_row,0)
	REVERSE_VIDEO
	centre_text("XXX",line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);
	AT(bottom_title_row+1,0)
	REVERSE_VIDEO
	centre_text("XXX",line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);
*/

	NORMAL_VIDEO
	WRAP_EOL

}

void centre_text(char *text_to_centre,char *centre_buffer, int width, char padding)
{

	int str_len=strlen(text_to_centre);
	int before_spaces;
	int after_spaces;
	int loop;
 
	before_spaces=(width/2)-((str_len/2)+(str_len%2));
	after_spaces=(width-(width/2))-(str_len/2);

	for(loop=0;loop<before_spaces;loop++)
		centre_buffer[loop]=padding;

	for(loop=0;loop<str_len;loop++)
		centre_buffer[before_spaces+loop]=text_to_centre[loop];

	for(loop=0;loop<after_spaces;loop++)
		centre_buffer[before_spaces+str_len+loop]=padding;

	centre_buffer[width]='\0';

}

void startup_screen( void )
{

	int secs;
	int curr_sec,temp_sec;
	clock_t tval2;
	long key;
	int upper,lower;

	char sec_buff[6];



	CLEAR_SCREEN

	centre_text("AL's BOOTY",line_buffer,prog_defaults.columns,' ');
	
	DISCARD_EOL
	AT(title_row,0)
	REVERSE_VIDEO
	printf("%s",line_buffer);
	NORMAL_VIDEO

	AT(0,0)
	REVERSE_VIDEO
	printf("%s",aldate);
	NORMAL_VIDEO

/*	update_time();
	AT(prog_defaults.columns-10,0)
	REVERSE_VIDEO
	printf("%s",altime);
	NORMAL_VIDEO
*/

	centre_text("PRESS THE BYPASS KEY TO QUIT",line_buffer,prog_defaults.columns,' ');
	AT(bottom_title_row,0)
	REVERSE_VIDEO
	printf("%s",line_buffer);
	NORMAL_VIDEO

	centre_text("ANY OTHER KEY TO ENTER PROGRAM",line_buffer,prog_defaults.columns,' ');
	AT(bottom_title_row+1,0)
	REVERSE_VIDEO
	printf("%s",line_buffer);
	NORMAL_VIDEO

	secs=prog_defaults.bypass_time;

	tval2=clock();
 	curr_sec= tval2/CLK_TCK;
	temp_sec=curr_sec;


	while(!Bconstat(2) && (curr_sec<prog_defaults.bypass_time)) 
	{
		sprintf(sec_buff,"%d",secs);
		centre_text(sec_buff,line_buffer,prog_defaults.columns,' ');
		AT(prog_defaults.rows/2,0)
		NORMAL_VIDEO
		printf("%s",line_buffer);
		NORMAL_VIDEO

		while(!Bconstat(2) && temp_sec==curr_sec)
		{
				tval2=clock();
				temp_sec= tval2/CLK_TCK;
/*				update_time();
				AT(prog_defaults.columns-10,0)
				REVERSE_VIDEO
				printf("%s",altime);
				NORMAL_VIDEO*/
		}
		secs--;
		curr_sec=temp_sec;
	}

	if(Bconstat(2))
	{
			key=Bconin(2);
			upper=(int)(key>>16);
			lower=(int)(key%256);


		if(upper==prog_defaults.bypass_key_high 
			&& lower==prog_defaults.bypass_key_low)
		{
			CLEAR_SCREEN
			exit(1);
		}
	}
	else
	{
		CLEAR_SCREEN
		exit(1);
	}


	WRAP_EOL

}


void help_screen()
{
	char temp_text[35];
	char help_info[][30]={	"DELETE ENTRY       ",
									"NEW ENTRY          ",
									"JUMP WINDOW        ",
								 	"EXIT/ABORT         ",
									"HELP               ",
									"PAGE               ",
									"OPTIONS            ",
								 	"TOGGLE             ",
									"CURSOR KEYS MOVE CURSORS"};

	int lines_of_help=9;
	int first_line_of_help;

	first_line_of_help=((prog_defaults.rows-3)/2)-(lines_of_help/2);


	CLEAR_SCREEN

	centre_text("HELP",line_buffer,prog_defaults.columns,' ');
	
	DISCARD_EOL
	AT(title_row,0)
	REVERSE_VIDEO
	printf("%s",line_buffer);
	NORMAL_VIDEO

	AT(0,0)
	REVERSE_VIDEO
	printf("%s",aldate);
	NORMAL_VIDEO


	AT(first_line_of_help,0)
	sprintf(temp_text,"%s%s",help_info[0],prog_defaults.delete_key_text);
	centre_text(temp_text,line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);

	AT(first_line_of_help+1,0)
	sprintf(temp_text,"%s%s",help_info[1],prog_defaults.new_key_text);
	centre_text(temp_text,line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);

	AT(first_line_of_help+2,0)
	sprintf(temp_text,"%s%s",help_info[2],prog_defaults.switch_key_text);
	centre_text(temp_text,line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);

	AT(first_line_of_help+3,0)
	sprintf(temp_text,"%s%s",help_info[3],prog_defaults.abort_key_text);
	centre_text(temp_text,line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);

	AT(first_line_of_help+4,0)
	sprintf(temp_text,"%s%s",help_info[4],prog_defaults.new_key_text);
	centre_text(temp_text,line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);

	AT(first_line_of_help+5,0)
	sprintf(temp_text,"%s%s",help_info[5],prog_defaults.page_key_text);
	centre_text(temp_text,line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);

	AT(first_line_of_help+6,0)
	sprintf(temp_text,"%s%s",help_info[6],prog_defaults.options_key_text);
	centre_text(temp_text,line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);

	AT(first_line_of_help+7,0)
	sprintf(temp_text,"%s%s",help_info[7],prog_defaults.toggle_key_text);
	centre_text(temp_text,line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);

	AT(first_line_of_help+8,0)
	sprintf(temp_text,"%s",help_info[8]);
	centre_text(temp_text,line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);



	centre_text("PRESS ANY KEY TO RETURN TO",line_buffer,prog_defaults.columns,' ');
	AT(bottom_title_row,0)
	REVERSE_VIDEO
	printf("%s",line_buffer);
	NORMAL_VIDEO

	centre_text(" THE MAIN PROGRAM",line_buffer,prog_defaults.columns,' ');
	AT(bottom_title_row+1,0)
	REVERSE_VIDEO
	printf("%s",line_buffer);
	NORMAL_VIDEO

	while(!Bconstat(2))
	{
/*		update_time();
		AT(prog_defaults.columns-10,0)
		REVERSE_VIDEO
		printf("%s",altime);
		NORMAL_VIDEO*/
	}
}

