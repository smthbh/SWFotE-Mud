 /*********************************************************************************** 
 *                                                                                  *
 *          _______.____    __    ____       _______                  _______       *
 *         /       |\   \  /  \  /   /  _   |   ____|          __    |   ____|      *
 *        |   (----` \   \/    \/   /  (_)  |  |__    ____   _/  |_  |  |__         *
 *         \   \      \            /    _   |   __|  /  _ \  \   __\ |   __|        *
 *     .----)   |      \    /\    /    (_)  |  |    (  <_> )  |  |   |  |____       *
 *     |_______/        \__/  \__/          |__|     \____/   |__|   |_______|      *
 *                                                                                  *
 * SWFotE v2.0 (FotE v1.1 cleaned up and considerably modded)  by:                  *
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

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "mud.h"        


/* 
   Original Code from SW:FotE 1.1 
   Reworked strrep function. 
   Fixed a few glaring errors. It also will not overrun the bounds of a string. 
   -- Xorith 
*/ 
char *strrep( const char *src, const char *sch, const char *rep ) 
{ 
   int lensrc = strlen( src ), lensch = strlen( sch ), lenrep = strlen( rep ), x, y, in_p; 
   static char newsrc[MAX_STRING_LENGTH]; 
   bool searching = FALSE; 

   newsrc[0] = '\0'; 
   for( x = 0, in_p = 0; x < lensrc; x++, in_p++ ) 
   { 
      if( src[x] == sch[0] ) 
      { 
         searching = TRUE; 
         for( y = 0; y < lensch; y++ ) 
            if( src[x+y] != sch[y] ) 
               searching = FALSE; 

         if( searching ) 
         { 
            for( y = 0; y < lenrep; y++, in_p++ ) 
            { 
               if( in_p == ( MAX_STRING_LENGTH - 1 ) ) 
               { 
                  newsrc[in_p] = '\0'; 
                  return newsrc; 
               } 
               newsrc[in_p] = rep[y]; 
            } 
            x += lensch - 1; 
            in_p--; 
            searching = FALSE; 
            continue; 
         } 
      } 
      if( in_p == ( MAX_STRING_LENGTH - 1 ) ) 
      { 
         newsrc[in_p] = '\0'; 
         return newsrc; 
      } 
      newsrc[in_p] = src[x]; 
   } 
   newsrc[in_p] = '\0'; 
   return newsrc; 
} 

char *strlinwrp(char *src, int length)
{
  int srclen,in_p,x,last_line;
  char newstr[MAX_STRING_LENGTH];
  bool looking;
    if(!length)
      length = 60;
    srclen = strlen(src);
    in_p = 0;
// STRFREE(newstr); Commented out - was just defined!
    looking = FALSE;
    for(x=0,last_line=0;x<srclen;x++,last_line++)
    {
        if(src[x] == '\r' || src[x] == '\n')
        {
            last_line = 0;
            looking = FALSE;
        }
        else if(last_line%length == 0 && x != 0)
            looking = TRUE;
        if(looking)
        {
          if(src[x] == ' ')
          {
            newstr[in_p++] = '\r';
            newstr[in_p++] = '\n';
            looking = FALSE;
            last_line = 0;
            if(src[x+1] == ' ')
              x++;
            continue;
          }
        }
        newstr[in_p++] = src[x];
    }
    newstr[in_p++] = '\r';
    newstr[in_p++] = '\n';
    newstr[in_p++] = '\0';
  return str_dup( newstr );
}

char *remand( char *arg )
{
        static char ret[MAX_STRING_LENGTH];
        char *retptr;
        retptr = ret;

        if(arg == NULL)
                return NULL;

        for (; *arg != '\0'; arg++ )
        {
                if (*arg == '&' && *(arg + 1) != '\0' )
                        arg++;
                else if (*arg == '^' && *(arg + 1) != '\0' )
                        arg++;
                else
                {
                        *retptr = *arg;
                        retptr++;
                }
        }

        *retptr = '\0';
        return ret;
}

char *rembg( char *src )
{
      static char ret[MAX_STRING_LENGTH];
      char *retptr;
      retptr = ret;

      if(src == NULL)
              return NULL;

      for (; *src != '\0'; src++ )
      {
              if (*src == '^' && *(src + 1) != '\0' )
                      src++;
              else
              {
                      *retptr = *src;
                      retptr++;
              }
      }

      *retptr = '\0';
      return ret;
}



