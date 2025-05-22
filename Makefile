CC = gcc
CFLAGS = -Wall -g -std=c99 -Werror -D_POSIX_C_SOURCE=200809L

output: main.o dataRetrival.o pidRetrival.o Printing.o
	$(CC) $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

pidRetrival.o: pidRetrival.c pidRetrival.h 
	$(CC) $(CFLAGS) -c $< -o $@

dataRetrival.o: dataRetrival.c dataRetrival.h 
	$(CC) $(CFLAGS) -c $< -o $@

Printing.o: Printing.c Printing.h 
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
	clean:
		rm -f *.o output