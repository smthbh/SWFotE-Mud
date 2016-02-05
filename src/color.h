 /*********************************************************************************** 
 *                                                                                  *
 *          _______.____    __    ____       _______                 _______        *
 *         /       )\   \  /  \  /   /  _   |   ____)         __    |   ____)       *
 *        (   (----` \   \/    \/   /  (_)  |  |__    ___   _/  |_  |  |__          *
 *         \   \      \            /    _   |   __)  / _ \ (_   __) |   __)         *
 *     .----)   )      \    /\    /    (_)  |  |    ( (_) )  |  |   |  |____        *
 *    (________/        \__/  \__/          |__|     \___/   |__|   |_______)       *
 *                                                                                  *
 * SWFotE v2.0 (FotE v1.1 cleaned up and considerably modded) by                    *
 * Greg (Keberus) Mosley                                                            *
 * Roman (Trelar) Arnold                                                            *
 *                                                                                  *
 * SWFotE v1 & v1.1 copyright (c) 2002 was created by                               *
 * Chris 'Tawnos' Dary (cadary@uwm.edu),                                            *
 * Korey 'Eleven' King (no email),                                                  *
 * Matt 'Trillen' White (mwhite17@ureach.com),                                      *
 * Daniel 'Danimal' Berrill (danimal924@yahoo.com),                                 *
 * Richard 'Bambua' Berrill (email unknown),                                        *
 * Stuart 'Ackbar' Unknown (email unknown)                                          *
 *                                                                                  *
 * SWR 1.0 copyright (c) 1997, 1998 was created by Sean Cooper                      *
 * based on a concept and ideas from the original SWR immortals:                    *
 * Himself (Durga), Mark Matt (Merth), Jp Coldarone (Exar), Greg Baily (Thrawn),    *
 * Ackbar, Satin, Streen and Bib as well as much input from our other builders      *
 * and players.                                                                     *
 *                                                                                  *
 * Original SMAUG 1.4a written by Thoric (Derek Snider) with Altrag,                *
 * Blodkai, Haus, Narn, Scryn, Swordbearer, Tricops, Gorog, Rennard,                *
 * Grishnakh, Fireblade, and Nivek.                                                 *
 *                                                                                  *
 * Original MERC 2.1 code by Hatchet, Furey, and Kahn.                              *
 *                                                                                  *
 * Original DikuMUD code by: Hans Staerfeldt, Katja Nyboe, Tom Madsen,              *
 * Michael Seifert, and Sebastian Hammer.                                           *
 *                                                                                  *
 ***********************************************************************************/

/****************************************************************************
 *                   ^     +----- |  / ^     ^ |     | +-\                  *
 *                  / \    |      | /  |\   /| |     | |  \                 *
 *                 /   \   +---   |<   | \ / | |     | |  |                 *
 *                /-----\  |      | \  |  v  | |     | |  /                 *
 *               /       \ |      |  \ |     | +-----+ +-/                  *
 ****************************************************************************
 * AFKMud Copyright 1997-2003 by Roger Libiez (Samson),                     *
 * Levi Beckerson (Whir), Michael Ward (Tarl), Erik Wolfe (Dwip),           *
 * Cameron Carroll (Cam), Cyberfox, Karangi, Rathian, Raine, and Adjani.    *
 * All Rights Reserved.                                                     *
 *                                                                          *
 * Original SMAUG 1.4a written by Thoric (Derek Snider) with Altrag,        *
 * Blodkai, Haus, Narn, Scryn, Swordbearer, Tricops, Gorog, Rennard,        *
 * Grishnakh, Fireblade, and Nivek.                                         *
 *                                                                          *
 * Original MERC 2.1 code by Hatchet, Furey, and Kahn.                      *
 *                                                                          *
 * Original DikuMUD code by: Hans Staerfeldt, Katja Nyboe, Tom Madsen,      *
 * Michael Seifert, and Sebastian Hammer.                                   *
 ****************************************************************************
 *               Color Module -- Allow user customizable Colors.            *
 *                                   --Matthew                              *
 *                      Enhanced ANSI parser by Samson                      *
 ****************************************************************************/

