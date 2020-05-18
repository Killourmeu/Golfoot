/**
 * \file menu.c
 * \brief Création et affichage du menu
 * \author Baptiste DUBIN
 * \version 2
 * \date 08/05/2020
*/

#include "menu.h"

/**
 * \fn init_SDL(int type, int flag)
 * \brief Initialise les modules SDL
 * \param type Sous système
 * \param flag Format image
 * \return 0 si marche
*/

int init_SDL(int type, int flag){

    /* Initialisation des modules SDL */

    if(SDL_Init(type) != 0){
        fprintf(stderr, "[-]SDL_Init : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if((IMG_Init(flag) & flag )!= flag){
        fprintf(stderr, "[-]IMG_Init: %s!\n", IMG_GetError());
        return EXIT_FAILURE;
    }

    if(TTF_Init() != 0){
        fprintf(stderr, "[-]TTF_Init: %s!\n", TTF_GetError());        
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * \fn void quit_SDL()
 * \brief Ferme les module SDL
*/

void quit_SDL(){
    /* Fermeture des modules SDL */
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

/**
 * \fn int creation_chemin_img (char *ajout, char **res)
 * \brief Copie d'une chaîne dans une autre
 * \param src Chaine a copier
 * \param dest Destination de la copie
 * \return 0 si marche
*/

int creation_chemin_img (char *src, char **dest){ 
    /* Vérification */
    if (!src || !dest){
        return EXIT_FAILURE;
    }

    /* Copie */
    *dest = malloc(sizeof(char) * strlen(src) + 1);
    strcpy(*dest, src);

    return EXIT_SUCCESS;
}

/**
 * \fn int img_texture(SDL_Renderer *renderer, const char *chemin_img, SDL_Texture **texture_dest){
 * \brief Créé une texture a partir d'une image
 * \param renderer Renderer de la fenêtre
 * \param chemin_img Chemin d'accès a l'image
 * \param texture_dest Texture destination
 * \return 0 si marche
*/

int img_texture(SDL_Renderer *renderer, const char *chemin_img, SDL_Texture **texture_dest){
    /* Vérification */
    if(!renderer || !texture_dest){
        fprintf(stderr, "[-]img_texture : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    /* Création Texture */

    *texture_dest = IMG_LoadTexture(renderer, chemin_img);

    if(!texture_dest){
        fprintf(stderr, "[-]img_texture : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * \fn int texte_texture(SDL_Renderer *renderer, char *texte, char *chemin_police, int taille_police, SDL_Color couleur, SDL_Texture **texture_dest)
 * \brief Créé une texture a partir d'une police/textte
 * \param renderer Renderer de la fenêtre
 * \param texte Texte source
 * \param chemin_police Chemin d'accès a la police
 * \param taille_police Taille de la Police
 * \param couleur Couleur du texte
 * \param texture_dest Texture destination
 * \return 0 si marche
*/

int texte_texture(SDL_Renderer *renderer, char *texte, char *chemin_police, int taille_police, SDL_Color couleur, SDL_Texture **texture_dest){
    /* Vérification */
    if(!renderer || !texture_dest){
        fprintf(stderr, "[-]texte_texture : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Création police */
    TTF_Font *police = TTF_OpenFont(chemin_police, taille_police);
    if(!police){
        fprintf(stderr, "[-]texte_texture : %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    /* Création Surface */
    SDL_Surface *texte_surface = TTF_RenderText_Blended(police, texte, couleur);
    if(!texte_surface){
        fprintf(stderr, "[-]texte_texture : %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    /* Création Texture */
    *texture_dest = SDL_CreateTextureFromSurface(renderer, texte_surface);
    if(!*texture_dest){
        fprintf(stderr, "[-]texte_texture : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Destruction pointeur */
    SDL_FreeSurface(texte_surface);
    TTF_CloseFont(police);

    return EXIT_SUCCESS;
}

/**
 * \fn int init_menu(SDL_Renderer *renderer, SDL_Texture **texture)
 * \brief Initialise les texture du menu
 * \param renderer Renderer de la fenêtre
 * \param texture Stockage des texture
 * \return 0 si marche
*/

int init_menu(SDL_Renderer *renderer, SDL_Texture **texture){

    /* Initialise les texture du menu */

    img_texture(renderer, FOND, &(texture[0]));
    if(!texture[0]){
        fprintf(stderr, "[-]init_menu : %s\n", IMG_GetError());
    }

    img_texture(renderer, BOUTON, &(texture[1]));
    if(!texture[1]){
        fprintf(stderr, "[-]init_menu : %s\n", IMG_GetError());
    }

    return EXIT_SUCCESS;
}

/**
 * \fn void quit_menu(SDL_Texture **texture)
 * \brief Libère les texture d'affichage
 * \param texture Stockage des texture
*/

void quit_menu(SDL_Texture **texture){
    for(int i = 0; i < NB_MENU; i++)
        SDL_DestroyTexture(texture[i]);
}

/**
 * \fn int cree_button(SDL_Rect position, char *titre, t_menu *menu, t_opt_menu def)
 * \brief Initialise les texture du menu
 * \param position Position du bouton
 * \param titre Titre du bouton
 * \param def Titre du menu correspondant
 * \return 0 si marche
*/

int cree_button(SDL_Rect position, char *titre, t_menu *menu, t_opt_menu def){
    /* Vérification */
    if(position.h < 0 || position.w < 0 || position.x < 0 || position.y < 0 || position.x > LARGEUR_FENETRE || position.y > HAUTEUR_FENETRE){
        fprintf(stderr, "[-]cree_button : %s\n", SDL_GetError());
        return EXIT_FAILURE;        
    }
    if(!menu){
        fprintf(stderr, "[-] cree_button : menuLL.\n");
        return EXIT_FAILURE;
    }


    t_boutton *boutton = malloc(sizeof(t_boutton));     // Bouton tempon
    if(!boutton){
        fprintf(stderr, "[-]cree_button : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Copie des informations dans le bouton */
    if(titre){
        boutton->titre = malloc(sizeof(char) * strlen(titre) + 1);
        strcpy(boutton->titre, titre);
    }

    boutton->position.h = position.h;
    boutton->position.w = position.w;
    boutton->position.x = position.x;
    boutton->position.y = position.y;

    if(menu->tableau_boutton == NULL){
        menu->tableau_boutton = malloc(sizeof(t_menu));
    } 
    else{
        menu->tableau_boutton = realloc(menu->tableau_boutton, (menu->nb_button + 1) * sizeof(t_menu));
    }

    /* Copie du bouton dans le menu */
    menu->tableau_boutton[menu->nb_button] = boutton;
    menu->nb_button++;

    return EXIT_SUCCESS;
}

/**
 * \fn t_menu *cree_menu(t_menu **menu, t_opt_menu def, char *titre)
 * \brief Création du menu
 * \param menu Menu source
 * \param def Titre du menu correspondant
 * \param titre Titre du bouton
 * \return Le menu
*/

t_menu *cree_menu(t_menu **menu, t_opt_menu def, char *titre){
    /* Vérification */
    if(!menu){
        printf("[-] cree_button : menuLL.\n");
    }

    /* Variable */
    int ecart = 40;
    SDL_Rect position;

    /* Copie des informations dans le menu */
    (*menu)->def = def;
    (*menu)->titre = malloc(sizeof(char) * strlen(titre) + 1);
    strcpy((*menu)->titre, titre);
    (*menu)->nb_button = 0;

    /* Position du bouton sur le menu */
    position.w = LARGEUR_FENETRE / 185;
    position.h = HAUTEUR_FENETRE / 10;
    position.x = ((LARGEUR_FENETRE - (position.w * 2)) / 2) + 20;
    position.y = (15 * position.w);

    
    /* Création du menu selon la définitions */
    if(def == GOLF){
        cree_button(position, "Jouer", *menu, JOUER);
        position.y += position.h + ecart;              

        cree_button(position, "Options", *menu, OPTIONS);
        position.y += position.h + ecart;

        cree_button(position, "Aide", *menu, AIDE);
        position.y += position.h + ecart;

        cree_button(position, "Quitter", *menu, QUITTER);
        position.y += position.h + ecart;        
    }
    
    else if(def == JOUER){
        cree_button(position, "Solo", *menu, SOLO);
        position.y += position.h + ecart;

        cree_button(position, "Duo", *menu, DUO);
        position.y += position.h + ecart;

        cree_button(position, "Retour", *menu, RETOUR);
        position.y += position.h + ecart;
    }

    else if(def == SOLO){
        cree_button(position, "Aventure", *menu, AVENTURE);
        position.y += position.h + ecart;

        cree_button(position, "Creation", *menu, CREATION);
        position.y += position.h + ecart;

        cree_button(position, "Chargement", *menu, CHARGEMENT);
        position.y += position.h + ecart;

        cree_button(position, "Retour", *menu, RETOUR);
        position.y += position.h + ecart;
    }

    else if(def == DUO){
        cree_button(position, "Chargement", *menu, CHARGEMENT);
        position.y += position.h + ecart;

        cree_button(position, "Selection", *menu, SELECION);
        position.y += position.h + ecart;

        cree_button(position, "Retour", *menu, RETOUR);
        position.y += position.h + ecart;
    }
    /* Création d'une fonction pour les options de jeu car trop long a écrire */
    else{
        (*menu)->tableau_boutton = NULL;
        detruire_menu(menu);  
    }
    return *menu;
}

/**
 * \fn int detruire_boutton(t_boutton **boutton)
 * \brief Déstruction du boutton
 * \param boutton Boutton
 * \return 0 si marche
*/
int detruire_boutton(t_boutton **boutton){
    /* Vérification */
    if(!boutton){
        fprintf(stderr, "[-]detruire_boutton : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    if((*boutton)->titre){
        free((*boutton)->titre);
    }

    /* Libération de la mémoire */
    free(*boutton);
    *boutton = NULL;
    
    return EXIT_SUCCESS;
}

/**
 * \fn int detruire_menu(t_menu **menu)
 * \brief Déstruction du menu
 * \param menu Menu
 * \return 0 si marche
*/

int detruire_menu(t_menu **menu){
    /* Vérification */
    if(!menu){
        fprintf(stderr, "[-] detruire_menu : menuLL.\n");
        return EXIT_FAILURE;
    }

    if((*menu)->titre){
        free((*menu)->titre);
    }

    if((*menu)->tableau_boutton){
        for(int i = 0; i < (*menu)->nb_button; i++){
            detruire_boutton(&((*menu)->tableau_boutton[i]));
        }
        free((*menu)->tableau_boutton);
    }

    free(*menu);
    *menu = NULL;
    return EXIT_SUCCESS;
}

/**
 * \fn int afficher_menu_titre(t_menu *menu, SDL_Renderer *renderer)
 * \brief Affichage du titre du jeu dans la fenêtre
 * \param menu Menu
 * \param renderer Renderer
 * \return 0 si marche
*/

int afficher_menu_titre(t_menu *menu, SDL_Renderer *renderer){
    /* Vérification*/
     if(!menu || !renderer){
        fprintf(stderr, "[-] afficher_menu_titre : %s.\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Variable */
    int taille_police = 70;
    char *police, *txt = "GolFoot";
    SDL_Texture *texte;
    SDL_Rect fenetre = {260, 40, taille_police * strlen(txt), taille_police};
    SDL_Color blanc = {255, 255, 255};

    creation_chemin_img(POLICE, &police);       // Allocation du chemin de la police
    texte_texture(renderer, txt, police, taille_police, blanc, &texte);         // Création de la texture du titre

    if(SDL_RenderCopy(renderer, texte, NULL, &fenetre) != 0){                // Copie dans le renderer
        fprintf(stderr, "[-] afficher_menu_titre : %s.\n", SDL_GetError());
    }

    SDL_RenderPresent(renderer);        // Affichage

    /* Libération de la mémoire */
    SDL_DestroyTexture(texte);
    free(police);
    return EXIT_SUCCESS;
}

/**
 * \fn int afficher_menu(t_menu *menu, SDL_Renderer *renderer, SDL_Texture **texture)
 * \brief Affichage du Menu dans la fenêtre
 * \param menu Menu
 * \param renderer Renderer
 * \param texture Stockage des texture
 * \return 0 si marche
*/

int afficher_menu(t_menu *menu, SDL_Renderer *renderer, SDL_Texture **texture){
    /* Vérification */
    if(!menu || !renderer || !menu->tableau_boutton){
        fprintf(stderr, "[-] afficher_menu : %s.\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Variable */
    int i, taille_police = 35, pos_y_txt = 155;
    char *police;
    SDL_Texture *texte;
    SDL_Rect r_fenetre = {0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE};
    SDL_Rect r_img, r_txt;
    SDL_Color blanc = {255, 255, 255};


    creation_chemin_img(POLICE, &police);

    /* Copie et affichage du fond du menu */
    if(SDL_RenderCopy(renderer, texture[0], NULL, &r_fenetre) != 0){
        fprintf(stderr, "[-] afficher_menu : %s.\n", SDL_GetError());
    }

    SDL_RenderPresent(renderer);
    afficher_menu_titre(menu, renderer);
   
    for(i = 0; i < menu->nb_button; i++){
        /* Position de l'image du boutton */
        r_img.x = (LARGEUR_FENETRE / 2) - (LARGEUR_FENETRE / 4);
        r_img.y =  menu->tableau_boutton[i]->position.y + 10;
        r_img.w = LARGEUR_FENETRE / 2 + 75;
        r_img.h = menu->tableau_boutton[i]->position.h * 4;

        /* Position de texte du boutton */
        r_txt.w =  taille_police * strlen(menu->tableau_boutton[i]->titre);
        r_txt.h = taille_police;
        r_txt.x = (r_img.x / 2) + (r_img.w / 2);
        r_txt.y = pos_y_txt;

        pos_y_txt += 90;

        texte_texture(renderer, menu->tableau_boutton[i]->titre, police, taille_police, blanc, &texte);     // Création de la texture du texte
        
        if(SDL_RenderCopy(renderer, texture[1], NULL, &r_img) != 0){                                                // Copie de l'image en premier
            fprintf(stderr, "[-] afficher_menu : %s.\n", SDL_GetError());
        }                                                        
        if(SDL_RenderCopy(renderer, texte, NULL, &r_txt) != 0){                                                     // Copie de texte par dessus
            fprintf(stderr, "[-] afficher_menu : %s.\n", SDL_GetError());
        }                                                            
        SDL_RenderPresent(renderer);                                                                                // Affichage
        SDL_DestroyTexture(texte);                                                                                  // Destruction du texte
    }
    
    /* Libération de la mémoire */
    free(police);

    return EXIT_SUCCESS;
}

/**
 * \fn int event_SDL(t_menu *menu, SDL_Renderer *renderer, SDL_Texture **texture)
 * \brief Récupération des évènement du menu
 * \param menu Menu
 * \param renderer Renderer
 * \param texture Stockage des texture
 * \param def Nom du menu suivant
 * \return 0 si marche
*/

void event_SDL(t_menu *menu, SDL_Renderer *renderer, SDL_Texture **texture, int *def){
    /* Vérification */
    if(!menu || !renderer){
        fprintf(stderr, "[-] event_SDL : %s.\n", SDL_GetError());
    }
    
    /* Variable */
    SDL_Event event;
    SDL_WaitEvent(&event);
    switch (event.type){
        case SDL_QUIT   : break;
        case SDL_MOUSEBUTTONUP:
            if(SDL_BUTTON (SDL_BUTTON_LEFT)){
                if(menu->def == GOLF){
                    if (event.button.x > 245 && event.button.x < 745 && event.button.y > 135 && event.button.y < 205){
                        // Lancer Jouer
                        *def = JOUER;
                        printf("Jouer Marche\n");
                        break;
                    }
                    if (event.button.x > 245 && event.button.x < 745 && event.button.y > 225 && event.button.y < 295){
                        // Lancer Options
                        *def = OPTIONS;
                        printf("Options Marche\n");
                        break;
                    }
                    if (event.button.x > 245 && event.button.x < 745 && event.button.y > 315 && event.button.y < 385){
                        // Lancer Aide
                        *def = AIDE;
                        printf("Aide Marche\n");
                        break;
                    }
                    if (event.button.x > 245 && event.button.x < 745 && event.button.y > 410 && event.button.y < 485){
                        // Quitter
                        *def = QUITTER;
                        printf("A+\n");
                    }
                }
                else if(menu->def == JOUER){
                    if (event.button.x > 245 && event.button.x < 745 && event.button.y > 135 && event.button.y < 205){
                        // Lancer Aventure
                        *def = SOLO;
                        printf("Solo Marche\n");
                        break;
                    }
                    if (event.button.x > 245 && event.button.x < 745 && event.button.y > 225 && event.button.y < 295){
                        // Lancer Création
                        *def = DUO;
                        printf("Duo Marche\n");
                        break;
                    }
                   if (event.button.x > 245 && event.button.x < 745 && event.button.y > 315 && event.button.y < 385){
                        // Lancer Retour
                        *def = GOLF;
                        printf("Retour Marche\n");
                        break;
                    }
                }
                else if (menu->def == SOLO){
                    if (event.button.x > 245 && event.button.x < 745 && event.button.y > 135 && event.button.y < 205){
                        // Lancer Aventure
                        *def = AVENTURE;
                        printf("Aventure Marche\n");
                        break;
                    }
                    if (event.button.x > 245 && event.button.x < 745 && event.button.y > 225 && event.button.y < 295){
                        // Lancer Création
                        *def = CREATION;
                        printf("Création Marche\n");
                        break;
                    }
                    if (event.button.x > 245 && event.button.x < 745 && event.button.y > 315 && event.button.y < 385){
                        // Lancer Chargement
                        printf("Chargement Marche\n");
                        *def = CHARGEMENT;
                        break;
                    }
                    if (event.button.x > 245 && event.button.x < 745 && event.button.y > 410 && event.button.y < 485){
                        // Lancer Retour
                        *def = JOUER;
                        printf("Retour Marche\n");
                        break;
                    }
                }
                else if (menu->def == DUO){
                    if (event.button.x > 245 && event.button.x < 745 && event.button.y > 135 && event.button.y < 205){
                        // Lancer Chargement
                        *def = CHARGEMENT;
                        printf("Chargement Marche\n");
                        break;
                    }
                    if (event.button.x > 245 && event.button.x < 745 && event.button.y > 225 && event.button.y < 295){
                        // Lancer Séléction
                        *def = SELECION;
                        printf("Séléction Marche\n");
                        break;
                    }
                   if (event.button.x > 245 && event.button.x < 745 && event.button.y > 315 && event.button.y < 385){
                        // Lancer Retour
                        *def = JOUER;
                        printf("Retour Marche\n");
                        break;
                    }
                }
            }
            break;
        default:break;
    }
} 

/**
 * \fn t_menu menu_suivant(t_menu *menu, int def)
 * \brief Menu suivant
 * \param menu Menu
 * \param def Nom du menu suivant
 * \return Un menu
*/

t_menu menu_suivant(t_menu *menu, int def){
    t_menu *menu_tmp = NULL;

    menu_tmp = malloc(sizeof(t_menu));
    menu_tmp = cree_menu(&menu, def, menu->titre);

    return *menu_tmp;
}