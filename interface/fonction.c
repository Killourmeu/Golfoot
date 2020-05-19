/**
 * \file fonction.c
 * \brief Interface de Jeu
 * \author Baptiste DUBIN
 * \version 5
 * \date 10/05/2020
*/

#include "fonction.h"

SDL_Color noir = {0, 0, 0};
SDL_Color rouge = {255, 0, 0};
SDL_Color vert = {0, 255, 0};
SDL_Color bleu = {0, 0, 255};
SDL_Color blanc = {255, 255, 255};


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

    if(!*texture_dest){
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
 * \fn int init_fond(SDL_Renderer *renderer, SDL_Texture **texture){
 * \brief Initialise la texture fond avec les images
 * \param renderer Renderer de la fenêtre
 * \param texture Tableau stockant les images converti en Texture
 * \return 0 si marche
*/

int init_fond(SDL_Renderer *renderer, SDL_Texture **texture){

    /* Initialise les texture du menu */

    img_texture(renderer, DARK, &(texture[0]));
    if(!texture[0]){
        fprintf(stderr, "[-]init_fond : %s\n", IMG_GetError());
    }

    img_texture(renderer, LIGHT, &(texture[1]));
    if(!texture[1]){
        fprintf(stderr, "[-]init_fond : %s\n", IMG_GetError());
    }

    return EXIT_SUCCESS;
}


/**
 * \fn void quit_fond(SDL_Texture **texture)
 * \brief Detruit les Texture fond
 * \param texture Tableau stockant les images converti en Texture
*/


void quit_fond(SDL_Texture **texture){
    /* Destruction des Texture */
    for(int i = 0; i < 2; i++)
            SDL_DestroyTexture(texture[i]);
}


/**
 * \fn s_map* cree_matrice(int taille, char *nom)
 * \brief Créé une matrice
 * \param taille taille de la matrice
 * \param nom  nom de la map
 * \return un pointeur de map
*/

s_map* cree_matrice(int taille, char *nom){
    /* Vérification */
    if(!nom){
        fprintf(stderr, "[-] cree_matrice : valeur null\n");
    }

    /* Variable */
    int i, j;
    s_map *map;
    SDL_Rect **matrice;

    map = malloc(sizeof(s_map));


    /* Création de la matrice */
    matrice = malloc(sizeof(SDL_Rect*) * taille);
    for(i = 0; i < taille; i++){
        matrice[i] = malloc(sizeof(SDL_Rect) * taille);
        matrice[i][0].y = 0;
        for(j = 0; j < taille; j++){
            if(i == 0) matrice[i][j].x = 0;
            else matrice[i][j].x = (LARGEUR_FENETRE / taille) * i;

            if(j != 0) matrice[i][j].y = (HAUTEUR_FENETRE / taille) * j;
            matrice[i][j].w = LARGEUR_FENETRE / taille;
            matrice[i][j].h = HAUTEUR_FENETRE / taille;

        }
    }

    /* Copie dans la map */
    map->nom = malloc(sizeof(char) * strlen(nom) + 1);
    strcpy(map->nom, nom);
    map->matrice.matrice = matrice;
    map->matrice.taille = taille;

    return map;
}



/**
 * \fn int affiche_fond(SDL_Renderer *renderer, SDL_Texture **texture, s_map map)
 * \brief Affiche le fond de l'interface
 * \param renderer Renderer de la fenêtre
 * \param texture Tableau stockant le Thème couleur
 * \param map information sur la map
 * \return 0 si marche
*/


int affiche_fond(SDL_Renderer *renderer, SDL_Texture **texture, s_map map){ 
    /* Vérification */
    if(!renderer){
        fprintf(stderr, "[-]affiche_fond : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Variable */
    int i, j;
    SDL_Rect position;

    for(i = 0; i < map.matrice.taille; i++){
        for(j = 0; j < map.matrice.taille; j++){
            position.x = map.matrice.matrice[i][j].x;
            position.y = map.matrice.matrice[i][j].y;
            position.w = map.matrice.matrice[i][j].w;
            position.h = map.matrice.matrice[i][j].h;

            if(SDL_RenderCopy(renderer, texture[0], NULL, &position) != 0){
                fprintf(stderr, "[-]affiche_fond : %s\n", SDL_GetError());
                return EXIT_FAILURE;
            }
        }
    }
    return EXIT_SUCCESS;
}


/**
 * \fn int affiche_barre_menu(SDL_Renderer *renderer)
 * \brief Affiche la barre blanche
 * \param renderer Renderer de la fenêtre
 * \return 0 si marche
*/


int affiche_barre_menu(SDL_Renderer *renderer){
    /* Vérification */
    if(!renderer){
        fprintf(stderr, "[-]affiche_barre_menu : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Variable */
    SDL_Rect position = {   LARGEUR_FENETRE - (LARGEUR_FENETRE / 5),
                            0, 
                            LARGEUR_FENETRE - (LARGEUR_FENETRE / 5), 
                            HAUTEUR_FENETRE};

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);       // Couleur du rectangle
    SDL_RenderFillRect(renderer, &position);                    // Position du rectangle
    SDL_RenderPresent(renderer);                                // Afichage
    SDL_Delay(1);   

    return EXIT_SUCCESS;
}


/**
 * \fn int afficher_texte(SDL_Renderer *renderer, SDL_Rect position_rec, SDL_Texture *texte)
 * \brief Affiche le Texte et leurs rectangle dans la barre_menu
 * \param renderer Renderer de la fenêtre
 * \param position_rec Position du rectangle
 * \param texte Texte à afficher
 * \return 0 si marche
*/


int afficher_texte(SDL_Renderer *renderer, SDL_Rect position_rec, SDL_Texture *texte){
    /* Vérification */
    if(!renderer){
        fprintf(stderr, "[-]afficher_texte : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Variable */
    SDL_Rect position_txt = { position_rec.x + 5, position_rec.y + 5, position_rec.w - 10, position_rec.h - 15};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);     // Couleur du bouton
    SDL_RenderFillRect(renderer, &position_rec);        // Position du bouton

    if(SDL_RenderCopy(renderer, texte, NULL, &position_txt) != 0){      // Copie du texte a la bonne position
        fprintf(stderr, "[-] afficher_texte : %s.\n", SDL_GetError());
    } 

    SDL_RenderPresent(renderer);
    SDL_Delay(1);

    return EXIT_SUCCESS;
}

/**
 * \fn SDL_Texture *degrade(SDL_Renderer *renderer)
 * \brief Creé un dégradé de couleur allant du rouge au vert
 * \param renderer Renderer de la fenêtre
 * \return Une texture
*/


SDL_Texture *degrade(SDL_Renderer *renderer){
    /* Vérification */
    if(!renderer){
        fprintf(stderr, "[-]afficher_texte : %s", SDL_GetError());
    }

    /* Variable */
    SDL_Texture *texture = NULL;
    SDL_PixelFormat *format;
    Uint32 pixels[255] = {0};
    size_t i, j;

    /* Allocation */
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
                                1, 255); 
    format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

    
    for(i = 0, j = 255; i < 255; i++, j--)
        pixels[i] = SDL_MapRGBA(format, j, i, 0, 255);
    SDL_UpdateTexture(texture, NULL, pixels, sizeof(Uint32) * 1);

    /* Libération de la mémoire */
    SDL_FreeFormat(format);
    return texture;
}

/**
 * \fn int barre_puissance(SDL_Renderer *renderer, SDL_Rect position_rec)
 * \brief Affiche le dégradé dans un recrangle pour faire une barre de puissance de tir
 * \param renderer Renderer de la fenêtre
 * \param postion_rec Position du rectangle
 * \return 0 si marche
*/

int barre_puissance(SDL_Renderer *renderer, SDL_Rect position_rec){ 
    /* Vérification */
    if(!renderer){
        fprintf(stderr, "[-]afficher_texte : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Variable */   
    SDL_Texture *ancre = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, position_rec.w, position_rec.h);
    int i, j;

    /* Mis a jour de la Texture */
    SDL_SetRenderTarget(renderer, ancre);
    ancre = degrade(renderer);
    SDL_SetRenderTarget(renderer, NULL);

    /* Affichage */
    if(SDL_RenderCopy(renderer, ancre, NULL, &position_rec) != 0){
        fprintf(stderr, "[-]barre_puissance : %s", SDL_GetError());
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(100);

    return EXIT_SUCCESS;
}


/**
 * \fn int init_text_interface(SDL_Renderer *renderer, SDL_Texture **texture, char **texte)
 * \brief Initialise le texte dans la barre de menu (blanche)
 * \param renderer Renderer de la fenêtre
 * \param texture Texture stcokant les texte
 * \param texte Texte a stocké
 * \return 0 si marche
*/

int init_text_interface(SDL_Renderer *renderer, SDL_Texture **texture, char **texte){
    /* Vérification */
    if(!renderer){
        fprintf(stderr, "[-]afficher_texte : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Initialise les texture du menu */

    texte_texture(renderer, texte[0], POLICE, 10, blanc, &texture[0]);
    if(!texture[0]){
        fprintf(stderr, "[-]init_text_interface : %s\n", SDL_GetError());
    }

    texte_texture(renderer, texte[1], POLICE, 10, blanc, &texture[1]);
    if(!texture[1]){
        fprintf(stderr, "[-]init_text_interface : %s\n", SDL_GetError());
    }

    texte_texture(renderer, texte[2], POLICE, 10, blanc, &texture[2]);
    if(!texture[2]){
        fprintf(stderr, "[-]init_text_interface : %s\n", SDL_GetError());
    }

    return EXIT_SUCCESS;
}

/**
 * \fn void quit_text_interface(SDL_Texture **texture)
 * \brief Supprime le tableau de texture du texte de la barre menu
 * \param texture Texture stcokant les texte
*/

void quit_text_interface(SDL_Texture **texture){
    for(int i = 0; i < 3; i++)
            SDL_DestroyTexture(texture[i]);
}

/**
 * \fn void afficher_interface(SDL_Renderer *renderer, SDL_Texture **texture)
 * \brief Affiche l'interface de jeu
 * \param renderer Renderer de la fenêtre
 * \param texture Texture stockant les texte
*/



void afficher_interface(SDL_Renderer *renderer, SDL_Texture **texture){
    /* Vérification */
    if(!renderer){
        fprintf(stderr, "[-]afficher_texte : %s", SDL_GetError());
    }

    /* Variable */
    int w = LARGEUR_FENETRE / 10 + 30;
    int h = 40;
    int x = (LARGEUR_FENETRE / 5); 
    x = LARGEUR_FENETRE - (3* x / 4) - 15;

    /* Position de l'affichage */
    SDL_Rect position_joueur = {x, 0, w, h};
    SDL_Rect position_puissance = {x, 65, w, h};
    SDL_Rect position_trou = {x, 800, w, h};
    SDL_Rect position_barre = {835, 110, LARGEUR_FENETRE / 10 + 70, 650};

    /* Affichage */
    affiche_barre_menu(renderer);
    afficher_texte(renderer, position_puissance, texture[0]);
    afficher_texte(renderer, position_trou, texture[1]);
    afficher_texte(renderer, position_joueur, texture[2]);
    barre_puissance(renderer, position_barre);
}
