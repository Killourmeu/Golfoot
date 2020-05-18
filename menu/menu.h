/**
 * \file menu.h
 * \brief Création et affichage du menu (Header)
 * \author Baptiste DUBIN
 * \version 2
 * \date 08/05/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

    /* Information sur la fenetre */
#define LARGEUR_FENETRE 915
#define HAUTEUR_FENETRE 500

    /* Source des fichiers externes */
#define FOND "IMG/Sample.png"
#define BOUTON "IMG/buttons.png"
#define POLICE "data/golf_police.ttf"

    /* Autre */
#define NB_MENU 2

/**
 * \enum t_opt_menu
 * \brief Contient les différents types de menus possibles
*/
typedef enum t_opt_menu
{
    GOLF,
    JOUER,
    OPTIONS,
    AIDE,
    QUITTER,
    SOLO,
    DUO,
    AVENTURE,
    CREATION,
    CHARGEMENT,
    SELECION,
    SUPPRIMER,
    RETOUR
}t_opt_menu;

/**
 * \struct t_boutton
 * \brief Contient les informations d'un bouton
*/
typedef struct t_boutton
{
    char *titre;
    SDL_Rect position;
}t_boutton;

/**
 * \struct t_menu
 * \brief Contient l'ensemble des boutons appartenant au menu
*/
typedef struct t_menu
{
    t_opt_menu def;
    char *titre;
    int nb_button;
    t_boutton **tableau_boutton;
    // Ajout d'une liste chainé a la structure pour connaitre les possible menu suivant
}t_menu;
 
    /* Initialisation et Fermeture des module SDL */
int init_SDL(int type, int flag);
void quit_SDL();

    /* Boite a Outil */
int creation_chemin_img (char *src, char **dst);
int img_texture(SDL_Renderer *renderer, const char *chemin_img, SDL_Texture **texture_dest);
int texte_texture(SDL_Renderer *renderer, char *texte, char *chemin_police, int taille_police, SDL_Color couleur, SDL_Texture **texture_dest);

    /* Ouverture et fermeture des texture du menu */
int init_menu(SDL_Renderer *renderer, SDL_Texture **texture);
void quit_menu(SDL_Texture **menu_texture);

    /* Création et destruction d'un boutton */
int cree_button(SDL_Rect position, char *titre, t_menu *menu, t_opt_menu def);
int detruire_boutton(t_boutton **boutton);

    /* Création et destruction du menu */
t_menu *cree_menu(t_menu **menu, t_opt_menu def, char *titre);
int detruire_menu(t_menu **menu);

    /* Affichage du menu */
int afficher_menu(t_menu *menu, SDL_Renderer *renderer, SDL_Texture **texture);
int afficher_menu_titre(t_menu *menu, SDL_Renderer *renderer);
t_menu menu_suivant(t_menu *menu, int def);

    /* Gestion des évènements */
void event_SDL(t_menu *menu, SDL_Renderer *renderer, SDL_Texture **texture, int *def);
