#include "sets.h"
#include "edit.h"
#include "display.h"
#include "global.h"
#include "other.h"

void sets_window( void )
{

	int width;
	int loop;

	width=SETS_NAME_SIZE+ARROW_BORDER+ARROW_BORDER+LINE_BORDER+
					LINE_BORDER;

	/* accs title */

	centre_text("SETS",line_buffer,width,' ');
	AT(mid_window_title_row,sets_menu_col)
	printf("%s",line_buffer);

	centre_text("--",line_buffer,width,'-');
	AT(mid_window_title_row+1,sets_menu_col)
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
		AT(mid_window_first_item_row+loop,sets_menu_col)
		printf("%s",line_buffer);
	}

	centre_text("--",line_buffer,width,'-');
	line_buffer[0]='+';
	line_buffer[width-1]='+';
	AT(mid_window_first_item_row+prog_defaults.progs_win,sets_menu_col)
	printf("%s",line_buffer);

}


void print_sets_in_window( SET *sets )
{
	SET *temp;
	int loop;

	temp=sets;

	loop=1; 
	while(temp!=NULL && loop<first_set_on_screen)
	{
		 loop++;
		temp=temp->right;
	}

	

	for(loop=0;loop<prog_defaults.progs_win;loop++)
	{

		if(temp!=NULL)
		{

			if(temp==curr_set)
			{
				AT(mid_window_first_item_row+loop, sets_menu_col+2)
				printf("            ");
				AT(mid_window_first_item_row+loop, sets_menu_col+2)
				REVERSE_VIDEO 
				printf("%s",temp->set_name); 
				NORMAL_VIDEO
			}
			else
			{
				AT(mid_window_first_item_row+loop, sets_menu_col+2)
				printf("            ");
				AT(mid_window_first_item_row+loop, sets_menu_col+2)
				printf("%s",temp->set_name); 
			}

		temp=temp->right;
		}
		else
		{
				AT(mid_window_first_item_row+loop, sets_menu_col+2)
				printf("            ");
		}
	}
}

void print_sets_title( int logical_sets_cursor )
{

	int width;
/*	int loop;*/
	char total[4];
/*	char current[4];*/

	width=SETS_NAME_SIZE+ARROW_BORDER+ARROW_BORDER+LINE_BORDER+
					LINE_BORDER;

	sprintf(total,"%d",total_sets);
	centre_text("--",line_buffer,width,'-');
	AT(mid_window_title_row+1,sets_menu_col)
	line_buffer[0]='+';
	line_buffer[width-1]='+';
	printf("%s",line_buffer);

	AT(mid_window_title_row+1,sets_menu_col+width-2-strlen(total))
	printf("%s",total);


	AT(mid_window_title_row+1,sets_menu_col+2)
	printf("%d",logical_sets_cursor);


}


void sets_up_arrow( void )
{
		int num_in_window;

		num_in_window=prog_defaults.progs_win;		


/* at first entry */
/* at middle entry in middle */
/* at middle entry at top of window */


	if(logical_sets_cursor<=1) /* at first entry */
					BELL
	else
	{
		if(sets_cursor<=1)
		{
			old_sets_cursor=sets_cursor;
			sets_cursor=1;


				if(prog_defaults.sets_paging==SCROLLING)
				{
					logical_sets_cursor--;
					first_set_on_screen--;
				}
				else
				{
					first_set_on_screen-=num_in_window;
					logical_sets_cursor--;
					if(logical_sets_cursor<num_in_window)
						sets_cursor=logical_sets_cursor;
					else
						sets_cursor=num_in_window;
				}

				if(first_set_on_screen<1)
					first_set_on_screen=1;
				if(logical_sets_cursor<1)
					logical_sets_cursor=1;

			print_sets_in_window( sets );

		}
		else
		{
			old_sets_cursor=sets_cursor;
			sets_cursor--;
			logical_sets_cursor--;
			
		}

		print_sets_title(logical_sets_cursor);
		remove_cursor(current_window,old_sets_cursor);	
		draw_cursor(current_window,sets_cursor);
	}

}

