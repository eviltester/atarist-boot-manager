#include "vt52.h"
#include "progs.h"
#include "display.h"
#include "filelist.h"
#include "edit.h"
#include "defaults.h"
#include "sets.h"
#include "accs.h"
#include "fileform.h"
#include "options.h"
#include "other.h"

short col1;
short col2;
short col3;
int old_resolution;

/*#define TESTING
*/
/*
void update_time()
{
	size_t temp_sizet;
	time_t temp_time;
	struct tm *tmpoint;

	time(&temp_time);
	tmpoint=gmtime(&temp_time);

	temp_sizet= strftime(altime,9,"%X",tmpoint);
}

void update_date()
{
	size_t temp_sizet;
	time_t temp_time;
	struct tm *tmpoint;

	time(&temp_time);
	tmpoint=gmtime(&temp_time);

	temp_sizet= strftime(aldate,9,"%x",tmpoint);
}
*/

				
										


int main_loop( void )
{

		long k;
		int u;
		int l;
		int s;

/*		int num_in_window;
		void (*draw_func)();
		void (*title_func)();
		void *print_thing;*/
	
	k=0;
	u=0;
	l=0;
	s=0;

	while(u!=prog_defaults.abort_key_high)
	{
	


		if(u==prog_defaults.options_key_high 		/*OPTIONS SCREEN*/
			)
			{
				options_screen();
				draw_screen();
			}		

		if(u==prog_defaults.help_key_high 		/*HELP SCREEN*/
			)
			{
				help_screen();
				draw_screen();
			}	

		if(u==prog_defaults.switch_key_high
			)
			{
				old_window=current_window;
				current_window++;
				if(current_window>4)
					current_window=1;

				draw_old_window_title(old_window);
				switch(old_window)
				{
				case 1:
					remove_cursor(old_window,progs_cursor);
					break;	
				case 2:
					remove_cursor(old_window,accs_cursor);
					break;	
				case 3:
					remove_cursor(old_window,sets_cursor);
					break;	
				case 4:
					remove_cursor(old_window,other_cursor);
					break;	
				}
				switch(current_window)
				{
				case AUTO:
					draw_cursor(current_window,progs_cursor);
					progs_bottom_title();
					break;	
				case ACCS:
					draw_cursor(current_window,accs_cursor);
					accs_bottom_title();
					break;	
				case SETS:
					draw_cursor(current_window,sets_cursor);
					sets_bottom_title();
					break;	
				case OTHER:
					draw_cursor(current_window,other_cursor);
					other_bottom_title();
					break;	
				}
				draw_new_window_title(current_window);

			}

			switch(current_window)
			{
			case AUTO:
					u=progs_main_loop( &s);
					break;	
				case ACCS:
					u=accs_main_loop( &s);
					break;	
				case SETS:
					u=sets_main_loop( &s);
					break;	
				case OTHER:
					u=other_main_loop( &s);
					break;	
			}

	}

		set_set_from_progs(curr_set, prgs);
		set_set_from_accs( curr_set, accs);
		if(curr_set!=NULL)
			curr_set->others=others;

/*		printf("\n %d \n",s); */
	if(s==2)
		return 0;
	else 
		return 1;
}
/*
int oconterm;

int conset(void)
{
	oconterm=*(char *)0x484;
	*(char *)0x484|=1<<3;
}

int conunset(void)
{
	*(char *)0x484=oconterm;
}
*/

void main( void );

