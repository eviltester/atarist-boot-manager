#include "accs.h"
#include "sets.h"
#include "display.h"
#include "filelist.h"
#include "global.h"


void accs_window( void )
{

	int width;
	int loop;

	width=(prog_defaults.accs_win_width*(PROG_NAME_SIZE+ARROW_BORDER))+ARROW_BORDER+
					LINE_BORDER+
					LINE_BORDER;

	/* accs title */

	centre_text("ACCS",line_buffer,width,' ');
	AT(mid_window_title_row,accs_menu_col)
	printf("%s",line_buffer);

	centre_text("----",line_buffer,width,'-');
	AT(mid_window_title_row+1,accs_menu_col)
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
		AT(mid_window_first_item_row+loop,accs_menu_col)
		printf("%s",line_buffer);
	}

	centre_text("--",line_buffer,width,'-');
	line_buffer[0]='+';
	line_buffer[width-1]='+';
	AT(mid_window_first_item_row+prog_defaults.progs_win,accs_menu_col)
	printf("%s",line_buffer);

}

void print_accs_title( int cursor_on )
{

	int width;
/*	int loop;*/
	char current[4];
	char total[4];

	width=(prog_defaults.accs_win_width*(PROG_NAME_SIZE+ARROW_BORDER))+ARROW_BORDER+
					LINE_BORDER+
					LINE_BORDER;

	/* accs title */


	centre_text("----",line_buffer,width,'-');
	AT(mid_window_title_row+1,accs_menu_col)
	line_buffer[0]='+';
	line_buffer[width-1]='+';
	printf("%s",line_buffer);

	sprintf(total,"%d",total_accs);
	AT(mid_window_title_row+1,accs_menu_col+width-2-strlen(total))
	printf("%s",total);

	sprintf(current,"%d",cursor_on);
	AT(mid_window_title_row+1,accs_menu_col+2)
	printf("%s",current);

}


void accs_up_arrow()
{
		int num_in_window;

		num_in_window=prog_defaults.progs_win*prog_defaults.accs_win_width;		


/* at first entry */
/* at middle entry in middle */
/* at middle entry at top of window */


	if(logical_accs_cursor<=1) /* at first entry */
					BELL
	else
	{
		if(accs_cursor<=1)
		{
			old_accs_cursor=accs_cursor;
			accs_cursor=1;


				if(prog_defaults.accs_paging==SCROLLING)
				{
					logical_accs_cursor--;
					first_acc_on_screen--;
				}
				else
				{
					first_acc_on_screen-=num_in_window;
					logical_accs_cursor--;
					if(logical_accs_cursor<num_in_window)
						accs_cursor=logical_accs_cursor;
					else
						accs_cursor=num_in_window;
				}

				if(first_acc_on_screen<1)
					first_acc_on_screen=1;
				if(logical_accs_cursor<1)
					logical_accs_cursor=1;

			print_progs(accs,curr_set,first_acc_on_screen);

		}
		else
		{
			old_accs_cursor=accs_cursor;
			accs_cursor--;
			logical_accs_cursor--;
			
		}
		print_accs_title(logical_accs_cursor);
		remove_cursor(current_window,old_accs_cursor);	
		draw_cursor(current_window,accs_cursor);
	}

}

void accs_down_arrow()
{
		int num_in_window;

		num_in_window=prog_defaults.progs_win*prog_defaults.accs_win_width;		

/* last entry */
/* middle entry at end */
/* middle entry in middle */

	if(logical_accs_cursor>=total_accs)
					BELL
	else
	{
		if(accs_cursor>=num_in_window)
		{

				accs_cursor=num_in_window;
				old_accs_cursor=accs_cursor;

			if(prog_defaults.accs_paging==SCROLLING)
			{
				first_acc_on_screen++;
				logical_accs_cursor++;
			}
			else
			{
				logical_accs_cursor++;
				first_acc_on_screen+=num_in_window;
				accs_cursor=1;
			}

			if(first_acc_on_screen>total_accs)
				first_acc_on_screen=total_accs-num_in_window;
			if(first_acc_on_screen<1)
				first_acc_on_screen=1;

			if(logical_accs_cursor>total_accs)
				logical_accs_cursor=total_accs;

			print_progs(accs,curr_set,first_acc_on_screen);

		}
		else
		{
			logical_accs_cursor++;
			old_accs_cursor=accs_cursor;
			accs_cursor++;
		}
		print_accs_title(logical_accs_cursor);
		remove_cursor(current_window,old_accs_cursor);	
		draw_cursor(current_window,accs_cursor);
	}	
}

