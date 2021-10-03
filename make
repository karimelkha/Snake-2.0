all: clientAPI.o main.o snakeAPI.o fonctions.o SNAKE


clientAPI.o : clientAPI.c
	gcc -Wall  -c clientAPI.c

snakeAPI.o : snakeAPI.c
	gcc -Wall  -c snakeAPI.c

fonctions.o: fonctions.c
    gcc -Wall -c fonctions.c

main.o: main.c
	gcc -Wall -c main.c




SNAKE: main.o snakeAPI.o clientAPI.o fonctions.o
	gcc -o SNAKE main.o snakeAPI.o clientAPI.o fonctions.o

clear:
	rm -f *.o

vclean:
	rm -f SNAKE

.PHONEY:
	clean all
