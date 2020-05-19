/**
 * \file fonction.c
 * \brief Interface de Jeu
 * \author Baptiste DUBIN
 * \version 5
 * \date 10/05/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

    /* Paramètre de la fenêtre */
#define LARGEUR_FENETRE 1024
#define HAUTEUR_FENETRE 864

    /* Paramètre du fond */
#define DARK "IMG/FOND/Dark/texture_09.png"
#define LIGHT "IMG/FOND/Light/texture_08.png"


#define BOUTON "IMG/buttons.png"
#define POLICE "data/arial.ttf"

typedef struct t_matrice    
{
    SDL_Rect** matrice;     // Matrice de Jeu
    int taille;             // Taille de la matrice de jeu
}s_matrice;

typedef struct t_map
{
    char* nom;              // Nom de la carte          
    s_matrice matrice;
}s_map;

    /* Initialisation et Fermeture des module SDL */
int init_SDL(int type, int flag);
void quit_SDL();

    /* Boite a Outil */
int img_texture(SDL_Renderer *renderer, const char *chemin_img, SDL_Texture **texture_dest);
int texte_texture(SDL_Renderer *renderer, char *texte, char *chemin_police, int taille_police, SDL_Color couleur, SDL_Texture **texture_dest);

    /* Initialisation, affichage et fermeture du fond */
int init_fond(SDL_Renderer *renderer, SDL_Texture **texture);
int affiche_fond(SDL_Renderer *renderer, SDL_Texture **texture, s_map map);
void quit_fond(SDL_Texture **texture);

    /* Création de la matrice */
s_map* cree_matrice(int taille, char *nom);

    /* Création et Fermeture de la texture texte */
int init_text_interface(SDL_Renderer *renderer, SDL_Texture **texture, char **texte);
void quit_text_interface(SDL_Texture **texture);
    
    /* Affichage de l'interface */
int affiche_barre_menu(SDL_Renderer *renderer);
int afficher_texte(SDL_Renderer *renderer, SDL_Rect position_rec, SDL_Texture *texte);
SDL_Texture *degrade(SDL_Renderer *renderer);
int barre_puissance(SDL_Renderer *renderer, SDL_Rect position_rec);
void afficher_interface(SDL_Renderer *renderer, SDL_Texture **texture);
