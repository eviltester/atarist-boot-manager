#include "progs.h"
#include "sets.h"
#include "display.h"
#include "global.h"


void progs_bottom_title()
{
	
	char temp[50];

	DISCARD_EOL

	sprintf(	temp,
				"CURSOR-^v<>  PAGE-%s  TOGGLE-%s",
				prog_defaults.page_key_text,
				prog_defaults.toggle_key_text);

	AT(bottom_title_row,0)
	REVERSE_VIDEO
	centre_text(temp,line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);

	if(prog_defaults.columns<=40)
		sprintf( temp,
				"SWTC-%s HLP-%s OPT-%s BYE-%s",
				prog_defaults.switch_key_text,
				prog_defaults.help_key_text,
				prog_defaults.options_key_text,
				prog_defaults.abort_key_text);
	else	
		sprintf( temp,
				"SWITCH-%s  HELP-%s  OPTIONS-%s EXIT-%s",
				prog_defaults.switch_key_text,
				prog_defaults.help_key_text,
				prog_defaults.options_key_text,
				prog_defaults.abort_key_text);

	AT(bottom_title_row+1,0)
	REVERSE_VIDEO
	centre_text(temp,line_buffer,prog_defaults.columns,' ');
	printf("%s",line_buffer);

	NORMAL_VIDEO
	WRAP_EOL
}

void auto_window( void )
{

	int width;
	int loop;

	width=(prog_defaults.progs_win_width*(PROG_NAME_SIZE+ARROW_BORDER))+ARROW_BORDER+
					LINE_BORDER+
					LINE_BORDER;

	/* auto title */

	centre_text("AUTO",line_buffer,width,' ');
	AT(mid_window_title_row,auto_menu_col)
	printf("%s",line_buffer);

	centre_text("----",line_buffer,width,'-');
	AT(mid_window_title_row+1,auto_menu_col)
	line_buffer[0]='+';
	line_buffer[width-1]='+';
	printf("%s",line_buffer);

	for(loop=0;loop<width;loop++)
		line_buffer[loop]=' ';
	line_buffer[loop]='\0';

	line_buffer[0]='|';
	line_buffer[width-1]='|';

	for(loop=0;loop<prog_defaults.progs_win;loop++)
	{
		AT(mid_window_first_item_row+loop,auto_menu_col)
		printf("%s",line_buffer);
	}

	centre_text("--",line_buffer,width,'-');
	line_buffer[0]='+';
	line_buffer[width-1]='+';
	AT(mid_window_first_item_row+prog_defaults.progs_win,auto_menu_col)
	printf("%s",line_buffer);

}

void print_auto_title( int cursor_on )
{

	int width;
/*	int loop;*/
	char total[4];
	char current[4];

	width=(prog_defaults.progs_win_width*(PROG_NAME_SIZE+ARROW_BORDER))+ARROW_BORDER+
					LINE_BORDER+
					LINE_BORDER;

	/* auto title */


	centre_text("----",line_buffer,width,'-');
	AT(mid_window_title_row+1,auto_menu_col)
	line_buffer[0]='+';
	line_buffer[width-1]='+';
	printf("%s",line_buffer);

	sprintf(total,"%d",total_progs);
	AT(mid_window_title_row+1,auto_menu_col+width-2-strlen(total))
	printf("%s",total);

	sprintf(current,"%d",cursor_on);
	AT(mid_window_title_row+1,auto_menu_col+2)
	printf("%s",current);

}

void progs_up_arrow()
{
		int num_in_window;

		num_in_window=prog_defaults.progs_win*prog_defaults.progs_win_width;		


/* at first entry */
/* at middle entry in middle */
/* at middle entry at top of window */


	if(logical_progs_cursor<=1) /* at first entry */
					BELL
	else
	{
		if(progs_cursor<=1)
		{
			old_progs_cursor=progs_cursor;
			progs_cursor=1;


				if(prog_defaults.auto_paging==SCROLLING)
				{
					logical_progs_cursor--;
					first_prog_on_screen--;
				}
				else
				{
					first_prog_on_screen-=num_in_window;
					logical_progs_cursor--;
					if(logical_progs_cursor<num_in_window)
						progs_cursor=logical_progs_cursor;
					else
						progs_cursor=num_in_window;
				}

				if(first_prog_on_screen<1)
					first_prog_on_screen=1;
				if(logical_progs_cursor<1)
					logical_progs_cursor=1;

			print_progs(prgs,curr_set,first_prog_on_screen);

		}
		else
		{
			old_progs_cursor=progs_cursor;
			progs_cursor--;
			logical_progs_cursor--;
			
		}
		print_auto_title(logical_progs_cursor);
		remove_cursor(current_window,old_progs_cursor);	
		draw_cursor(current_window,progs_cursor);
	}

}

