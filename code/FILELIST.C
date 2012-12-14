#include "filelist.h"
#include "options.h"

void print_progs( FILELIST *progs, SET *curr_set, int first)
{
	FILELIST *temp;
	int count=1;
	int row_loop, col_loop;
	int progs_left_char=auto_menu_col+2;
/*	char pause[]={13};
	char resume[]={11};
*/
	temp=progs;

/*	Ikbdws(0,pause);*/

	while(count<first && temp!=NULL)
	{
		temp=temp->right;
		count++;
	}

	for(col_loop=0; col_loop<prog_defaults.progs_win_width; col_loop++)
	{
		for(row_loop=0; row_loop<prog_defaults.progs_win; row_loop++)
		{
			AT(mid_window_first_item_row+row_loop, progs_left_char+(col_loop*9))
			if(temp!=NULL)
			{
				if(temp->on_off==1) /*in_set(temp->name,curr_set)*/
				{
					printf("        ");
					AT(mid_window_first_item_row+row_loop, progs_left_char+(col_loop*9))
					REVERSE_VIDEO printf("%s",temp->name); NORMAL_VIDEO
				}
				else
				{
					printf("        ");
					AT(mid_window_first_item_row+row_loop, progs_left_char+(col_loop*9))
					printf("%s",temp->name);
				}

				temp=temp->right;
			}
			else
			{
				printf("        ");
			}
		}
	}
/*	Ikbdws(0,resume);*/

}

void print_accs( FILELIST *accs, SET *curr_set, int first)
{
	FILELIST *temp;
	int count=1;
	int row_loop, col_loop;
	int progs_left_char=accs_menu_col+2;

	temp=accs;

/*	AT(0,0)
	printf("PRINT ACCS START");
*/
	while(count<first && temp!=NULL)
	{
		temp=temp->right;
		count++;
	}
	for(col_loop=0; col_loop<prog_defaults.accs_win_width; col_loop++)
	{
		for(row_loop=0; row_loop<prog_defaults.progs_win; row_loop++)
		{
			AT(mid_window_first_item_row+row_loop, progs_left_char+(col_loop*9))
			if(temp!=NULL)
			{
				if(temp->on_off==1) /*in_set(temp->name,curr_set)*/
				{
					REVERSE_VIDEO printf("%s",temp->name); NORMAL_VIDEO
				}
				else
				{
					printf("%s",temp->name);
				}

				temp=temp->right;
			}
			else
			{
				printf("        ");
			}
		}
	}
/*	AT(0,0)
	printf("PRINT ACCS END");*/
}

FILELIST *build_list(char *path, char *type, short attr)
{
	FILELIST *fl;
	FILELIST *head;
	FILELIST *last;
	struct FILEINFO dta;
	char *filenamep1,*filenamep2;

	head=NULL;
	fl=NULL;
	last=NULL;

	strcat(path,type);

	Fsetdta(&dta);
	if( !Fsfirst(path,attr))
	{
		do{
				fl=(FILELIST *)malloc(sizeof(FILELIST));

				if(fl==NULL)
				{
					printf("ERROR: not enough memory to build file list %s\n",type);
					exit(1);
				}

				fl->left=NULL;
				fl->right=NULL;
				fl->on_off=0;


				filenamep1=dta.name;
				filenamep2=fl->name;
				while(*filenamep1!='.')
				{
					*filenamep2=*filenamep1;
					filenamep1++;
					filenamep2++;
				}
				*filenamep2='\0';

				filenamep2=fl->ext;
				while(*filenamep1!='\0')
				{
					*filenamep2=*filenamep1;
					filenamep1++;
					filenamep2++;
				}
				*filenamep2='\0';

				fl->attr=dta.attr;

				if(head==NULL)
				{
					head=fl;
				}

				if(last==NULL)
				{
					last=fl;
				}
				else
				{
					last->right=fl;
					fl->left=last;
					last=fl;
				}

		}while(!Fsnext());
	}
	return(head);
}

