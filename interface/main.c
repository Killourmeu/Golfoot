/* Main a regroupé avec les autre partie du projet */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "fonction.h"

/* verif valgrind */

int main(int argc, char *argv[]){
    /* Démarrage SDL */
    init_SDL(SDL_INIT_VIDEO, IMG_INIT_PNG);  

    /* Variable */
    SDL_Renderer *renderer = NULL;
    SDL_Window *fenetre = NULL;
    SDL_Texture *texture_fond[2], *texture_text[3];
    s_map *map = NULL;
    SDL_Event event;
    int pass = 1;
    char *texte[3] = {"Puissance", "TROU 1/2", "Joueur X"};
    SDL_Color blanc = {255, 255, 255};


    /* Vérification */
    fenetre = SDL_CreateWindow("Niveau I.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN);
    if(!fenetre){
        fprintf(stderr, "[-] SDL_CreateWindow : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        fprintf(stderr, "[-] SDL_CreateRenderer :  %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Affichage */
    init_fond(renderer, texture_fond);
    init_text_interface(renderer, texture_text, texte);
    map = cree_matrice(32, "Test");
    affiche_fond(renderer, texture_fond, *map);
    afficher_interface(renderer, texture_text);

    /* Arret du programme */
    while(pass){
        SDL_WaitEvent(&event);
        switch (event.type){
            case SDL_QUIT   : pass = 0; break;
            default:break;
        }
    }

    /* Fermeture de tout ce qui a été ouvert */
    quit_text_interface(texture_text);
    quit_fond(texture_fond);
    quit_SDL();
}