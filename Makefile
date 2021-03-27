CC=gcc
CFLAGS=-Wall -std=c99 -O3
 
projeto: main.o slist.o dlist.o stack.o aresta.o fileinterface.o cabecalho.o
		$(CC) $(CFLAGS) -o projeto main.o slist.o dlist.o stack.o aresta.o	    	
main.o: main.c
	 	$(CC) -c $(CFLAGS) main.c
slist.o: slist.c slist.h
		$(CC) -c $(CFLAGS) slist.c
dlist.o: dlist.c dlist.h
		$(CC) -c $(CFLAGS) dlist.c
stack.o: stack.c stack.h
		$(CC) -c $(CFLAGS) stack.c
aresta.o: aresta.c aresta.h
		$(CC) -c $(CFLAGS) aresta.c
fileinterface.o: fileinterface.c fileinterface.h
		$(CC) -c $(CFLAGS) fileinterface.c
cabecalho.o: cabecalho.c cabecalho.h
		$(CC) -c $(CFLAGS) cabecalho.c