void sets_down_arrow( void )
{
		int num_in_window;

		num_in_window=prog_defaults.progs_win;		

/* last entry */
/* middle entry at end */
/* middle entry in middle */

	if(logical_sets_cursor>=total_sets)
					BELL
	else
	{
		if(sets_cursor>=num_in_window)
		{

				sets_cursor=num_in_window;
				old_sets_cursor=sets_cursor;

			if(prog_defaults.sets_paging==SCROLLING)
			{
				first_set_on_screen++;
				logical_sets_cursor++;

			}
			else
			{
				logical_sets_cursor++;
				first_set_on_screen+=num_in_window;
				sets_cursor=1;
			}

			if(first_set_on_screen>total_sets)
				first_set_on_screen=total_sets-num_in_window;
			if(first_set_on_screen<1)
				first_set_on_screen=1;

			if(logical_sets_cursor>total_sets)
				logical_sets_cursor=total_sets;

			print_sets_in_window( sets );

		}
		else
		{
			logical_sets_cursor++;
			old_sets_cursor=sets_cursor;
			sets_cursor++;

		}

		print_sets_title(logical_sets_cursor);
		remove_cursor(current_window,old_sets_cursor);	
		draw_cursor(current_window,sets_cursor);
	}	
}


void select_set( void )
{
	SET *sel_set;
/*	SET *first_set;*/
	int loop;

/*	AT(0,0)
	printf("SELECT 1");
*/

if(sets!=NULL)
{
	sel_set=sets;
	loop=1;

/*	AT(0,0)
	printf("SELECT 2");
*/
	while(loop!=logical_sets_cursor)
	{
		loop++;
		sel_set=sel_set->right;
/*	AT(0,0)
	printf("SELECT 2.%d",loop);
*/
	}

/*	AT(0,0)
	printf("SELECT 3     ");
*/
	if(curr_set!=sel_set)
	{

/*	AT(0,0)
	printf("SELECT 4");
*/
		set_set_from_progs(curr_set, prgs);
		set_set_from_accs( curr_set, accs);

		if(curr_set!=NULL)
			curr_set->others=others;

/*	AT(0,0)
	printf("SELECT 5");
*/
		curr_set=sel_set;
		set_other_counts();

/*	AT(0,0)
	printf("SELECT 6");
*/
		print_sets_in_window( sets );
/*	AT(0,0)
	printf("SELECT 7");
*/
		set_progs_on_off_from_set(curr_set, prgs);
/*	AT(0,0)
	printf("SELECT 8");
*/
		set_accs_on_off_from_set(curr_set,accs);
/*	AT(0,0)
	printf("SELECT 9");
*/

		if(curr_set!=NULL)
			others=curr_set->others;
		else
			others=NULL;

		set_other_counts();
		draw_old_window_title(4);
		print_accs(accs,curr_set,first_acc_on_screen);
/*	AT(0,0)
	printf("SELECT 10");
*/
		print_progs(prgs,curr_set,first_prog_on_screen);
		print_others_in_window(others);

	}
/*	AT(0,0)
	printf("SELECT 11");
*/
}
/*	AT(0,0)
	printf("SELECT 12");
*/
}