void progs_down_arrow()
{
		int num_in_window;

		num_in_window=prog_defaults.progs_win*prog_defaults.progs_win_width;		

/* last entry */
/* middle entry at end */
/* middle entry in middle */

	if(logical_progs_cursor>=total_progs)
					BELL
	else
	{
		if(progs_cursor>=num_in_window)
		{

				progs_cursor=num_in_window;
				old_progs_cursor=progs_cursor;

			if(prog_defaults.auto_paging==SCROLLING)
			{
				first_prog_on_screen++;
				logical_progs_cursor++;
			}
			else
			{
				logical_progs_cursor++;
				first_prog_on_screen+=num_in_window;
				progs_cursor=1;
			}

			if(first_prog_on_screen>total_progs)
				first_prog_on_screen=total_progs-num_in_window;
			if(first_prog_on_screen<1)
				first_prog_on_screen=1;

			if(logical_progs_cursor>total_progs)
				logical_progs_cursor=total_progs;

			print_progs(prgs,curr_set,first_prog_on_screen);

		}
		else
		{
			logical_progs_cursor++;
			old_progs_cursor=progs_cursor;
			progs_cursor++;
		}
		print_auto_title(logical_progs_cursor);
		remove_cursor(current_window,old_progs_cursor);	
		draw_cursor(current_window,progs_cursor);
	}	
}

void progs_right_arrow()
{
		int num_in_window;
		int column;
		num_in_window=prog_defaults.progs_win*prog_defaults.progs_win_width;		
		column=(progs_cursor-1)/prog_defaults.progs_win;


/* middle column */
/* middle column with blank to the right */
/* last column */

	if(column+1>=prog_defaults.progs_win_width) /* need to page */
	{
		if(first_prog_on_screen+progs_cursor+prog_defaults.progs_win<=total_progs+1)
		{
			if(progs_cursor+prog_defaults.progs_win>num_in_window)
			{
				old_progs_cursor=progs_cursor;
				first_prog_on_screen+=prog_defaults.progs_win;
				logical_progs_cursor+=prog_defaults.progs_win;
			}
			else
			{
				logical_progs_cursor+=prog_defaults.progs_win;
				old_progs_cursor=progs_cursor;
				progs_cursor+=prog_defaults.progs_win;
			}

			print_progs(prgs,curr_set,first_prog_on_screen);
			print_auto_title(logical_progs_cursor);
			remove_cursor(current_window,old_progs_cursor);	
			draw_cursor(current_window,progs_cursor);
		}	
		else
			BELL
	}
	else
	{
		if(first_prog_on_screen+progs_cursor+prog_defaults.progs_win<=total_progs+1)
		{

				logical_progs_cursor+=prog_defaults.progs_win;
				old_progs_cursor=progs_cursor;
				progs_cursor+=prog_defaults.progs_win;

			print_auto_title(logical_progs_cursor);
			remove_cursor(current_window,old_progs_cursor);	
			draw_cursor(current_window,progs_cursor);
		}	
		else
			BELL
	}
}

