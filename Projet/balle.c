#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "map.h"

#define RAYONBALLE 3
#define DEGTORAD 0.0174533

void creer_balle(int *p, int x, int y){
  //*(p + y*TX + x - 1*TX    ) = 1;
  //*(p + y*TX + x        - 1) = 1;
  *(p + y*TX + x           ) = BALLE;
  //*(p + y*TX + x        + 1) = 1;
  //*(p + y*TX + x + 1*TX    ) = 1;
}

double detecte_mur(int *p, int x, int y){
  double i ;
  double angle = 0 ;
  double cptangle = 0 ;
  double xa, ya ;

  for(i = 0 ; i < 360 ; i += 15){
//  printf("%d",*(p + x + y*TX + (int)(cos(i * DEGTORAD) * RAYONBALLE) + (int)(sin(i * DEGTORAD) * RAYONBALLE) * TX) );
    if(*(p + x + y*TX + (int)(cos(i * DEGTORAD) * RAYONBALLE) + (int)(sin(i * DEGTORAD) * RAYONBALLE) * TX) == MUR){
      return(i);
      angle += i  ;
      cptangle++ ;
      printf("Angle : %.1f ; Cpt : %.1f\n",angle,cptangle);
    }
  }
  if(cptangle == 0)
    return(-1) ;
  return(angle / cptangle) ;
}

// Où r est le rayon de la balle
double detecte_murfinal(int *p, int x, int y, int r){
  FILE *f;
  f = fopen("menfou.txt","a");
  int i, j;
  double xmoy = 0, ymoy = 0, cpt = 0;
  for(i = r * -1 ; i < r ; i++){
    for(j = r * -1 ; j < r ; j++){
      if(*(p + y * TY + x + i * TY + j) == MUR){
        fprintf(f,"Pos collision : ( %d ; %d ) & Valeur case pointée : %d\n",x+i,y+j,*(p + y * TY + x + i * TY + j));
        xmoy += (double)j;
        ymoy += (double)i;
        cpt += 1;
      }
    }
  }
  fprintf(f,"Position de la balle : %d %d   |   Moyenne des collisions : %.2f %.2f   |   compteur : %.1f\n\n",x,y,xmoy,ymoy,cpt);
  if(cpt == 0)
    return(-1);
  xmoy /= cpt;
  ymoy /= cpt;
  fprintf(f,"Angle retourné : %.2f\n",atan(xmoy / ymoy));
  double angle = atan(xmoy / ymoy);
  angle /= DEGTORAD;
  if(angle < 0)
    angle += 360;
  fprintf(f,"Angle renvoyé : %.2f\n",angle);
    return(angle);
  fclose(f);
}















//menfou
