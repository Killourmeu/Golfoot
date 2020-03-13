CC = gcc
CCOBJ = $(CC) -c
CFLAGS = -Wall
LIBMATHS = -lm

# Création de l'éxécutable
Jeu: jeu.o map.o balle.o
	$(CC) $^ -o $@ $(CFLAGS) $(LIBMATHS)
balle.o: balle.c map.h
	$(CCOBJ) $< $(LIBMATHS)
map.o: map.c
	$(CCOBJ) $<
# Suppression des fichiers temporaires
clean:
	rm -rf *.o
# Suppression de tous les fichier sauf les sources en vue d'une reconstruction complète
mrproper:    clean
