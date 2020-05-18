/* Réunir dans le main principal */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "menu.h"

int main(){
    /* Démarrage SDL */
    init_SDL(SDL_INIT_VIDEO, IMG_INIT_PNG);  

    /* Variable */
    SDL_Renderer *renderer;
    SDL_Window *fenetre = NULL;                        
    t_menu *menu = NULL; 
    SDL_Texture *texture[NB_MENU];
    int pass = 1, def = 0, tmp_def;

    /* Allocation */
    menu = malloc(sizeof(t_menu));

    /* Vérification */
    fenetre = SDL_CreateWindow("GolfIt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN );
    if(fenetre == NULL){
        fprintf(stderr, "[-] SDL_CreateWindow : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        fprintf(stderr, "[-] SDL_CreateRenderer :  %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    
    /* Initialisation des Texture du menu */
    init_menu(renderer, texture);
    menu = cree_menu(&menu, GOLF, "Menu Principal");
    tmp_def = GOLF;
    while (pass){
        afficher_menu(menu, renderer, texture);
        while (tmp_def == def){
            event_SDL(menu, renderer, texture, &def);
        }
        if(tmp_def != def){
            if(def == QUITTER){
                pass = 0;
            }
            else{
                *menu = menu_suivant(menu, def);
                tmp_def = def;                
            }
        }
    }

    /* Destruction des menus et libération de la mémoire */
    detruire_menu(&menu);
    quit_menu(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    quit_SDL();
    return EXIT_SUCCESS;
}