void rename_progs_and_accs( int verbose_flag )
{
/*	SMALLFILE *sfp;*/
/*	OTHER_FILES *ofp;*/
	FILELIST *flp;
	char *cp;
	long ferror;
	char temp_file[FMSIZE];
	char temp_file2[FMSIZE];

if(curr_set!=NULL)
{
	remove_extension(prog_defaults.auto_path);
	cp=prog_defaults.auto_path;
	
	flp=prgs;
	while(flp!=NULL)
	{
		if(flp->on_off==1)
		{
/*			sprintf(temp_file,"%s%s.PRX",cp,flp->name);
			ferror=Fattrib(temp_file,0,0);*/

			if(!strcmp(".PRX",flp->ext) /*&& (flp->attr&0x01==0)*/)
			{

/*printf("renameing %s%s.PRX to %s%s.PRG\n",cp,flp->name,cp,flp->name);
*/				sprintf(temp_file,"%s%s.PRX",cp,flp->name);
				sprintf(temp_file2,"%s%s.PRG",cp,flp->name);

				ferror=Frename(0,temp_file,temp_file2);
				if(/*verbose_flag && */ferror!=0)
					printf("could not rename %s\n",temp_file);
			}
/*			else
printf("won't %s%s.PRX to %s%s.PRG\n",cp,flp->name,cp,flp->name);
*/		}
		else
		{
/*			sprintf(temp_file,"%s%s.PRG",cp,flp->name);
			ferror=Fattrib(temp_file,0,0);*/
			if(!strcmp(".PRG",flp->ext) /*&& (flp->attr&0x01==0)*/)
			{


/*printf("renameing %s%s.PRG to %s%s.PRX\n",cp,flp->name,cp,flp->name);
*/				sprintf(temp_file,"%s%s.PRG",cp,flp->name);
				sprintf(temp_file2,"%s%s.PRX",cp,flp->name);
				ferror=Frename(0,temp_file,temp_file2);
				if(/*verbose_flag && */ferror!=0)
					printf("could not rename %s\n",temp_file);
			}
/*			else
printf("wont %s%s.PRG to %s%s.PRX\n",cp,flp->name,cp,flp->name);
*/
		}

		flp=flp->right;
	}

	remove_extension(prog_defaults.accs_path);
	cp=prog_defaults.accs_path;
	flp=accs;
	while(flp!=NULL)
	{
		if(flp->on_off==1)
		{
/*			sprintf(temp_file,"%s%s.ACX",cp,flp->name);
			ferror=Fattrib(temp_file,0,0);*/
			if(!strcmp(".ACX",flp->ext) /*&& (flp->attr&0x01==0)*/)
			{

				

				sprintf(temp_file,"%s%s.ACX",cp,flp->name);
				sprintf(temp_file2,"%s%s.ACC",cp,flp->name);
				ferror=Frename(0,temp_file,temp_file2);
				if(/*verbose_flag && */ferror!=0)
					printf("could not rename %s\n",temp_file);
			}
		}
		else
		{
/*			sprintf(temp_file,"%s%s.ACC",cp,flp->name);
			ferror=Fattrib(temp_file,0,0);*/
			if(!strcmp(".ACC",flp->ext) /*&& (flp->attr&0x01==0)*/)
			{

				sprintf(temp_file,"%s%s.ACC",cp,flp->name);
				sprintf(temp_file2,"%s%s.ACX",cp,flp->name);
				ferror=Frename(0,temp_file,temp_file2);
				if(/*verbose_flag && */ferror!=0)
					printf("could not rename %s\n",temp_file);
			}
		}

		flp=flp->right;
	}

	
}

}

void copy_file(FILE *in, FILE *out, char *buffer, int buffer_size)
{
	int n_chars;
	while((n_chars=fread(buffer,sizeof(char),buffer_size,in))>0)
	{
		fwrite(buffer,sizeof(char),n_chars,out);
	}
}

void process_others(int verbose_flag)
{
	OTHER_FILES *otf;
	FILE *in,*out;
	char *copy_buffer,*cp;
/*	int ferror;*/

#define copy_buffer_size	500


if(curr_set!=NULL)
{
	otf=curr_set->others;
	copy_buffer=NULL;

	while(otf!=NULL)
	{

		if(otf->from[0]=='!')
		{
			out=fopen(otf->to,"w");
			cp=otf->from+sizeof(char);

			if(out!=NULL)
			{
				fprintf(out,"%s\n",cp);
				fclose(out);
			}
			else
			{
			/*	if(verbose_flag==1)*/
					printf("ERROR cannot write %s to\n\t\t%s\n",cp,otf->to);
			}
		}
		else
		{

			out=fopen(otf->to,"w");

			if(out!=NULL)
			{
				in=fopen(otf->from,"r");
				if(in!=NULL)
				{
					if(copy_buffer==NULL)
					{
						copy_buffer=(char *)malloc(copy_buffer_size+2);
						if(copy_buffer==NULL && verbose_flag==1)
						{
							printf("ERROR COULD NOT CREATE COPY BUFFER\n");
						}
					}

					if(copy_buffer!=NULL)
					{
						copy_file(in,out,copy_buffer,copy_buffer_size);
						printf("Copying: %s to %s\n",otf->from,otf->to);
					}
					fclose(in);
				}
				else
				{
					if(verbose_flag==1)
						printf("ERROR could not open %s\n",otf->from);
				}
				fclose(out);
			}
			else
			{
				if(verbose_flag==1)
					printf("ERROR could not open %s\n",otf->to);
			}
		}
		otf=otf->right;
	}
}
}			

void consistency_check( SET *first_set, FILELIST *progs, int progs_or)
{
	int found;
	FILELIST *flp;
	SMALLFILE *sfp;

	while(first_set!=NULL)
	{
		if(progs_or)
			sfp=first_set->progs;
		else
			sfp=first_set->accs;

		while(sfp!=NULL)
		{
			flp=progs;
			found=0;

			while(flp!=NULL && found==0)
			{
				if(!strcmp(sfp->name,flp->name))
					found=1;

				flp=flp->right;
			}

			if(found==0)
			{
				if(sfp->left==NULL)
					first_set->progs=sfp->right;
				else
					((SMALLFILE *)sfp->left)->right=sfp->right;

				free(sfp);
			}

			sfp=sfp->right;
		}

		first_set=first_set->right;
	}
}

	