#define SAMSONCOLOR  /* To interact with other snippets */

#define COLOR_DIR "../color/"

DECLARE_DO_FUN( do_color );

void reset_colors( CHAR_DATA * ch );
void set_char_color( short AType, CHAR_DATA * ch );
void set_pager_color( short AType, CHAR_DATA * ch );
char *color_str( short AType, CHAR_DATA * ch );
const char *const_color_align( const char *argument, int size, int align );

/*
 * Color Alignment Parameters
 */
#define ALIGN_LEFT	1
#define ALIGN_CENTER	2
#define ALIGN_RIGHT	3

/* These are the ANSI codes for foreground text colors */
#define ANSI_BLACK    	"\e[0;30m"
#define ANSI_DRED    	"\e[0;31m"
#define ANSI_DGREEN     "\e[0;32m"
#define ANSI_ORANGE    	"\e[0;33m"
#define ANSI_DBLUE    	"\e[0;34m"
#define ANSI_PURPLE    	"\e[0;35m"
#define ANSI_CYAN	"\e[0;36m"
#define ANSI_GREY	"\e[0;37m"
#define ANSI_DGREY	"\e[1;30m"
#define ANSI_RED	"\e[1;31m"
#define ANSI_GREEN	"\e[1;32m"
#define ANSI_YELLOW   	"\e[1;33m"
#define ANSI_BLUE	"\e[1;34m"
#define ANSI_PINK	"\e[1;35m"
#define ANSI_LBLUE   	"\e[1;36m"
#define ANSI_WHITE      "\e[1;37m"
#define ANSI_RESET	"\e[0m"

/* These are the ANSI codes for blinking foreground text colors */
#define BLINK_BLACK		"\e[0;5;30m"
#define BLINK_DRED		"\e[0;5;31m"
#define BLINK_DGREEN		"\e[0;5;32m"
#define BLINK_ORANGE		"\e[0;5;33m"
#define BLINK_DBLUE		"\e[0;5;34m"
#define BLINK_PURPLE		"\e[0;5;35m"
#define BLINK_CYAN		"\e[0;5;36m"
#define BLINK_GREY		"\e[0;5;37m"
#define BLINK_DGREY		"\e[1;5;30m"
#define BLINK_RED			"\e[1;5;31m"
#define BLINK_GREEN		"\e[1;5;32m"
#define BLINK_YELLOW		"\e[1;5;33m"
#define BLINK_BLUE		"\e[1;5;34m"
#define BLINK_PINK		"\e[1;5;35m"
#define BLINK_LBLUE		"\e[1;5;36m"
#define BLINK_WHITE		"\e[1;5;37m"

/* These are the ANSI codes for background colors */
#define BACK_BLACK 	"\e[40m"
#define BACK_DRED  	"\e[41m"
#define BACK_DGREEN	"\e[42m"
#define BACK_ORANGE     "\e[43m"
#define BACK_DBLUE      "\e[44m"
#define BACK_PURPLE     "\e[45m"
#define BACK_CYAN       "\e[46m"
#define BACK_GREY       "\e[47m"

/* Other miscelaneous ANSI tags that can be used */
#define ANSI_BOLD		"\e[1m" /* For bright color stuff */
#define ANSI_ITALIC	"\e[3m" /* Italic text */
#define ANSI_UNDERLINE  "\e[4m" /* Underline text */
#define ANSI_BLINK	"\e[5m" /* Blinking text */
#define ANSI_REVERSE    "\e[7m" /* Reverse colors */
#define ANSI_STRIKEOUT  "\e[9m" /* Overstrike line */

#define AT_BLACK    	0
#define AT_BLOOD    	1
#define AT_DGREEN       2
#define AT_ORANGE    	3
#define AT_DBLUE    	4
#define AT_PURPLE    	5
#define AT_CYAN	  	    6
#define AT_GREY		    7
#define AT_DGREY	    8
#define AT_RED		    9
#define AT_GREEN	   10
#define AT_YELLOW   	11
#define AT_BLUE	        12
#define AT_PINK	        13
#define AT_LBLUE        14
#define AT_WHITE        15
#define AT_BLINK        16

