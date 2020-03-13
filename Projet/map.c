#include <stdio.h>
#include <stdlib.h>

#define TX 240
#define TY 80

typedef enum{
  VIDE, MUR, BALLE, TRAINEE
}map_objet;

int *lire_map(char *s){ // Récupère la map en .txt
  FILE *f;
  f = fopen(s,"r");
  int *p = malloc(sizeof(int) * TX * TY);
  int i;
  for(i = 0 ; !feof(f) ; i++)
    fscanf(f,"%i",(p+i));
  fclose(f);
  return(p);
}

void aff_map(int *p){ // Affiche la matrice map
  int i;
  printf("\n");
  for(i = 0 ; i < TX * TY ; i++){
    switch(*(p+i)){
      case VIDE : printf(" "); break;
      case MUR : printf("\u2588"); break;
      case BALLE : printf("#"); break;
      case TRAINEE : printf("*"); break;
    }
  }
}

int case_valide(int *p, int x, int y){
  if(y < TY && y > 0 && x > 0 && x < 240)
    return(1);
  return(0);
}
