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



/*****************************************************************
*Program writen by:                                              *
*Greg (Keberus Maou'San) Mosley                                  *
*Co-Owner/Coder SW: DoD                                          *
*www.t-n-k-games.com                                             *
*                                                                *
*Description:                                                    *
*This program will allow imms to designate rooms for people      *
*to go to play slot machines. I tried to comment the code        *
*enough to not have to go into great detail in this description  *
******************************************************************
*What it does:                                                   *
*This program uses the number_range function to generate three   *
*numbers and if the number is in a certain range it is assigned  *
*a value the chance of getting a bar is 10%, cherries 15% and    *
*the other 3 are 25%                                             *
*****************************************************************/

/*TERMS OF USE
         I only really have 2 terms...
 1. Give credit where it is due, keep the above header in your code 
    (you don't have to give me credit in mud) and if someone asks 
	don't lie and say you did it.
 2. If you have any comments or questions feel free to email me
    at keberus@gmail.com

  Thats All....
 */
 
/* To Implement:
	In:  mud.h
		after:  DECLARE_DO_FUN( do_plantbeacon );
			add:  DECLARE_DO_FUN( do_playslots );
		after:  #define ROOM_HIDDENPAD          BV10 (or whatever your last one is on the second set)
			add:  #define ROOM_SLOTS          BV11

	In:  build.c
		In:  char * const    r_flags2 []
			replace:  "r12"  
				with:  "room_slots"
		In:  void do_redit( CHAR_DATA *ch, char *argument )
			In the ifcheck:  if ( !str_cmp( arg, "flags2" ) )
				change:  send_to_char( "emptyshop pshop shipyard garage barraks control clanland clanjail arena\n\r", ch );
                  to:  send_to_char( "emptyshop pshop shipyard garage barraks control clanland clanjail arena room_slots\n\r", ch );

    In:  tables.c
		after: if(!str_cmp(name, "do_plantbeacon"))     return do_plantbeacon;
			add:  if(!str_cmp(name, "do_playslots"))     return do_playslots;
		after:  if ( skill == do_planets )     return "do_planets";
			add:  if ( skill == do_playslots )     return "do_playslots";
*/


#include <stdio.h>
#include <string.h>
#include "mud.h"


//Constant multipliers types of winnings
#define matchingthreebars     5
#define matchingthreenobar    3
#define wildthree             2
#define twocherries           1

//Constant Defines for max and min slot bets
#define maxsbet		      100
#define minsbet               1

//Constant values for the slots
#define slot_cherries         1
#define slot_orange           2
#define slot_plum             3
#define slot_bar              4
#define slot_lemon            5


//All the the headers for functions used in the program
sh_int   genslots      (void);
void     calcslots     (CHAR_DATA *ch, sh_int *amount);
void     printslots    (CHAR_DATA *ch, sh_int *slot1, sh_int *slot2, sh_int *slot3);
void     printwinnings (CHAR_DATA *ch, sh_int *amount, sh_int *winningsmult);
void     checkslots    (CHAR_DATA *ch, sh_int *amount, sh_int *slot1, sh_int *slot2, sh_int *slot3);
void     playslots_help(CHAR_DATA *ch);
char   * get_slot_string(sh_int *slot);

void playslots_help (CHAR_DATA *ch)
{
   ch_printf(ch, "&W Syntax: &wplayslots <amount to bet> \n\r\n\r"
      "   &WWinning Combos		    Payoff \n\r"
	  "   &O--------------                   ------ \n\r"
	  "   &z2 cherries                         &C1x    \n\r"
	  "   &zWild 3 (3 of a kind with 1 bar)    &C2x    \n\r"
	  "   &z3 of a kind (not using a bar)      &C3x    \n\r"
	  "   &zbar bar bar                        &C5x    \n\r\n\r"
          "   &wThe minimum bet is: &Y%d\n\r"
          "   &wThe maximum bet is: &Y%d\n\r" , minsbet, maxsbet );

}

void do_playslots (CHAR_DATA *ch, char *argument)
{
	sh_int amount;
    char errbuf[MSL];

	if(IS_NPC(ch))
		return;

	if(argument == NULL)
	{
		playslots_help(ch);
		return;
	}

	if( !IS_SET( ch->in_room->room_flags2, ROOM_SLOTS) )
	{
		send_to_char("&WThere are no slot machines in your vicinity\n\r", ch);
		return;
	}

	amount = atoi(argument);

	if(amount < minsbet)
	{
		sprintf(errbuf, "&WYou must insert at least &Y%d &Wcredit(s)!\n\r\n\r", minsbet);
		send_to_char(errbuf, ch);
		playslots_help(ch);
		return;
	}

    if(ch->gold < atoi(argument))
    {
        send_to_char("You don't have that much money\n\r", ch);
        return;
    }

	if(amount > maxsbet)
	{
           sprintf(errbuf, "&WWhoah....the max bet is &Y%d &Wcredit(s)!\n\r\n\r", maxsbet);
           send_to_char(errbuf, ch);
           playslots_help(ch);
           return;
	}

	ch->gold -= amount;
	calcslots(ch, &amount);
        amount = 0;
	return;
}

sh_int genslots(void)
{
	sh_int slotval;

	slotval = number_range(1, 100);
 
        if (slotval >= 90)
             return 4;
       
        else if ( slotval >= 75 )
             return 1;
 
        else if ( slotval >= 50 )
             return 5; 

        else if ( slotval >= 25 )
             return 2;
 
        else 
             return 3;
	
}

