CC=gcc
CFLAGS=-Wall -std=c99 -O3
 
projeto: main.o slist.o
		$(CC) $(CFLAGS) -o projeto main.o slist.o 	    	
main.o: main.c
	 	$(CC) -c $(CFLAGS) main.c
slist.o: slist.c slist.h
		$(CC) -c $(CFLAGS) slist.c