void accs_right_arrow()
{
		int num_in_window;
		int column;
		num_in_window=prog_defaults.progs_win*prog_defaults.accs_win_width;		
		column=(accs_cursor-1)/prog_defaults.progs_win;


/* middle column */
/* middle column with blank to the right */
/* last column */

	if(column+1>=prog_defaults.accs_win_width) /* need to page */
	{
		if(first_acc_on_screen+accs_cursor+prog_defaults.progs_win<=total_accs+1)
		{
			if(accs_cursor+prog_defaults.progs_win>num_in_window)
			{
				old_accs_cursor=accs_cursor;
				first_acc_on_screen+=prog_defaults.progs_win;
				logical_progs_cursor+=prog_defaults.progs_win;
			}
			else
			{
				logical_accs_cursor+=prog_defaults.progs_win;
				old_accs_cursor=accs_cursor;
				accs_cursor+=prog_defaults.progs_win;
			}

			print_progs(accs,curr_set,first_acc_on_screen);
			print_accs_title(logical_accs_cursor);
			remove_cursor(current_window,old_accs_cursor);	
			draw_cursor(current_window,accs_cursor);
		}	
		else
			BELL
	}
	else
	{
		if(first_acc_on_screen+accs_cursor+prog_defaults.progs_win<=total_accs+1)
		{

				logical_accs_cursor+=prog_defaults.progs_win;
				old_accs_cursor=accs_cursor;
				accs_cursor+=prog_defaults.progs_win;

			print_accs_title(logical_accs_cursor);
			remove_cursor(current_window,old_accs_cursor);	
			draw_cursor(current_window,accs_cursor);
		}	
		else
			BELL
	}
}

void accs_left_arrow()
{
		int num_in_window;
		int column;
		num_in_window=prog_defaults.progs_win*prog_defaults.accs_win_width;		
		column=(accs_cursor-1)/prog_defaults.progs_win;


/* middle column */
/* middle column with blank to the right */
/* last column */

	if(column==0) /* need to page */
	{
		if(first_acc_on_screen-prog_defaults.progs_win>0)
		{


				logical_accs_cursor-=prog_defaults.progs_win;
				first_acc_on_screen-=prog_defaults.progs_win;
				old_accs_cursor=accs_cursor;



			print_progs(accs,curr_set,first_acc_on_screen);
			print_accs_title(logical_accs_cursor);
			remove_cursor(current_window,old_accs_cursor);	
			draw_cursor(current_window,accs_cursor);
		}	
		else
			BELL
	}
	else
	{

				logical_accs_cursor-=prog_defaults.progs_win;
				old_accs_cursor=accs_cursor;
				accs_cursor-=prog_defaults.progs_win;

			print_accs_title(logical_accs_cursor);
			remove_cursor(current_window,old_accs_cursor);	
			draw_cursor(current_window,accs_cursor);

	}
}

void accs_paging()
{
		int num_in_window;
		int column;
		num_in_window=prog_defaults.progs_win*prog_defaults.accs_win_width;		
		column=(accs_cursor-1)/prog_defaults.progs_win;

		if(first_acc_on_screen+num_in_window<total_accs+1)
		{

				first_acc_on_screen+=num_in_window;
				logical_accs_cursor+=num_in_window;

				if(logical_accs_cursor>total_accs)
					logical_accs_cursor=total_accs;

				old_accs_cursor=accs_cursor;
				accs_cursor=logical_accs_cursor-first_acc_on_screen;
				accs_cursor++;

				print_accs(accs,curr_set,first_acc_on_screen);
				print_accs_title(logical_accs_cursor);
				remove_cursor(current_window,old_accs_cursor);	
				draw_cursor(current_window,accs_cursor);
		}	
		else
			BELL

}

void accs_paging_up()
{
		int num_in_window;
		int column;
		num_in_window=prog_defaults.progs_win*prog_defaults.accs_win_width;		
		column=(accs_cursor-1)/prog_defaults.progs_win;

		if(first_acc_on_screen>1)
		{

				first_acc_on_screen-=num_in_window;
				logical_accs_cursor-=num_in_window;

				if(logical_accs_cursor<1)
					logical_accs_cursor=1;
		
				if(first_acc_on_screen<1)
					first_acc_on_screen=1;

				old_accs_cursor=accs_cursor;
				accs_cursor=logical_accs_cursor-first_acc_on_screen;
				accs_cursor++;

				print_accs(accs,curr_set,first_acc_on_screen);
				print_accs_title(logical_accs_cursor);
				remove_cursor(current_window,old_accs_cursor);	
				draw_cursor(current_window,accs_cursor);
		}	
		else
			BELL

}


void accs_toggle_key( void )
{

	FILELIST *flp;
	int loop;

	loop=1;
	flp=accs;

	while(flp!=NULL && loop!=logical_accs_cursor)
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
	print_accs(accs,curr_set,first_acc_on_screen);
	
}

int accs_main_loop( int *shift_key )
{

/*		long k;*/
		int u,l,s;

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
			accs_up_arrow();
		else
		{
			if(u==prog_defaults.page_key_high || (u==0x50 && s==2))
				accs_paging();
			else
			{
				if(u==0x50 && s!=2)
					accs_down_arrow();
				else
				{
					if(u==0x4D)
						accs_right_arrow();
					else
					{
						if(u==0x4B)
							accs_left_arrow();
						else
						{
							if(u==prog_defaults.toggle_key_high)
							{
								if(curr_set==NULL)
									sets=new_set_key( sets );
								else
									accs_toggle_key();
							}
							else
							{
								if(u==0x48 && s==2)
									accs_paging_up();
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

void accs_bottom_title()
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