void calcslots(CHAR_DATA *ch, sh_int *amount) //This function makes and sets the values of the slots
{
	sh_int slot1=0, slot2=0, slot3 =0;

	//Set up to output a value of 1 to 5
	slot1 = genslots(); 
	slot2 = genslots();
	slot3 = genslots();

        printslots( ch, &slot1, &slot2, &slot3); //Sending them to the printing function
        checkslots( ch, &(*amount),  &slot1, &slot2, &slot3); //Figuring out if you are the winner
	return;
}

char  *get_slot_string(sh_int *slot)
{
    if ((*slot) == slot_cherries) //if the rand number is equal to cheries num (1)
            return("&Rcherries");    //copy cherries to string

    else if ((*slot) == slot_orange)       //repeat comment above but change type and num value
            return("&Oorange");

    else if ((*slot) == slot_plum)
            return("&Pplum");

    else if ((*slot) == slot_bar)
            return("&zbar");

    else
            return("&Ylemon");
}

//Below code prints out the nice strings for the values
void printslots(CHAR_DATA *ch, sh_int *slot1, sh_int *slot2, sh_int *slot3)
{ 
    char buf[MSL];
	char slots1[MSL], slots2[MSL], slots3[MSL]; //defining slot strings to be modified
        
        strcpy(slots1, "");
        strcpy(slots2, "");
        strcpy(slots3, "");

//Slot 1 checks for type
          strcpy(slots1, get_slot_string( &(*slot1) ) );
	
//slot 2 checks for type
          strcpy(slots2, get_slot_string( &(*slot2) ) );

//slot 3 checks for type
          strcpy(slots3, get_slot_string( &(*slot3) ) );
	
	send_to_char("\n\r&c*********************************************************&w&W\n\r", ch);
	sprintf(buf, "   &c***&w&W  %10.10s   &c***&w&W  %10.10s   &c***&w&W  %10.10s   &c***&w&W       \n\r", slots1, slots2, slots3);
        send_to_char(buf, ch);
	send_to_char("&c*********************************************************&w&W\n\r", ch);	
	return;
}

//Below function says if you are a winner or not
//Then adds winnings or takes away the cost per turn
void printwinnings(CHAR_DATA *ch, sh_int *amount, sh_int *winningsmult)
{
	char buf[MSL];

	if ( (*winningsmult) > 0)
	{
		sprintf(buf, "&BWINNER, &WYou won &Y%d &Wcredit(s)&w&W\n\r", ((*winningsmult) * (*amount) ) );
		send_to_char(buf, ch);
		ch->gold += ( (*winningsmult) * (*amount) );
        }
	else 
	{
		sprintf(buf, "&RNo luck. &WYou lose &Y%d &Wcredit(s)\n\r", (*amount) );
		send_to_char(buf, ch);

	}

        (*amount) = 0;
        (*winningsmult) = 0;
	return;
}

void checkslots(CHAR_DATA *ch, sh_int *amount, sh_int *slot1, sh_int *slot2, sh_int *slot3)
{
	bool oneandtwo=FALSE, oneandthree=FALSE, twoandthree=FALSE;
	bool allthree=FALSE;
        sh_int winningsmult =0;

	      /*1 = "cherries";
		  2 = "orange";
		  3 = "plum";
	          4 = "bar";
		  5 = "lemon";*/

	//This sections checks to see which ones match
	if ( (*slot1) == (*slot2) )
               oneandtwo = TRUE;
 
	if( (*slot1) == (*slot3))
		oneandthree = TRUE;

	if( (*slot2) == (*slot3))
		twoandthree = TRUE;


//Find out if they all match
	if ( (oneandtwo == TRUE) && (oneandthree == TRUE) && (twoandthree == TRUE) )
		allthree = TRUE;

//If they all match and are all bars
    if ( (allthree == TRUE) && ((*slot1) == slot_bar) )
		winningsmult = matchingthreebars;


//If they all match but aren't bars
	else if ( (allthree == TRUE) && ((*slot1) != slot_bar) )
		winningsmult = matchingthreenobar;


//This section checks to see if two match and one of the matching is a bar
	else if ( (oneandtwo == TRUE) && ((*slot1) == slot_bar) )
		winningsmult = wildthree;
	
	else if ( (oneandthree == TRUE) && ((*slot1) == slot_bar) )
		winningsmult = wildthree;
		
	else if ( (twoandthree == TRUE) && ((*slot2) == slot_bar) )
		winningsmult = wildthree;

//This section checks to see if two match and the third is a bar (doesn't work for 2 matching bars)
	else if ( (oneandtwo == TRUE) && ((*slot3) == slot_bar) )
		winningsmult = wildthree;
	
	else if ( (oneandthree == TRUE) && ((*slot2) == slot_bar) )
		winningsmult = wildthree;
		
	else if ( (twoandthree == TRUE) && ((*slot1) == slot_bar) )
		winningsmult = wildthree;

	//This section checks to see if two match and they are type cherries
	else if ( (oneandtwo == TRUE) && ((*slot1) == slot_cherries) )
		winningsmult = twocherries;
	
	else if ( (oneandthree == TRUE) && ((*slot1) == slot_cherries) )
		winningsmult = twocherries;
		
	else if ( (twoandthree == TRUE) && ((*slot2) == slot_cherries) )
		winningsmult = twocherries;
       

	printwinnings(ch, &(*amount), &winningsmult); //Send the winningsmult to the printing function
	return;
}

