#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "balle.h"
#include "map.h"

int main(){
  const float frottement = -1.35 ;     // Constante de freinage de la balle (modifiable)
  const float refresh_rate = 0.1 ;     // Constante de précision du calcul (un calcul toutes les x secondes)
  double angle = 0 , traj ;             // Angle de la balle en degré et radian
  float vitesse ;                      // Vitesse de la balle (pour calculs)
  float x_balle = 120 , y_balle = 40 ; // Position de départ de la balle (arbitrairement le centre)
  double normale_mur ;                 // Utilisé pour déterminer la normale au mur lors de collisions

// Récupération de la map
  int *map = lire_map("map_test.txt") ;

// Lancement du jeu
  while(angle != -1){

// Sélection de l'angle du tir
    printf("Choisir l'angle du tir (-1 pour arreter) : ") ;
    scanf("%lf",&angle) ;
    if(angle != -1){
      traj = angle * DEGTORAD ;

// Sélection de la force du coup
      printf("Choisir la force du tir : ") ;
      scanf("%f",&vitesse) ;

// Tant que la balle roule, calcul de sa position & vitesse
      while(vitesse > 0){

        normale_mur = detecte_murfinal(map, (int)x_balle, (int)y_balle, 3);
        if(normale_mur > 0){
          angle += 2 * (normale_mur - angle) ;
          traj = angle * DEGTORAD ;
        }

// Calcul de la position de la balle & de sa vitesse
        x_balle += (frottement * (refresh_rate * refresh_rate) + vitesse * refresh_rate) * cos(traj) ;
        y_balle += (frottement * (refresh_rate * refresh_rate) + vitesse * refresh_rate) * sin(traj) ;
        vitesse += 2 * frottement * refresh_rate ;

        *(map + (int)x_balle + (int)y_balle * TX) = TRAINEE ;

        usleep(1000000 * refresh_rate) ;
        system("clear") ;
        aff_map(map) ;
      }
      creer_balle(map, (int)x_balle, (int)y_balle) ;
      system("clear") ;
      aff_map(map) ;
      printf("\n");
    }
  }

// Libération de l'espace mémoire alloué
  free(map) ;
}