/* These should be 17 - 31 normally */
#define AT_BLACK_BLINK  AT_BLACK + AT_BLINK
#define AT_BLOOD_BLINK  AT_BLOOD + AT_BLINK
#define AT_DGREEN_BLINK AT_DGREEN + AT_BLINK
#define AT_ORANGE_BLINK AT_ORANGE + AT_BLINK
#define AT_DBLUE_BLINK  AT_DBLUE + AT_BLINK
#define AT_PURPLE_BLINK AT_PURPLE + AT_BLINK
#define AT_CYAN_BLINK   AT_CYAN + AT_BLINK
#define AT_GREY_BLINK   AT_GREY + AT_BLINK
#define AT_DGREY_BLINK  AT_DGREY + AT_BLINK
#define AT_RED_BLINK    AT_RED + AT_BLINK
#define AT_GREEN_BLINK  AT_GREEN + AT_BLINK
#define AT_YELLOW_BLINK AT_YELLOW + AT_BLINK
#define AT_BLUE_BLINK   AT_BLUE + AT_BLINK
#define AT_PINK_BLINK   AT_PINK + AT_BLINK
#define AT_LBLUE_BLINK  AT_LBLUE + AT_BLINK
#define AT_WHITE_BLINK  AT_WHITE + AT_BLINK


/*People, Objects or Room Related*/
#define AT_IMMORT		32
#define AT_NOTE		    33
#define AT_OBJECT		34
#define AT_PERSON		35
#define AT_RMDESC		36
#define AT_RMNAME		37
#define AT_SHIP         38


/*Actions or Commands*/
#define AT_ACTION	    39       
#define AT_CONSIDER	    40
#define AT_EXITS		41
#define AT_GOLD		    42
#define AT_HELP		    43 /* Added by Samson 1-15-01 for helpfiles */
#define AT_LIST		    44
#define AT_OLDSCORE		45
#define AT_PLAIN	    46
#define AT_QUIT			47
#define AT_REPORT		48
#define AT_SKILL		49
#define AT_SLIST		50


/*Fighting Stuffs*/
#define AT_DAMAGE		51
#define AT_FLEE		    52
#define AT_HIT		    53
#define AT_HITME	    54
#define AT_HURT		    55


/*Continual Messages*/
#define AT_DEAD		    56
#define AT_DYING		57
#define AT_FALLING	   58
#define AT_HUNGRY		59
#define AT_POISON		60
#define AT_RESET		61
#define AT_SOBER		62
#define AT_THIRSTY	    63
#define AT_WEAROFF	    64


/*Mortal Channels*/
#define AT_ARENA        65
#define AT_AUCTION      66 /* Added by Samson 12-25-98 for auction channel */
#define AT_CHAT		    67
#define AT_CLAN         68
#define AT_GOSSIP		69
#define AT_GTELL		70
#define AT_HOLONET      71
#define AT_OOC          72
#define AT_MUSIC        73
#define AT_SAY		    74
#define AT_SHIPTALK     75
#define AT_SHOUT		76 /* Added by Samson 9-29-98 for shout channel */
#define AT_SOCIAL		77
#define AT_TELL		    78
#define AT_WARTALK      79
#define AT_WHISPER    	80 /* Added by Samson 9-29-98 for version 1.4 code */
#define AT_YELL		    81

/*Imm Only Colors*/
#define AT_AVATAR		82
#define	AT_BUILD        83
#define	AT_COMM         84
#define AT_IMMTALK      85
#define AT_LOG		    86
#define AT_RFLAGS1      87
#define AT_RFLAGS2      88
#define AT_RVNUM        89


/* Should ALWAYS be one more than the last numerical value in the list */
#define MAX_COLORS      90

#define AT_MAGIC        AT_WHITE
#define AT_FIRE	        AT_RED
#define AT_DIEMSG       AT_BLOOD
#define AT_DANGER	AT_RED
extern const short default_set[MAX_COLORS];
