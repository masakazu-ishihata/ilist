# Makefile
TAR = test
CC = gcc -O6 -Wall
L = -lm -listring
OBJS = main.o ilist.o
SHAD = -fPIC -shared
LIB = libilist.so

all : $(TAR) lib
$(TAR): $(OBJS)
	  $(CC) -o $@ $(OBJS) $(L)
clean:
	  rm -f $(OBJS) $(TAR) $(LIB) *~ *.bak

.c.o:	  $(CC) -c $<

lib:
	$(CC) $(SHAD) -o $(LIB) ilist.c $(L)

main.o: ilist.h
ilist.o: ilist.h