void main( )
{
/*	int loop;*/
	FILELIST *fl;
	FILE *fp;
	SET *sp;
	char *cp;
	char curr_path[FMSIZE];
	int ferror;
	long fatt;
	int save_sets_flag=1;
	int verbose_flag=1;
/*	int rename_the_lot=1;*/
	char defs_path[FMSIZE];
	char defs_path_bak[FMSIZE];

/*	int s,u,l;*/


	getcd(0,curr_path);


#ifndef TESTING
	cp=curr_path;
	while(*cp!='\0')
		cp++;

	cp=cp-5;
	if(strcmp(cp,"\\AUTO"))
		strcat(curr_path,"\\AUTO");
#endif


	#ifndef TESTING
		sprintf(defs_path,"%s\\BOOTSETS.DEF",curr_path);
		sprintf(defs_path_bak,"%s\\BOOTSETS.BAK",curr_path);
/*	#else
		sprintf(defs_path,"I:\\BOOT\\BOOTSETS.DEF");
		sprintf(defs_path_bak,"I:\\BOOT\\BOOTSETS.BAK",curr_path);
*/
	#endif

	prgs=NULL;
	accs=NULL;
	sets=NULL;

	logical_progs_cursor=0;
	logical_accs_cursor=0;
	logical_sets_cursor=0;
	logical_other_cursor=0;

	progs_cursor=0;
	accs_cursor=0;
	sets_cursor=0;
	other_cursor=0;

	old_progs_cursor=0;
	old_accs_cursor=0;
	old_sets_cursor=0;
	old_other_cursor=0;

	first_prog_on_screen=0;
	first_acc_on_screen=0;
	first_set_on_screen=0;
	first_other_on_screen=0;
	
	curr_set=NULL;

	others=NULL;
	curr_other=NULL;

	current_window=1;
	old_window=1;

/*	long key;
	int upk,lowk;
*/
/*	while(!Bconstat(2) && u!=)
		{
			key=Bconin(2);
			upk=(int)(key>>16);
			lowk=(int)(key%256);
			printf("%d %d\n",upk,lowk);

		}
*/

	CLEAR_SCREEN
	set_defaults();


/*	u=0;
	while(u!=prog_defaults.abort_key_high)
		{

			while(!Bconstat(2));
			get_key(&s,&u,&l);

			printf("s %d u %d l %d\n",s,u,l);

		}
*/

	fp=fopen(defs_path,"r");
	if(fp!=NULL)
	{
/*		printf("\n\nOPENED AND READING %s\n",defs_path);
		getchar();
*/		curr_set=load_sets( fp );
		fclose(fp);
		sets=curr_set;
	}
	else
	{
		printf("\n\nERROR COULD NOT OPEN SETS FILE %s\n",defs_path);
		BELL
		printf("\nPRESS ANY KEY\n");
			while(!Bconstat(2));
			Bconin(2);
	}

	cp=prog_defaults.auto_path;
	while(*cp!='\0')
		cp++;

	cp--;
	if(*cp!='\\')
	{
		cp++;
		*cp='\\';
		cp++;
		*cp='\0';
	}

	cp=prog_defaults.accs_path;
	while(*cp!='\0')
		cp++;

	cp--;
	if(*cp!='\\')
	{
		cp++;
		*cp='\\';
		cp++;
		*cp='\0';
	}

	prgs=build_list(prog_defaults.auto_path,"*.PR?",0);
	accs=build_list(prog_defaults.accs_path,"*.AC?",0);

	consistency_check(sets, prgs, 1);
	consistency_check(sets, accs, 0);

	total_progs=0;
	fl=prgs;
	while(fl)
	{
		total_progs++;
		fl=fl->right;
	}

	if(total_progs>0)
	{
		logical_progs_cursor=1;
		progs_cursor=1;
		old_progs_cursor=1;
		first_prog_on_screen=1;
	}

	total_accs=0;
	fl=accs;
	while(fl)
	{
		total_accs++;
		fl=fl->right;
	}

	if(total_accs>0)
	{
		logical_accs_cursor=1;
		accs_cursor=1;
		old_accs_cursor=1;
		first_acc_on_screen=1;
	}

	total_sets=0;
	sp=sets;
	while(sp)
	{
		total_sets++;
		sp=sp->right;
	}

	if(total_sets>0)
	{
		logical_sets_cursor=1;
		sets_cursor=1;
		old_sets_cursor=1;
		first_set_on_screen=1;
	}

	set_other_counts();
/*	getchar();*/

	set_progs_on_off_from_set(curr_set, prgs);
	set_accs_on_off_from_set(curr_set,accs);
	if(curr_set!=NULL)
		others=curr_set->others;
	else
		others=NULL;

	calculate_screen_sizes();
	startup_screen();

	Supexec(conset);

	draw_screen();
	save_sets_flag=main_loop();

	CLEAR_SCREEN
	
	if(save_sets_flag)
	{
		
		fatt=Fattrib(defs_path_bak,0,0);

		if(fatt>=0)
			Fdelete(defs_path_bak);

		ferror=Frename(0,defs_path,defs_path_bak);
		if(verbose_flag && ferror!=0)
		{
			BELL
			printf("Could not rename .DEF file\n");
		}

		fp=fopen(defs_path,"w");
		if(fp!=NULL)
		{
			save_sets(fp);
			fclose(fp);
		}
		else
		{
			BELL
			printf("Could not save .DEF file\n");
		}

/*		if(rename_the_lot==1)
		{*/

			rename_progs_and_accs(verbose_flag);		
			process_others(verbose_flag);

/*		}*/
	}
	
	Supexec(conunset);

	free(line_buffer);


	if(/*prog_defaults.*/old_resolution==0 /* && prog_defaults.medium_res==1 */)
	{
		Setscreen((void *)-1,(void *)-1,(short)0);
		Setcolor(1,col1);
		Setcolor(2,col2);
		Setcolor(3,col3);	
	}


}