void progs_left_arrow()
{
		int num_in_window;
		int column;
		num_in_window=prog_defaults.progs_win*prog_defaults.progs_win_width;		
		column=(progs_cursor-1)/prog_defaults.progs_win;


/* middle column */
/* middle column with blank to the right */
/* last column */

	if(column==0) /* need to page */
	{
		if(first_prog_on_screen-prog_defaults.progs_win>0)
		{


				logical_progs_cursor-=prog_defaults.progs_win;
				first_prog_on_screen-=prog_defaults.progs_win;
				old_progs_cursor=progs_cursor;



			print_progs(prgs,curr_set,first_prog_on_screen);
			print_auto_title(logical_progs_cursor);
			remove_cursor(current_window,old_progs_cursor);	
			draw_cursor(current_window,progs_cursor);
		}	
		else
			BELL
	}
	else
	{
/*		if(first_prog_on_screen+progs_cursor+prog_defaults.progs_win<total_progs)
		{
			if(progs_cursor+prog_defaults.progs_win>num_in_window)
			{
				old_progs_cursor=progs_cursor;
				first_prog_on_screen+=prog_defaults.progs_win;
				logical_progs_cursor+=prog_defaults.progs_win;
			}
			else
			{*/
				logical_progs_cursor-=prog_defaults.progs_win;
				old_progs_cursor=progs_cursor;
				progs_cursor-=prog_defaults.progs_win;
/*			}*/

			print_auto_title(logical_progs_cursor);
			remove_cursor(current_window,old_progs_cursor);	
			draw_cursor(current_window,progs_cursor);
/*		}	
		else
			BELL*/
	}
}

void progs_paging()
{
		int num_in_window;
		int column;
		num_in_window=prog_defaults.progs_win*prog_defaults.progs_win_width;		
		column=(progs_cursor-1)/prog_defaults.progs_win;

		if(first_prog_on_screen+num_in_window<total_progs+1)
		{

				first_prog_on_screen+=num_in_window;
				logical_progs_cursor+=num_in_window;

				if(logical_progs_cursor>total_progs)
					logical_progs_cursor=total_progs;

				old_progs_cursor=progs_cursor;
				progs_cursor=logical_progs_cursor-first_prog_on_screen;
				progs_cursor++;

				print_progs(prgs,curr_set,first_prog_on_screen);
				print_auto_title(logical_progs_cursor);
				remove_cursor(current_window,old_progs_cursor);	
				draw_cursor(current_window,progs_cursor);
		}	
		else
			BELL

}

void progs_paging_up()
{
		int num_in_window;
		int column;
		num_in_window=prog_defaults.progs_win*prog_defaults.progs_win_width;		
		column=(progs_cursor-1)/prog_defaults.progs_win;

		if(first_prog_on_screen>1)
		{

				first_prog_on_screen-=num_in_window;
				logical_progs_cursor-=num_in_window;

				if(logical_progs_cursor<1)
					logical_progs_cursor=1;
		
				if(first_prog_on_screen<1)
					first_prog_on_screen=1;

				old_progs_cursor=progs_cursor;
				progs_cursor=logical_progs_cursor-first_prog_on_screen;
				progs_cursor++;

				print_progs(prgs,curr_set,first_prog_on_screen);
				print_auto_title(logical_progs_cursor);
				remove_cursor(current_window,old_progs_cursor);	
				draw_cursor(current_window,progs_cursor);
		}	
		else
			BELL

}

void progs_toggle_key( void )
{

	FILELIST *flp;
	int loop;

	loop=1;
	flp=prgs;

	while(flp!=NULL && loop!=logical_progs_cursor)
	{
		loop++;
		flp=flp->right;
	}

	if(flp!=NULL)
	{
		if(flp->on_off==1)
			flp->on_off=0;
		else
			flp->on_off=1;
	}
	print_progs(prgs,curr_set,first_prog_on_screen);
	
}

int progs_main_loop( int *shift_key )
{
/*		long k;*/
		int s,u,l;

	while(1)
	{

		while(!Bconstat(2))
		{
			/*possibly update the clock here*/;
		}
/*		k=Bconin(2);
		u=(int)(k>>16);
		l=(int)(k%256);
*/
		get_key(&s,&u,&l);


		if(u==0x48 && s!=2)
			progs_up_arrow();
		else
		{
			if(u==prog_defaults.page_key_high || (u==0x50 && s==2))
				progs_paging();
			else
			{
				if(u==0x50)
					progs_down_arrow();
				else
				{
					if(u==0x4D)
						progs_right_arrow();
					else
					{
						if(u==0x4B)
							progs_left_arrow();
						else
						{
							if(u==prog_defaults.toggle_key_high)
							{
								if(curr_set==NULL)
									sets=new_set_key( sets );
								else
									progs_toggle_key();
							}
							else
							{	
								if(u==0x48 && s==2)
									progs_paging_up();
								else
								{
									*shift_key=s;
									return u;
								}
							}
						}
					}
				}
			}
		}
	}
}
