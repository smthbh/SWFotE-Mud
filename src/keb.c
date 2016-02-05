#include <math.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "mud.h"

#if defined(__CYGWIN__)
#include <dirent.h>
#else
#include <sys/dir.h>
#endif

#include <unistd.h>

void descriptor_switch( DESCRIPTOR_DATA * ch, DESCRIPTOR_DATA * victim );
void do_as_mortal( CHAR_DATA * ch, char *argument );


bool exists_player( char *name )
{
   struct stat fst;
   char buf[256];

   /*
    * Stands to reason that if there ain't a name to look at, they damn well don't exist!
    */
   if( !name || !str_cmp( name, "" ) )
      return FALSE;

   snprintf( buf, 256, "%s%c/%s", PLAYER_DIR, tolower( name[0] ), capitalize( name ) );

   if( stat( buf, &fst ) != -1 )
      return TRUE;

   return FALSE;
}


void do_doas( CHAR_DATA * ch, char *argument )
{
   CHAR_DATA *victim;
   char arg[MAX_INPUT_LENGTH];

   argument = one_argument( argument, arg );

   if( IS_NPC( ch ) )
      return;

   if( argument[0] == '\0' )
   {
      send_to_pager( "You must input the name of an online character.\n\r", ch );
      return;
   }

   if( !str_prefix( "quit", argument ) )
   {
      send_to_char( "&RDon't be stupid, you'd turn them into you or trap yourself as a mortal.\n\r", ch );
      return;
   }
   if( !str_cmp( arg, "mortal" ) )
   {
      do_as_mortal( ch, argument );
      return;
   }
   if( ( ( victim = get_char_world( ch, arg ) ) == NULL ) )
   {
      send_to_pager( "No such character online.\n\r", ch );
      return;
   }
   if( IS_NPC( victim ) )
   {
      send_to_pager( "That's not a player!\n\r", ch );
      return;
   }
   if( !victim->desc )
   {
      send_to_pager( "&RAre you trying to crash the MUD or something?\n\r", ch );
      return;
   }
   if( ch->desc->original || victim->desc->original )
   {
      send_to_pager( "Not while switched!\n\r", ch );
      return;
   }

   if( get_trust( ch ) <= get_trust( victim ) )
   {
      send_to_char( "I don't think so..\n\r", ch );
      return;
   }
   descriptor_switch( ch->desc, victim->desc );
   interpret( victim, argument );
   descriptor_switch( ch->desc, victim->desc );
}

void descriptor_switch( DESCRIPTOR_DATA * ch, DESCRIPTOR_DATA * victim )
{
   DESCRIPTOR_DATA *origch;
   DESCRIPTOR_DATA *origvictim;
   CHAR_DATA *chr;
   CHAR_DATA *vict;

   if( !ch || !victim )
      return;

   origch = ch;
   origvictim = victim;
   chr = ch->character;
   vict = victim->character;

   victim = origch;
   victim->character = vict;
   victim->character->desc = origch;
   ch = origvictim;
   ch->character = chr;
   ch->character->desc = origvictim;
}

void do_as_mortal( CHAR_DATA * ch, char *argument )
{
   int trust, level;

   level = ch->top_level;
   trust = ch->trust;
   ch->top_level = LEVEL_IMMORTAL - 2;
   ch->trust = LEVEL_IMMORTAL - 2;
   interpret( ch, argument );
   ch->top_level = level;
   ch->trust = trust;
   return;
}

void do_pfreload( CHAR_DATA * ch, char *argument )
{
   CHAR_DATA *victim;
   char arg[MAX_INPUT_LENGTH];

   if( IS_NPC( ch ) )
      return;

   argument = one_argument( argument, arg );

   if( arg[0] == '\0' )
   {
      send_to_char( "Reload who?\n\r", ch );
      return;
   }

   if( !( victim = get_char_world( ch, arg ) ) )
   {
      send_to_char( "They are not here.\n\r", ch );
      return;
   }

   if( get_trust( victim ) > get_trust( ch ) )
   {
      send_to_char( "You can't reload imms who are on a higher level!\n\r", ch );
      return;
   }

   if( exists_player( victim->name ) )
   {
      DESCRIPTOR_DATA *d;
      char name[MAX_STRING_LENGTH];
      char buf[MAX_STRING_LENGTH];
      ROOM_INDEX_DATA *in_room;
      bool Load;
      d = NULL;
      d = victim->desc;

      sprintf( name, "%s", victim->name );
      in_room = victim->in_room;
      /*
       * clear descriptor pointer to get rid of bug message in log
       */
      victim->desc = NULL;
      extract_char( victim, TRUE );
      d->character = NULL;

      Load = load_char_obj( d, name, FALSE, FALSE );
      victim = d->character;
      victim->desc = d;
      victim->timer = 0;
      /*
       * Insert in the char_list
       */
      LINK( d->character, first_char, last_char, next, prev );
      char_to_room( victim, in_room );

      if( Load )
      {
         send_to_char( "Your pfile has been reloaded.\n\r", victim );
         send_to_char( "Their pfile has been reloaded.\n\r", ch );
         sprintf( buf, "%s has been reloaded.", victim->name );
         log_string( buf );
      }
      else
      {
         send_to_char( "Hrmm bug, it didnt work.\n\r", ch );
         return;
      }
   }

   else
      send_to_char( "They have to have a pfile before you can load it.\n\r", ch );

   return;
}

void do_crash( CHAR_DATA * ch, char *argument )
{
   if( !argument || ( argument[0] == '\0' ) || strcmp( argument, "yes" ) )
   {
      send_to_char( "&wIf you really want to crash the mud type \"&Wcrash yes&w\".\n\r", ch );
      return;
   }
   if( ch->pIndexData || ( ch->top_level < MAX_LEVEL ) )
   {
      send_to_char( "&YYou wish you had that kind of power!\n\r", ch );
      log_printf( "%s tried to crash the mud with the Crash Command", ch->name );
      return;
   }
   else
   {
      log_printf( "%s is crashing the mud", ch->name );
      if( ch->pIndexData->vnum == 1234 )
         send_to_char( "Wierd\n\r", ch );
   }
}
