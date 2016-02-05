CC      = gcc
PROF    =
NOCRYPT =

#Uncomment the line below if you are getting undefined references to dlsym, dlopen, and dlclose.
#Comment it out if you get errors about ldl not being found.
NEED_DL = -ldl

#Uncomment if using CYGWIN to compile with
#CYGWIN_FLAG = -DCYGWIN

#Some systems need this for dynamic linking to work.
EXPORT_SYMBOLS = -export-dynamic

C_FLAGS = -g2 -Wall $(EXPORT_SYMBOLS) $(CYGWIN_FLAG) $(PROF) $(NOCRYPT) $(DBUGFLG) $(EXPORT_SYMBOLS)
L_FLAGS = $(PROF) $(EXPORT_SYMBOLS) $(CYGWIN_FLAG) $(NEED_DL) -lz -g2

#Comment out to disable cargo
USECARGO = 1

ifdef USECARGO
   C_FLAGS := $(C_FLAGS) -DUSECARGO
endif


C_FILES =  11.c      act_comm.c     act_info.c    act_move.c    act_obj.c    act_wiz.c      boards.c \
       bounty.c         build.c      changes.c       clans.c      color.c       comm.c    comments.c \
        const.c      copyover.c           db.c      editor.c      fight.c      finfo.c       force.c \
      fskills.c     functions.c      handler.c     hashstr.c     hunter.c     interp.c         keb.c \
        magic.c      makeobjs.c     marriage.c         md5.c       mccp.c       misc.c    mud_comm.c \
     mud_prog.c      newarena.c       pfiles.c     planets.c     player.c   renumber.c       reset.c \
         save.c         ships.c        shops.c      skills.c       slay.c    slicers.c       slotm.c \
        space.c       special.c     swskills.c      tables.c       tech.c      track.c      update.c


O_FILES := $(patsubst %.c,o/%.o,$(C_FILES))

H_FILES = $(wildcard *.h) 

SWR = swr
SWR_OLD = ../bin/swr_old
COPYFILE = ../bin/cygwin/copyfile

all:
	$(MAKE) -s swr

# pull in dependency info for *existing* .o files
ifdef CYGWIN_FLAG
	-include dependencies.d
endif

swr: 	$(O_FILES)
	rm -f $(SWR)
ifdef CYGWIN_FLAG
	echo "Generating dependency file ...";
	$(CC) -MM $(C_FLAGS) $(C_FILES) > dependencies.d
	perl -pi -e 's.^([a-z]).o/$$1.g' dependencies.d
else
	$(CC) -o $(SWR) $(O_FILES) $(L_FLAGS) -lm -lcrypt
endif
	echo "                   ";
	echo "Done compiling mud.";
	chmod g+w $(SWR)
	chmod a+x $(SWR)
	chmod g+w $(O_FILES)
ifdef CYGWIN_FLAG
	./$(COPYFILE)
endif
	mv $(SWR) ../bin

clean:
ifdef CYGWIN_FLAG
	rm -f o/*.o ../bin/other/swr.def ../bin/cygwin/swr.exp
	chmod g+w $(COPYFILE)
	chmod a+x $(COPYFILE)
	./$(COPYFILE)
#        $(MAKE) all
else
	rm -f o/*.o $(SWR_OLD) ../bin/$(SWR) ../bin/${SWR}.exe ../bin/win/swr.def ../bin/cygwin/swr.exp
#        $(MAKE) all
endif


purge:
ifdef CYGWIN_FLAG
	rm -f o/*.o ../bin/cygwin/swr.def ../bin/cygwin/swr.exp dependencies.d
else
	rm -f o/*.o $(SWR_OLD) $(SWR) ../bin/cygwin/swr.def ../bin/cygwin/swr.exp
endif


o/%.o: %.c
#       echo "  Compiling $@....";
	echo " $@";
	$(CC) -c $(C_FLAGS) $< -o $@

.c.o: mud.h
	$(CC) -c $(C_FLAGS) $<

