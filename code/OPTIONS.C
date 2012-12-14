#include "options.h"
#include "edit.h"
#include "display.h"



void print_on_off_same(int y, int x, int reverse)
{
	if(reverse==1)
		REVERSE_VIDEO
	
		AT(y,x+17)
		printf("ON");
		NORMAL_VIDEO

	if(reverse==2)
		REVERSE_VIDEO

		AT(y,x+25)
		printf("OFF");
		NORMAL_VIDEO

	if(reverse==3)
		REVERSE_VIDEO

		AT(y,x+31)
		printf("SAME");
		NORMAL_VIDEO
}

void print_paging_scrolling(int y, int x, int reverse)
{
	if(reverse==1)
		REVERSE_VIDEO
	
		AT(y,x+18)
		printf("PAGING");
		NORMAL_VIDEO

	if(reverse==2)
		REVERSE_VIDEO

		AT(y,x+27)
		printf("SCROLLING");
		NORMAL_VIDEO

	
}

void print_option(int y, int x, int rubout, int show)
{
	char l,r;
	int loop;
	int toggle;

	l=' ';
	r=' ';
	toggle=rubout;

for(loop=0;loop<2;loop++)
	{
	switch(toggle)
	{
	case 0: /*New Progs*/
			AT(y,x)
			Bconout(2,l);
			AT(y,x+9)
			Bconout(2,r);
			break;
	case 1: /*New Accs*/
			AT(y+1,x)
			Bconout(2,l);
			AT(y+1,x+9)
			Bconout(2,r);
			break;
	case 2: /*Auto Window*/
			AT(y+3,x)
			Bconout(2,l);
			AT(y+3,x+12)
			Bconout(2,r);
			break;
	case 3: /*Accs Window*/
			AT(y+4,x)
			Bconout(2,l);
			AT(y+4,x+12)
			Bconout(2,r);
			break;
	case 4: /*Sets Window*/
			AT(y+5,x)
			Bconout(2,l);
			AT(y+5,x+12)
			Bconout(2,r);
			break;
	case 5: /*Other Window*/
			AT(y+6,x)
			Bconout(2,l);
			AT(y+6,x+13)
			Bconout(2,r);
			break;
	case 6: /*Auto Path*/
			AT(y+8,x)
			Bconout(2,l);
			AT(y+8,x+10)
			Bconout(2,r);
			break;
	case 7: /*Accs Path*/
			AT(y+11,x)
			Bconout(2,l);
			AT(y+11,x+10)
			Bconout(2,r);
			break;
	case 8: /*Set Keys*/
			AT(y+14,x)
			Bconout(2,l);
			AT(y+14,x+11)
			Bconout(2,r);
			break;
	case 9: /*Resolution Info*/
			AT(y+14,x+21)
			Bconout(2,l);
			AT(y+14,x+39)
			Bconout(2,r);
			break;
	case 10: /*OK*/
			AT(y+16,x+2)
			Bconout(2,l);
			AT(y+16,x+13)
			Bconout(2,r);
			break;
	case 11: /*CANCEL*/
			AT(y+16,x+14)
			Bconout(2,l);
			AT(y+16,x+25)
			Bconout(2,r);
			break;
	case 12: /*SAVE*/
			AT(y+16,x+26)
			Bconout(2,l);
			AT(y+16,x+37)
			Bconout(2,r);
			break;
	}

	l='>';
	r='<';
	toggle=show;
}
}

void remove_extension(char *filename)
{
	char *cp;
	int ext;

	ext=0;
	cp=filename;

	while(*cp!='\0')
		cp++;

	cp--;

	while(*cp!='\\' && cp!=filename)
	{
		if(*cp=='?' || *cp=='*')
			ext=1;
		cp--;
	}

	if(ext==1 && cp!=filename)
	{
		cp++;
		*cp='\0';
	}
}