int sets_main_loop( int *shift_key )
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
			sets_up_arrow();
		else
		{
			if(u==prog_defaults.new_key_high)
				{
				set_set_from_progs(curr_set, prgs);
				set_set_from_accs( curr_set, accs);
				if(curr_set!=NULL)
					curr_set->others=others;
				set_other_counts();
				sets=new_set_key(sets);
				set_progs_on_off_from_set(curr_set, prgs);
				set_accs_on_off_from_set(curr_set,accs);	
				if(curr_set!=NULL)
					others=curr_set->others;
				else
					others=NULL;
				set_other_counts();
				draw_old_window_title(4);
				print_accs(accs,curr_set,first_acc_on_screen);
				print_progs(prgs,curr_set,first_prog_on_screen);
				print_others_in_window(others);
				
				}
			else
			{
				if(u==prog_defaults.page_key_high || (u==0x50 && s==2))
					sets_paging();
				else
				{
					if(u==0x50 && s!=2)
					{
						sets_down_arrow();
					}
					else
					{
						if(u==prog_defaults.delete_key_high)
						{
							set_set_from_progs(curr_set, prgs);
							set_set_from_accs( curr_set, accs);
							if(curr_set!=NULL)
								curr_set->others=others;
							set_other_counts();
							sets=delete_set(sets,logical_sets_cursor);
							set_progs_on_off_from_set(curr_set, prgs);
							set_accs_on_off_from_set(curr_set,accs);	
							if(curr_set!=NULL)
								others=curr_set->others;
							else
								others=NULL;
							set_other_counts();
							draw_old_window_title(4);
							print_accs(accs,curr_set,first_acc_on_screen);
							print_progs(prgs,curr_set,first_prog_on_screen);
							print_others_in_window(others);
						}
						else
						{
							if(u==prog_defaults.toggle_key_high)
							{
								select_set();
							}
							else
							{
								if(u==0x1C)
								{
									edit_set();
									sets_bottom_title();
								}
								else
								{
									if(u==0x48 && s==2)
										sets_paging_up();
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
}

void sets_bottom_title( void )
{
	
	char temp[80];

	DISCARD_EOL

	if(prog_defaults.columns<=40)
		sprintf( temp,
				"^v SEL-%s NEW-%s DEL-%s ED-ENTER",
				prog_defaults.toggle_key_text,
				prog_defaults.new_key_text,
				prog_defaults.delete_key_text);
	else	
	sprintf(	temp,
				"CURS-^v SELECT-%s PAGE-%s NEW-%s DEL-%s EDIT-RETURN",
				prog_defaults.toggle_key_text,
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

void set_progs_on_off_from_set( SET *set, FILELIST *progs)
{
	FILELIST *fp;

	fp=progs;

	if(set!=NULL)
	{

		while(fp!=NULL)
		{
			if(prog_in_set(fp->name, set))
				fp->on_off=1;
			else
				fp->on_off=0;

			fp=fp->right;
		}
	}
	else
	{
		while(fp!=NULL)
		{
			fp->on_off=0;
			fp=fp->right;
		}
	}
}

SMALLFILE *append_smallfile( SMALLFILE *append, SMALLFILE *list)
{
	SMALLFILE *first;

	first=list;

	if(list==NULL)
	{
		return(append);
	}
	else
	{
		while(list->right!=NULL)
			list=list->right;

		list->right=append;
		append->left=list;

		return(first);
	}
}



void set_set_from_progs( SET *set, FILELIST *progs)
{
	FILELIST *fp;
	SMALLFILE *sfp;
	SMALLFILE *temp;

	fp=progs;

	if(set!=NULL)
	{
		sfp=set->progs;

		/* delete progs first */
		while(sfp!=NULL)
		{
			temp=sfp->right;
			free(sfp);
			sfp=temp;
		}
			
		set->progs=NULL;

		while(fp!=NULL)
		{
			if(fp->on_off==1)
			{
				temp=(SMALLFILE *)malloc(sizeof(SMALLFILE));
				if(temp==NULL)
				{
				AT(bottom_title_row,0)
				REVERSE_VIDEO
				centre_text(" ERROR: NOT ENOUGH MEMORY FOR THIS SET ",line_buffer,prog_defaults.columns,' ');
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
				sets_bottom_title();
				}
				else
				{
					temp->left=NULL;
					temp->right=NULL;
					strcpy(temp->name,fp->name);
	
					set->progs=append_smallfile(temp,set->progs);
				}
			}

			fp=fp->right;
		}
	}
}

void set_set_from_accs( SET *set, FILELIST *accs)
{
	FILELIST *fp;
	SMALLFILE *sfp;
	SMALLFILE *temp;

	fp=accs;

	if(set!=NULL)
	{
		sfp=set->accs;

		/* delete progs first */
		while(sfp!=NULL)
		{
			temp=sfp->right;
			free(sfp);
			sfp=temp;
		}
			
		set->accs=NULL;

		while(fp!=NULL)
		{
			if(fp->on_off==1)
			{
				temp=(SMALLFILE *)malloc(sizeof(SMALLFILE));
				if(temp==NULL)
				{
				AT(bottom_title_row,0)
				REVERSE_VIDEO
				centre_text(" ERROR: NOT ENOUGH MEMORY FOR THIS SET ",line_buffer,prog_defaults.columns,' ');
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
				sets_bottom_title();
				}
				else
				{
					temp->left=NULL;
					temp->right=NULL;
					strcpy(temp->name,fp->name);
	
					set->accs=append_smallfile(temp,set->accs);
				}
			}

			fp=fp->right;
		}
	}
}



int prog_in_set( char *progname, SET *sp)
{
	SMALLFILE *sfp;

	if(sp!=NULL)
	{
		sfp=sp->progs;

		while(sfp!=NULL)
		{
			if(!strcmp(progname,sfp->name))
				return 1;
			sfp=sfp->right;
		}


	}

	return 0;
}

void set_accs_on_off_from_set( SET *set, FILELIST *accs)
{
	FILELIST *fp;

	fp=accs;

	if(set!=NULL)
	{
		while(fp!=NULL)
		{
			if(acc_in_set(fp->name, set))
				fp->on_off=1;
			else
				fp->on_off=0;

			fp=fp->right;
		}
	}
	else
	{
		while(fp!=NULL)
		{
			fp->on_off=0;
			fp=fp->right;
		}
	}
}

int acc_in_set( char *accname, SET *sp)
{
	SMALLFILE *sfp;

	if(sp!=NULL)
	{
		sfp=sp->accs;

		while(sfp!=NULL)
		{
			if(!strcmp(accname,sfp->name))
				return 1;
			sfp=sfp->right;
		}

	}

	return 0;
}

SET *create_set( void )
{
/*	long k;*/
	SET *new_set;

	new_set=(SET *)malloc(sizeof(SET));

	if(new_set==NULL)
	{
		AT(bottom_title_row,0)
		REVERSE_VIDEO
		centre_text(" ERROR: NOT ENOUGH MEMORY FOR A NEW SET ",line_buffer,prog_defaults.columns,' ');
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
		sets_bottom_title();
		
		return NULL;
	}

	new_set->left=NULL;
/*	strcpy( new_set->set_name, "NEW SET" );*/
	new_set->set_name[0]='\0';
	new_set->progs=NULL;
	new_set->accs=NULL;
	new_set->others=NULL;
	new_set->right=NULL;

	return(new_set);
}

SET *append_set_to_list( SET *to_add, SET *list)
{
	SET *first;

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

int valid_set_char( char ch )
{
		if(	isalnum(ch) || ispunct(ch) || isspace(ch) )
		return 1;

	return 0;
}

SET *new_set_key( SET *sets )
{

	SET *temp;

	temp=create_set();

	if(temp!=NULL)
	{
		total_sets++;
		logical_sets_cursor=total_sets;
		old_sets_cursor=sets_cursor;
		curr_set=temp;

		if(logical_sets_cursor!=1)  /* no sets yet */
		{
			if(total_sets>prog_defaults.progs_win)	/* not just 1 screen */
			{
					/* not on this screen */
				if((total_sets-first_set_on_screen+1)>prog_defaults.progs_win)
					{
						if(prog_defaults.sets_paging==SCROLLING)
						{
							first_set_on_screen=total_sets-prog_defaults.progs_win+1;
							sets_cursor=prog_defaults.progs_win;
						}
						else
						{
							first_set_on_screen=total_sets;
							sets_cursor=1;
						}
					}
				else
					{		
						sets_cursor=total_sets-first_set_on_screen+1;
					}
			}
			else
			{
				first_set_on_screen=1;
				sets_cursor=total_sets;
			}
		}
		else
		{
			curr_set=temp;
			old_sets_cursor=1;
			first_set_on_screen=1;
			logical_sets_cursor=1;
			sets_cursor=1;
			total_sets=1;
		}

		sets=append_set_to_list(temp, sets);
		print_sets_in_window( sets );
		print_sets_title(logical_sets_cursor);
		remove_cursor(current_window,old_sets_cursor);	
		draw_cursor(current_window,sets_cursor);
		edit_at(mid_window_first_item_row+sets_cursor-1,
					sets_menu_col+2,
					12,
					12,
					curr_set->set_name,
					'-',
					1,
					valid_set_char,
					0);	

		if(curr_set->set_name[0]=='\0')
			sets=delete_set(sets,logical_sets_cursor);

		sets_bottom_title();
		print_sets_in_window( sets );


		return(sets);
	}
	else
		return NULL;
}

void edit_set( void )
{
	SET *temp;
	int loop;

	temp=sets;

	if(temp!=NULL)
	{
		loop=1;

		while(loop!=logical_sets_cursor)
		{
			loop++;
			temp=temp->right;
		}

		edit_at(mid_window_first_item_row+sets_cursor-1,
					sets_menu_col+2,
					12,
					12,
					temp->set_name,
					'-',
					1,
					valid_set_char,
					0);	
		sets_bottom_title();
		print_sets_in_window( sets );
	}
}

SET *delete_set( SET *sets, int set_number)
{
	SET *del_set;
/*	SET *first_set;*/
	int loop;

if(sets!=NULL)
{
	del_set=sets;
	loop=1;

	while(loop!=set_number)
	{
		loop++;
		del_set=del_set->right;
	}

	if(curr_set==del_set)
	{
		if(del_set->left==NULL)
			curr_set=del_set->right;
		else
			curr_set=del_set->left;

		set_progs_on_off_from_set(curr_set, prgs);
		set_accs_on_off_from_set(curr_set,accs);
		if(curr_set!=NULL)
			others=curr_set->others;
		else
			others=NULL;
	}

	sets=dlte_set(sets, del_set);

	total_sets--;
	if(logical_sets_cursor!=1)
		logical_sets_cursor--;


	if(first_set_on_screen>total_sets)
	{
		if(prog_defaults.sets_paging==SCROLLING)
			first_set_on_screen=total_sets;
		else
			first_set_on_screen=total_sets-prog_defaults.progs_win+1;
	}		

	if(logical_sets_cursor<=first_set_on_screen)
	{
		if(prog_defaults.sets_paging==SCROLLING)
			first_set_on_screen=logical_sets_cursor;
		else
		{
			first_set_on_screen=logical_sets_cursor-prog_defaults.progs_win+1;
			if(first_set_on_screen<0)
			{
				if(total_sets==0)		
					first_set_on_screen=0;
				else
					first_set_on_screen=1;
			}
		}
	}

	old_sets_cursor=sets_cursor;						

	if(total_sets==0)
	{
		logical_sets_cursor=0;
		sets_cursor=0;
	}	
	else
		sets_cursor=logical_sets_cursor-first_set_on_screen+1;


	print_sets_in_window( sets );
	print_sets_title(logical_sets_cursor);
	remove_cursor(current_window,old_sets_cursor);	
	draw_cursor(current_window,sets_cursor);
	return(sets);
}
else
	{
	BELL
	return(NULL);
	}
}

SET *dlte_set( SET *sets, SET *del_set )
{

	SET *first_set;
/*	int loop;*/

	if(sets==del_set)
		first_set=sets->right;
	else
		first_set=sets;

	if(del_set->left!=NULL)
		((SET *)del_set->left)->right=del_set->right;

	if(del_set->right!=NULL)
		((SET *)del_set->right)->left=del_set->left;

	free(del_set);
	return(first_set);

}


void sets_paging()
{
		int num_in_window;
		int column;
		num_in_window=prog_defaults.progs_win;		
		column=1;

		if(first_set_on_screen+num_in_window<total_sets+1)
		{

				first_set_on_screen+=num_in_window;
				logical_sets_cursor+=num_in_window;

				if(logical_sets_cursor>total_sets)
					logical_sets_cursor=total_sets;

				old_sets_cursor=sets_cursor;
				sets_cursor=logical_sets_cursor-first_set_on_screen;
				sets_cursor++;

				print_sets_in_window( sets );
				print_sets_title(logical_sets_cursor);
				remove_cursor(current_window,old_sets_cursor);	
				draw_cursor(current_window,sets_cursor);
		}	
		else
			BELL

}


void sets_paging_up()
{
		int num_in_window;
		int column;
		num_in_window=prog_defaults.progs_win;		
		column=1;

		if(first_set_on_screen>1)
		{

				first_set_on_screen-=num_in_window;
				logical_sets_cursor-=num_in_window;

				if(logical_sets_cursor<1)
					logical_sets_cursor=1;
		
				if(first_set_on_screen<1)
					first_set_on_screen=1;

				old_sets_cursor=sets_cursor;
				sets_cursor=logical_sets_cursor-first_set_on_screen;
				sets_cursor++;

				print_sets_in_window( sets );
				print_sets_title(logical_sets_cursor);
				remove_cursor(current_window,old_sets_cursor);	
				draw_cursor(current_window,sets_cursor);
		}	
		else
			BELL

}
 