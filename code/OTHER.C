#include "other.h"
#include "display.h"
#include "edit.h"
#include "global.h"

void other_window( void )
{

	int width;
	int loop;

	width=prog_defaults.columns;

	/* other title */

/*	centre_text("OTHER",line_buffer,width,'-');
	AT(other_window_title_row,0)
	line_buffer[0]='+';
	line_buffer[width-1]='+';
	printf("%s",line_buffer);
*/
	draw_old_window_title(4);

	for(loop=0;loop<width;loop++)
		line_buffer[loop]=' ';
	line_buffer[loop]='\0';

	line_buffer[0]='|';
	line_buffer[width-1]='|';

	for(loop=0;loop<prog_defaults.other_win;loop++)
	{
		AT(other_window_first_item_row+loop,0)
		printf("%s",line_buffer);
	}

	centre_text("--",line_buffer,width,'-');
	line_buffer[0]='+';
	line_buffer[width-1]='+';
	AT(other_window_first_item_row+prog_defaults.other_win,0)
	printf("%s",line_buffer);

}


int other_main_loop( int *shift_key )
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


		if(u==prog_defaults.new_key_high)
			others=new_other_key(others);
		else
		{
			if(u==0x48 && s!=2)
				other_up_arrow();
			else
			{
				if(u==prog_defaults.page_key_high || (u==0x50 && s==2))
					other_paging();
				else
				{
					if(u==0x50 && s!=2)
						other_down_arrow();
					else
					{
						if(u==0x48 && s==2)
							other_paging_up();
						else
						{
							if(u==prog_defaults.delete_key_high)
							{
								others=delete_other(others,logical_other_cursor);
							}
							else
							{
								if(u==0x1C)
								{
									edit_other();
									other_bottom_title();
									AT(other_window_first_item_row+other_cursor-1,
										prog_defaults.columns-2)
									Bconout(2,'<');
								}
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


void other_bottom_title( void )
{
	
	char temp[80];

	DISCARD_EOL

	if(prog_defaults.columns<=40)
		sprintf( temp,
				"^v NEW-%s DEL-%s EDIT-ENTER",
				prog_defaults.new_key_text,
				prog_defaults.delete_key_text);
	else	
	sprintf(	temp,
				"CURS-^v PAGE-%s NEW-%s DEL-%s EDIT-RETURN",
				prog_defaults.page_key_text,
				prog_defaults.new_key_text,
				prog_defaults.delete_key_text);

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

OTHER_FILES *create_other( void )
{
/*	long k;*/
	OTHER_FILES *new_other;

	new_other=(OTHER_FILES *)malloc(sizeof(OTHER_FILES));

	if(new_other==NULL)
	{
		AT(bottom_title_row,0)
		REVERSE_VIDEO
		centre_text(" ERROR: NOT ENOUGH MEMORY FOR A NEW OTHER ",line_buffer,prog_defaults.columns,' ');
		printf("%s",line_buffer);
		NORMAL_VIDEO
		AT(bottom_title_row+1,0)
		REVERSE_VIDEO
		centre_text(" PRESS ANY KEY ",line_buffer,prog_defaults.columns,' ');
		printf("%s",line_buffer);
		NORMAL_VIDEO	
		while(!Bconstat(2))
			;
		Bconin(2);
		other_bottom_title();
		
		return NULL;
	}

	new_other->left=NULL;
	new_other->from=NULL;
	new_other->to=NULL;
	new_other->right=NULL;

	return(new_other);
}

int valid_to_char( char ch )
{

	if( isalpha(ch) || isdigit(ch) || ch=='_' || ch==':' || ch=='\\' || ch=='.')
		return 1;

	return 0;
}

int valid_from_char( char ch )
{

	if( isalpha(ch) || isdigit(ch) || ch=='_' || ch=='!' || ch==':' || ch=='\\' || ch=='.')
		return 1;

	return 0;
}


OTHER_FILES *new_other_key( OTHER_FILES *others )
{
	int half_size;
	OTHER_FILES *temp;

	temp=create_other();
	half_size=((prog_defaults.columns-6)/2)+1;

	if(temp!=NULL)
	{
		total_others++;
		logical_other_cursor=total_others;
		old_other_cursor=other_cursor;
		curr_other=temp;

		if(logical_other_cursor!=1)  /* no sets yet */
		{
			if(total_others>prog_defaults.other_win)	/* not just 1 screen */
			{
					/* not on this screen */
				if((total_others-first_other_on_screen+1)>prog_defaults.other_win)
					{
						if(prog_defaults.other_paging==SCROLLING)
						{
							first_other_on_screen=total_others-prog_defaults.other_win+1;
							other_cursor=prog_defaults.other_win;
						}
						else
						{
							first_other_on_screen=total_others;
							other_cursor=1;
						}
					}
				else
					{		
						other_cursor=total_others-first_other_on_screen+1;
					}
			}
			else
			{
				first_other_on_screen=1;
				other_cursor=total_others;
			}
		}
		else
		{
			curr_other=temp;
			old_other_cursor=1;
			first_other_on_screen=1;
			logical_other_cursor=1;
			other_cursor=1;
			total_others=1;
		}

		others=append_other_to_list(temp, others);
		print_others_in_window( others );
		print_others_title(logical_other_cursor);
		remove_cursor(current_window,old_other_cursor);	
		draw_cursor(current_window,other_cursor);

		temp->to=(char *)malloc(FILENAME_MAX+1);
		temp->from=(char *)malloc(FILENAME_MAX+1);
		temp->to[0]='\0';
		temp->from[0]='\0';

		edit_at(other_window_first_item_row+other_cursor-1,
					2,
					FILENAME_MAX,
					half_size,
					temp->to,
					'-',
					0,
					valid_to_char,
					0);	

		edit_at(other_window_first_item_row+other_cursor-1,
					half_size+2+1,
					FILENAME_MAX,
					half_size,
					temp->from,
					'-',
					0,
					valid_from_char,
					0);	

		if(temp->from[0]=='\0' || temp->to[0]=='\0')
			others=delete_other(others,logical_other_cursor);

		other_bottom_title();
		print_others_in_window( others );
		AT(other_window_first_item_row+other_cursor-1,prog_defaults.columns-2)
		Bconout(2,'<');
		return(others);
	}
	else
		return NULL;
}



OTHER_FILES *append_other_to_list( OTHER_FILES *to_add, OTHER_FILES *list)
{
	OTHER_FILES *first;

	first=list;

	if(list==NULL)
	{
		return(to_add);
	}
	else
	{
		while(list->right!=NULL)
			list=list->right;

		list->right=to_add;
		to_add->left=list;

		return(first);
	}
}

void print_others_in_window( OTHER_FILES *others )
{
	OTHER_FILES *temp;
	int loop,loop2;
	char *half_buffer;
	int half_size;


	half_size=((prog_defaults.columns-6)/2)+1;
	half_buffer=(char *)malloc(half_size);
	DISCARD_EOL

	temp=others;


	loop=1; 
	while(temp!=NULL && loop<first_other_on_screen)
	{
		loop++;
		temp=temp->right;
	}

	

	for(loop=0;loop<prog_defaults.other_win;loop++)
	{

		if(temp!=NULL)
		{


				AT(other_window_first_item_row+loop, 2);
				CLEAR_EOL
				AT(other_window_first_item_row+loop, prog_defaults.columns-1);
				Bconout(2,'+');
	
				if(temp->to!=NULL && half_buffer!=NULL)
				{
					loop2=0;
					while(loop2<half_size && temp->to[loop2]!='\0')
					{
						half_buffer[loop2]=temp->to[loop2];
						loop2++;
					}
					half_buffer[loop2]='\0';
					AT(other_window_first_item_row+loop, 2);
					printf("%s",half_buffer);
				}

				if(temp->from!=NULL && half_buffer!=NULL)
				{
					loop2=0;
					while(loop2<half_size && temp->from[loop2]!='\0')
					{
						half_buffer[loop2]=temp->from[loop2];
						loop2++;
					}
					half_buffer[loop2]='\0';
					AT(other_window_first_item_row+loop, 2+half_size+1);
					printf("%s",half_buffer);
				}

			temp=temp->right;
		}
		else
		{
				AT(other_window_first_item_row+loop, 2);
				CLEAR_EOL
				AT(other_window_first_item_row+loop, prog_defaults.columns-1);
				Bconout(2,'+');
		}
	}

	WRAP_EOL
}


void print_others_title( int logical_others_cursor )
{

	int width;
/*	char small_text[20];*/
	char *cp;
/*	int loop;*/
	char total[4];
/*	char current[4];*/

	width=prog_defaults.columns;

/*	sprintf(total,"%d",total_sets);*/

/*	if(curr_window==OTHER)
		sprintf(small_text,"%sOTHER%s",REV_VID,NORM_VID);
	else
		sprintf(small_text,"OTHER"*/
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


}

OTHER_FILES *delete_other( OTHER_FILES *others, int set_number)
{
	OTHER_FILES *del_other;
/*	SET *first_set;*/
	int loop;

if(others!=NULL)
{
	del_other=others;
	loop=1;

	while(loop!=set_number)
	{
		loop++;
		del_other=del_other->right;
	}

	if(curr_other==del_other)
	{
		if(del_other->left==NULL)
			curr_set=del_other->right;
		else
			curr_set=del_other->left;

	}

	others=dlte_other(others, del_other);

	total_others--;
	if(logical_other_cursor!=1)
		logical_other_cursor--;


	if(first_other_on_screen>total_others)
	{
		if(prog_defaults.other_paging==SCROLLING)
			first_other_on_screen=total_others;
		else
			first_other_on_screen=total_others-prog_defaults.other_win+1;
	}		

	if(logical_other_cursor<=first_other_on_screen)
	{
		if(prog_defaults.other_paging==SCROLLING)
			first_other_on_screen=logical_other_cursor;
		else
		{
			first_other_on_screen=logical_other_cursor-prog_defaults.other_win+1;
			if(first_other_on_screen<0)
			{
				if(total_others==0)		
					first_other_on_screen=0;
				else
					first_other_on_screen=1;
			}
		}
	}

	old_other_cursor=other_cursor;						

	if(total_others==0)
	{
		logical_other_cursor=0;
		other_cursor=0;
	}	
	else
		other_cursor=logical_other_cursor-first_other_on_screen+1;


	print_others_in_window( others );
	print_others_title(logical_other_cursor);
	remove_cursor(current_window,old_other_cursor);	
	draw_cursor(current_window,other_cursor);
	return(others);
}
else
	{
	BELL
	return(NULL);
	}
}

OTHER_FILES *dlte_other( OTHER_FILES *others, OTHER_FILES *del_other )
{

	OTHER_FILES *first_set;
/*	int loop;*/

	if(others==del_other)
		first_set=others->right;
	else
		first_set=others;

	if(del_other->left!=NULL)
		((OTHER_FILES *)del_other->left)->right=del_other->right;

	if(del_other->right!=NULL)
		((OTHER_FILES *)del_other->right)->left=del_other->left;

	if(del_other->from!=NULL)
		free(del_other->from);

	if(del_other->to!=NULL)
		free(del_other->to);

	free(del_other);
	return(first_set);

}

void other_up_arrow()
{
		int num_in_window;

		num_in_window=prog_defaults.other_win;		


/* at first entry */
/* at middle entry in middle */
/* at middle entry at top of window */


	if(logical_other_cursor<=1) /* at first entry */
					BELL
	else
	{
		if(other_cursor<=1)
		{
			old_other_cursor=other_cursor;
			other_cursor=1;


				if(prog_defaults.other_paging==SCROLLING)
				{
					logical_other_cursor--;
					first_other_on_screen--;
				}
				else
				{
					first_other_on_screen-=num_in_window;
					logical_other_cursor--;
					if(logical_other_cursor<num_in_window)
						other_cursor=logical_other_cursor;
					else
						other_cursor=num_in_window;
				}

				if(first_other_on_screen<1)
					first_other_on_screen=1;
				if(logical_other_cursor<1)
					logical_other_cursor=1;

			print_others_in_window( others );

		}
		else
		{
			old_other_cursor=other_cursor;
			other_cursor--;
			logical_other_cursor--;
			
		}

		print_others_title(logical_other_cursor);
		remove_cursor(current_window,old_other_cursor);	
		draw_cursor(current_window,other_cursor);
	}

}

void other_down_arrow()
{
		int num_in_window;

		num_in_window=prog_defaults.other_win;		

/* last entry */
/* middle entry at end */
/* middle entry in middle */

	if(logical_other_cursor>=total_others)
					BELL
	else
	{
		if(other_cursor>=num_in_window)
		{

				other_cursor=num_in_window;
				old_other_cursor=other_cursor;

			if(prog_defaults.other_paging==SCROLLING)
			{
				first_other_on_screen++;
				logical_other_cursor++;

			}
			else
			{
				logical_other_cursor++;
				first_other_on_screen+=num_in_window;
				other_cursor=1;
			}

			if(first_other_on_screen>total_others)
				first_other_on_screen=total_others-num_in_window;
			if(first_other_on_screen<1)
				first_other_on_screen=1;

			if(logical_other_cursor>total_others)
				logical_other_cursor=total_others;

			print_others_in_window( others );

		}
		else
		{
			logical_other_cursor++;
			old_other_cursor=other_cursor;
			other_cursor++;

		}

		print_others_title(logical_other_cursor);
		remove_cursor(current_window,old_other_cursor);	
		draw_cursor(current_window,other_cursor);
	}	
}


void other_paging()
{
		int num_in_window;
		int column;
		num_in_window=prog_defaults.other_win;		
		column=1;

		if(first_other_on_screen+num_in_window<total_others+1)
		{

				first_other_on_screen+=num_in_window;
				logical_other_cursor+=num_in_window;

				if(logical_other_cursor>total_others)
					logical_other_cursor=total_others;

				old_other_cursor=other_cursor;
				other_cursor=logical_other_cursor-first_other_on_screen;
				other_cursor++;

				print_others_in_window( others );
				print_others_title(logical_other_cursor);
				remove_cursor(current_window,old_other_cursor);	
				draw_cursor(current_window,other_cursor);
		}	
		else
			BELL

}


void other_paging_up()
{
		int num_in_window;
		int column;
		num_in_window=prog_defaults.other_win;		
		column=1;

		if(first_other_on_screen>1)
		{

				first_other_on_screen-=num_in_window;
				logical_other_cursor-=num_in_window;

				if(logical_other_cursor<1)
					logical_other_cursor=1;
		
				if(first_other_on_screen<1)
					first_other_on_screen=1;

				old_other_cursor=other_cursor;
				other_cursor=logical_other_cursor-first_other_on_screen;
				other_cursor++;

				print_others_in_window( others );
				print_others_title(logical_other_cursor);
				remove_cursor(current_window,old_other_cursor);	
				draw_cursor(current_window,other_cursor);
		}	
		else
			BELL

}

void edit_other( void )
{
	OTHER_FILES *temp;
	int loop;
	int half_size;

	half_size=((prog_defaults.columns-6)/2)+1;

	temp=others;

	if(temp!=NULL)
	{
		loop=1;

		while(loop!=logical_other_cursor)
		{
			loop++;
			temp=temp->right;
		}

		edit_at(other_window_first_item_row+other_cursor-1,
					2,
					FILENAME_MAX,
					half_size,
					temp->to,
					'-',
					0,
					valid_to_char,
					0);	

		edit_at(other_window_first_item_row+other_cursor-1,
					half_size+2+1,
					FILENAME_MAX,
					half_size,
					temp->from,
					'-',
					0,
					valid_from_char,
					0);	

		other_bottom_title();
		print_others_in_window( others );
	}
}

void set_other_counts( void )
{
	OTHER_FILES *fl;

	total_others=0;
	if(curr_set!=NULL)
		fl=curr_set->others;
	else
		fl=NULL;

	while(fl)
	{
		total_others++;
		fl=fl->right;
	}

	if(total_others>0)
	{
		logical_other_cursor=1;
		other_cursor=1;
		old_other_cursor=1;
		first_other_on_screen=1;
	}
	else
	{
		logical_other_cursor=0;
		other_cursor=0;
		old_other_cursor=0;
		first_other_on_screen=0;
	}
}