char *htmlcolor( const char *src ) 
{ 
   static char arg[MAX_STRING_LENGTH]; 
   char *newarg; 

   /* This function will format color codes into <font color> strings */ 
   if( strlen(src) == 0 ) 
   { 
      bug( "Htmlcolor: emptry string!" ); 
      return "(err)"; 
   } 

   newarg = strrep( src, "<", "&" ); 
   newarg = strrep( newarg, ">", "&" ); 
   newarg = strrep( newarg, "&x", "</font><font color='#333333'>" ); 
   newarg = strrep( newarg, "&r", "</font><font color='#660000'>" ); 
   newarg = strrep( newarg, "&g", "</font><font color='#006600'>" ); 
   newarg = strrep( newarg, "&O", "</font><font color='#666600'>" ); 
   newarg = strrep( newarg, "&b", "</font><font color='#000066'>" ); 
   newarg = strrep( newarg, "&p", "</font><font color='#660066'>" ); 
   newarg = strrep( newarg, "&c", "</font><font color='#666699'>" ); 
   newarg = strrep( newarg, "&w", "</font><font color='#FFFFFF'>" ); 
   newarg = strrep( newarg, "&z", "</font><font color='#666666'>" ); 
   newarg = strrep( newarg, "&R", "</font><font color='#AA0000'>" ); 
   newarg = strrep( newarg, "&G", "</font><font color='#00AA00'>" ); 
   newarg = strrep( newarg, "&Y", "</font><font color='#999900'>" ); 
   newarg = strrep( newarg, "&B", "</font><font color='#0000AA'>" ); 
   newarg = strrep( newarg, "&P", "</font><font color='#AA00AA'>" ); 
   newarg = strrep( newarg, "&C", "</font><font color='#9999CC'>" ); 
   newarg = strrep( newarg, "&W", "</font><font color='#CCCCCC'>" ); 
   newarg = strrep( newarg, "\r", "" ); 

   strcpy( arg, newarg ); 
   return arg; 
} 
 
/*char *chrmax( char *src, int length )
{
  
  int srclen,in_p,i,count;
  char newstr[MAX_STRING_LENGTH];
  bool looking;
  srclen = strlen(src);
  in_p=0; STRFREE(newstr); count=0;
  looking=FALSE;
  for(i=0,in_p=0;i<srclen;i++,in_p++)
  {
    
      if (count >= length){
        newstr[in_p] = '\0';
    	return str_dup( newstr );
      } 
    
    if (src[i] == '&'){
    	looking = TRUE;
  
    	if (src[i++] == '&')
    	  count++;
    	  i--;
    }
    if (looking){
    	  looking = FALSE;
    	    newstr[in_p] = src[i];
    	    in_p++;
    	    i++;
 	    newstr[in_p] = src[i];
    }
    else {
    	newstr[in_p] = src[i];
    	count++;

    }
  }
  if (count < length){
    for(i=0;i<length-count-1;i++,in_p++){
      newstr[in_p] = ' ';
    }
  }
  newstr[in_p] = '\0';
  return str_dup( newstr );
}
*/

char *chrmax( char *src, int length )
{
  int i,len;
  static char ret[MAX_STRING_LENGTH];
  ret[0] = '\0';
  for(len=i=0;len<length;++i)
  {
    if((src[i] != '&') || (src[i] != '^'))
      ++len;
    if((src[i] == '&') || (src[i] == '^'))
      {
      	if ((src[i] == '&') && (src[i+1] == '&'))
      	  ++len;
      	else if ((src[i] == '^') && (src[i+1] == '^'))
      	  ++len;
      	else
      	  len-=2;
      }
    ret[i] = src[i];
  }
  return ret;
}
int strlen_color (char *argument)
{
    char  *str;
    int    i, length;

    str = argument;
    if (argument == NULL)
        return 0;

    for (length=i=0; i < strlen (argument); ++i)
    {
        if ((str [i] != '&') && (str [i] != '^'))
            ++length;
        if ((str [i] == '&') || (str [i] == '^'))
          {
            if ((str[i] == '&') && (str[i+1] == '&'))
                length=2+length;
            else if ((str[i] == '^') && (str[i+1] == '^'))
                length=2+length;
            else
                --length;
          }
    }

    return length;
}

char *format_str(char *src, int len){
  int sp1, sx;
  static char add_len[MAX_STRING_LENGTH];
  add_len[0] = '\0';
  sp1 = strlen_color(src);
  if (sp1 < len){
    for (sx=14; sx >= sp1; sx--)
      strcat( add_len, " ");
    strcat( src, add_len );
    return src;
  }
  else
    return chrmax( src, len );
}

/*
 * Strips colors from a string --Keberus
 */
char *strip_color( const char *str )
{
   static char newstr[MAX_STRING_LENGTH];
   int i, j;

   if( !str || str[0] == '\0' )
   {
      return "";
   }

   for( i = j = 0; ( str[i] != '\0' ); i++, j++ )
   {
      if( str[i] == '&' )
      {
         i = i + 2;
      }
      newstr[j] = str[i];
   }
   newstr[j] = '\0';
   return newstr;
}

