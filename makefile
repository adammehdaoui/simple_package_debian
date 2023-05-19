CC=gcc
CFLAGS=-Wall

all : main

main : 
	$(CC) $(CFLAGS) -o largest_file largest_file.c

force :
	make --always-make

clean :
	rm -f largest_file
	rm -rf *.o
	