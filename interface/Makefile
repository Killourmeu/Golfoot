CC = gcc
CCOBJ = $(CC) -c
CFLAGS = -g -Wall -lSDL2 -lSDL2_image -lSDL2_ttf

# Création de l'éxécutable

all:    main

main: main.o fonction.o 
	$(CC) $^ -o $@ $(CFLAGS)
main.o: main.c fonction.h
	$(CCOBJ) $< 
fonction.o: fonction.c
	$(CCOBJ) $< 
# Suppression des fichiers temporaires
clean:
	rm -rf *.o 
# Suppression de tous les fichier sauf les sources en vue d'une reconstruction complète
mrproper:	clean