void options_bottom_title( void )
{
	char temp[60];

	DISCARD_EOL

	sprintf(temp,"^v<> TO MOVE, <> or %s to TOGGLE",prog_defaults.toggle_key_text);
	centre_text(temp,line_buffer,prog_defaults.columns,' ');
	AT(bottom_title_row,0)
	REVERSE_VIDEO
	printf("%s",line_buffer);
	NORMAL_VIDEO

	centre_text("RETURN to Select",line_buffer,prog_defaults.columns,' ');
	AT(bottom_title_row+1,0)
	REVERSE_VIDEO
	printf("%s",line_buffer);
	NORMAL_VIDEO

	WRAP_EOL
}

void options_screen()
{

	/* options are */
	/*		17 Lines			-7 -1025

		0 New Progs			 ON    OFF   SAME
		1 New Accs			 ON	 OFF   SAME

		2 Auto Window		PAGING	SCROLLING
		3 Accs Window		PAGING	SCROLLING
		4 Sets Window		PAGING	SCROLLING		
		5 Other Window		PAGING	SCROLLING		

		6 Auto Path   
		 --------------------------------------

		7 Accs Path 
		 --------------------------------------					 
	
		8 <Set Keys>				9 <Resolution Info>

		10	[   OK   ]   11[ CANCEL ]   12[ SAVE ]

	*/

#define MAX_OPTIONS	12

int options_y, options_x, curr_option, old_option, exit_options;
long key; int upk,lowk;
/*char temp[60];
*/
/* local defaults */
	int lnew_progs_flag;	/* 1 = ON, 2 = OFF, 3 = SAME */
	int lnew_accs_flag;
	int lauto_paging;		/* 1 = paging, 2 = scrolling */
	int laccs_paging;
	int lsets_paging;
	int lother_paging;
	char lauto_path[FILENAME_MAX];
	char laccs_path[FILENAME_MAX];

	curr_option=0;
	old_option=11;

	lnew_progs_flag=prog_defaults.new_progs_flag;
	lnew_accs_flag=prog_defaults.new_accs_flag;
	lauto_paging=prog_defaults.auto_paging;		
	laccs_paging=prog_defaults.accs_paging;
	lsets_paging=prog_defaults.sets_paging;
	lother_paging=prog_defaults.other_paging;
	strcpy(lauto_path,prog_defaults.auto_path);
	strcpy(laccs_path,prog_defaults.accs_path);

	options_y=prog_defaults.rows-3-17+1;
	if(options_y>0)
		options_y=options_y/2;
	else
		options_y=1;

	options_x=prog_defaults.columns-40;
	if(options_x>0)
		options_x=options_x/2;
	else
		options_x=0;

	CLEAR_SCREEN

	centre_text("OPTIONS",line_buffer,prog_defaults.columns,' ');
	
	DISCARD_EOL
	AT(title_row,0)
	REVERSE_VIDEO
	printf("%s",line_buffer);
	NORMAL_VIDEO

	options_bottom_title();

	AT(options_y,options_x+1)
	printf("New Progs");
	print_on_off_same(options_y,options_x+1,lnew_progs_flag);
	AT(options_y+1,options_x+1)
	printf("New Accs");
	print_on_off_same(options_y+1,options_x+1,lnew_accs_flag);

	AT(options_y+3,options_x+1)
	printf("Auto Window");
	print_paging_scrolling(options_y+3,options_x+1,lauto_paging);
	AT(options_y+4,options_x+1)
	printf("Accs Window");
	print_paging_scrolling(options_y+4,options_x+1,laccs_paging);
	AT(options_y+5,options_x+1)
	printf("Sets Window");
	print_paging_scrolling(options_y+5,options_x+1,lsets_paging);
	AT(options_y+6,options_x+1)
	printf("Other Window");
	print_paging_scrolling(options_y+6,options_x+1,lother_paging);

	remove_extension(lauto_path);
	AT(options_y+8,options_x+1)
	printf("Auto Path");
/*	AT(options_y+9,options_x+1)
	printf("--------------------------------------");
*/	AT(options_y+9,options_x+1)
	printf("%s",lauto_path);

	remove_extension(laccs_path);
	AT(options_y+11,options_x+1)
	printf("Accs Path");
/*	AT(options_y+12,options_x+1)
	printf("--------------------------------------");
*/	AT(options_y+12,options_x+1)
	printf("%s",laccs_path);

	AT(options_y+14,options_x+1)
	printf("<Set Keys>");

	AT(options_y+14,options_x+22)
	printf("<Resolution Info>");
	
	AT(options_y+16,options_x+3)
	printf("[   OK   ]");

	AT(options_y+16,options_x+15)
	printf("[ CANCEL ]");

	AT(options_y+16,options_x+27)
	printf("[  SAVE  ]");

	upk=0;lowk=0;exit_options=0;
	print_option(options_y,options_x,old_option, curr_option);

	while(exit_options==0)
	{
			while(!Bconstat(2))
			;

			key=Bconin(2);
			upk=(int)(key>>16);
			lowk=(int)(key%256);

			if(upk==0x48 )	/* up arrow */
			{
				old_option=curr_option;
				switch(curr_option)
				{
				case 11:
				case 10:
						curr_option=8;
						break;
				case 12:
						curr_option=9;
						break;
				case 9:
						curr_option=7;
						break;
				default:
						curr_option=curr_option-1;
						break;
				}

				if(curr_option<0)
					curr_option=MAX_OPTIONS;
				print_option(options_y,options_x,old_option, curr_option);
			}
			else
			{
			if(upk==0x50)	/* down arrow */
				{
					old_option=curr_option;

					switch(curr_option)
					{
					case 8: 
							curr_option=10;
							break;
					case 9:
							curr_option =12;
							break;
					case 10:
					case 11:
					case 12:
							curr_option=0;
							break;		
					default:
							curr_option=curr_option+1;
							break;
					}
					if(curr_option>MAX_OPTIONS)
						curr_option=0;
					print_option(options_y,options_x,old_option, curr_option);
				}	
				else
				{	
					if(upk==0x4D)	/* right arrow */
					{
					old_option=curr_option;

						switch(curr_option)
						{
						case 0:
								lnew_progs_flag++;
								if(lnew_progs_flag>3)
									lnew_progs_flag=1;
								print_on_off_same(options_y,options_x+1,lnew_progs_flag);
								break;
						case 1:
								lnew_accs_flag++;
								if(lnew_accs_flag>3)
									lnew_accs_flag=1;
								print_on_off_same(options_y+1,options_x+1,lnew_accs_flag);
								break;
						case 2:
								lauto_paging++;
								if(lauto_paging>SCROLLING)
									lauto_paging=PAGING;
								print_paging_scrolling(options_y+3,options_x+1,lauto_paging);
								break;
						case 3:
								laccs_paging++;
								if(laccs_paging>SCROLLING)
									laccs_paging=PAGING;
								print_paging_scrolling(options_y+4,options_x+1,laccs_paging);
								break;
						case 4:
								lsets_paging++;
								if(lsets_paging>SCROLLING)
									lsets_paging=PAGING;
								print_paging_scrolling(options_y+5,options_x+1,lsets_paging);
								break;
						case 5:
								lother_paging++;
								if(lother_paging>SCROLLING)
									lother_paging=PAGING;
								print_paging_scrolling(options_y+6,options_x+1,lother_paging);
								break;

						case 8:
						case 10:
						case 11:
								curr_option++;
								break;
						}
						if(curr_option>MAX_OPTIONS)
							curr_option=0;
						print_option(options_y,options_x,old_option, curr_option);
					}	
					else
						{
							if(upk==0x4B)	/* left arrow */
							{
								old_option=curr_option;

								switch(curr_option)
								{
								case 0:
										lnew_progs_flag--;
										if(lnew_progs_flag<1)
											lnew_progs_flag=3;
										print_on_off_same(options_y,options_x+1,lnew_progs_flag);
										break;
								case 1:
										lnew_accs_flag--;
										if(lnew_accs_flag<1)
											lnew_accs_flag=3;
										print_on_off_same(options_y+1,options_x+1,lnew_accs_flag);
										break;
								case 2:
										lauto_paging--;
										if(lauto_paging<PAGING)
											lauto_paging=SCROLLING;
										print_paging_scrolling(options_y+3,options_x+1,lauto_paging);
										break;
								case 3:
										laccs_paging--;
										if(laccs_paging<PAGING)
											laccs_paging=SCROLLING;
										print_paging_scrolling(options_y+4,options_x+1,laccs_paging);
										break;
								case 4:
										lsets_paging--;
										if(lsets_paging<PAGING)
											lsets_paging=SCROLLING;
										print_paging_scrolling(options_y+5,options_x+1,lsets_paging);
										break;
								case 5:
										lother_paging--;
										if(lother_paging<PAGING)
											lother_paging=SCROLLING;
										print_paging_scrolling(options_y+6,options_x+1,lother_paging);
										break;
								case 9:
								case 11:
								case 12:
								curr_option--;
								break;
								}
								if(curr_option<0)
									curr_option=MAX_OPTIONS;
								print_option(options_y,options_x,old_option, curr_option);
							}
							else
							{
							if(upk==0x1C) /* return */
							{
								switch(curr_option)
								{
								case 6:
										edit_at(options_y+9,options_x+1,FILENAME_MAX,37,lauto_path,'-',0,valid_filename_char,1);
										options_bottom_title();
										break;
								case 7:
										edit_at(options_y+12,options_x+1,FILENAME_MAX,37,laccs_path,'-',0,valid_filename_char,1);
										options_bottom_title();
										break;
								case 8:
										/* set keys */
										break;
								case 9:
										/* set res stuff */
										break;
								case 10:
										/* set defaults */
										prog_defaults.new_progs_flag=lnew_progs_flag;
										prog_defaults.new_accs_flag=lnew_accs_flag;
										prog_defaults.auto_paging=lauto_paging;		
										prog_defaults.accs_paging=laccs_paging;
										prog_defaults.sets_paging=lsets_paging;
										prog_defaults.other_paging=lother_paging;
										strcpy(prog_defaults.auto_path,lauto_path);
										strcpy(prog_defaults.accs_path,laccs_path);
										exit_options=1;	
										break;
								case 11:
										exit_options=1;	
										break;
								case 12:
										/* save defaults */
										break;
								}
							}
							else
							{
								if(upk==prog_defaults.toggle_key_high)
								{
									switch(curr_option)
									{
									case 0:
										lnew_progs_flag++;
										if(lnew_progs_flag>3)
											lnew_progs_flag=1;
										print_on_off_same(options_y,options_x+1,lnew_progs_flag);
										break;
									case 1:
											lnew_accs_flag++;
											if(lnew_accs_flag>3)
											lnew_accs_flag=1;
											print_on_off_same(options_y+1,options_x+1,lnew_accs_flag);
											break;
									case 2:
											lauto_paging++;
											if(lauto_paging>SCROLLING)
												lauto_paging=PAGING;
											print_paging_scrolling(options_y+3,options_x+1,lauto_paging);
											break;
									case 3:
											laccs_paging++;
											if(laccs_paging>SCROLLING)
												laccs_paging=PAGING;
											print_paging_scrolling(options_y+4,options_x+1,laccs_paging);
											break;
									case 4:
											lsets_paging++;
											if(lsets_paging>SCROLLING)
												lsets_paging=PAGING;
											print_paging_scrolling(options_y+5,options_x+1,lsets_paging);
											break;
									case 5:
											lother_paging++;
											if(lother_paging>SCROLLING)
												lother_paging=PAGING;
											print_paging_scrolling(options_y+6,options_x+1,lother_paging);
											break;
									}
								}
							}

							}	
						}				
				}
			}

	}

}


