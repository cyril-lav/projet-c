#define TAILLE 30
#include "projet.h"

void appli(void){
  char choix='0'; // Choix dans le menu
  char confirmQuit='X';
  char saveDone='0';
  FILE *feLoge;
  Logement *tabLoge[TAILLE];
  int nbLoge;
  feLoge=fopen("logements.don","r");
  if(feLoge==NULL){
    printf("Erreur ouverture fichier \"logements.don\"\n");
    return;
  }


	
  menu();
  scanf("%c%*c",&choix);
	while(!(choix=='9' && saveDone=='1')){
	  switch(choix){
	  case '1':
	    affichLogeDispo(tabLoge, nbLoge);
	  case '2':
	    affichLogeOccup(tabLoge, nbLoge);
	  case '3':
	    break;
	  case '4':
	    saveDone='0';
	    break;
	  case '5':
	    saveDone='0';
	    break;
	  case '6':
	    saveDone='0';
	    break;
	  case '7':
	    saveDone='0';
	    break;
	  case '8':
	    saveDone='1';
	    break;
	  case '9':
	    if(saveDone=='0'){
	      printf("Vous n'avez pas sauvegardé, voulez-vous quand même quitter l'application ? (O/N)\n");
	      scanf("%c%*c",&confirmQuit);
	      if(confirmQuit=='O' || confirmQuit=='o'){
		saveDone='1';
	      }
	    }
	    break;
	  default:
	    printf("Erreur: valeur non valide\n");
	  }
	  if(choix=='9' && saveDone=='1'){
	    printf("La bise <3\n");
	    return;
	  }
	  menu();
	  scanf("%c%*c",&choix);
	}
	return;
}

int main(void){
  int nbLoge;
  Logement tabLoge[TAILLE];
  FILE *fe;
  fe=fopen("logements.don","r");
  if(fe==NULL){
    printf("pb ouv fichier\n");
    return -1;
  }
  nbLoge=chargeLogement(tabLoge,100,fe);
  // appli();
}
