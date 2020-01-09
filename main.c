#define TAILLE 100
#include "projet.h"

void appli(void){
  char choix='0'; // Choix dans le menu
  char confirmQuit='X';
  char saveDone='0';
  FILE *feLoge;
  Logement* tabLoge;
  int nbLoge,i;
  feLoge=fopen("logements.don","r");
  
  if(feLoge==NULL){
    printf("Erreur ouverture fichier \"logements.don\"\n");
    return;
  }
  
  tabLoge=chargeLogement(feLoge,&nbLoge);
  fclose(feLoge);
	
  menu();
  scanf("%c%*c",&choix);
	while(!(choix=='9' && saveDone=='1')){
	  if(choix=='1'){
	    //triBulle(tabLoge,nbLoge);
	    for(i=0;i<nbLoge;i++){
	      // printf("%s",tabLoge[i].type);
	      if(tabLoge[i].dispo==0){
		affichLogeDispo(tabLoge[i]);
	      }
	    }
	  }
	  else if(choix=='2'){
	    for(i=0;i<nbLoge;i++){
	      affichLogeOccup(tabLoge[i]);
	    }
	  }
	  else if(choix=='3'){
	  }
	  else if(choix=='4'){
	    saveDone='0';
	  }
	  else if(choix=='5'){
	    saveDone='0';
	  }
	  else if(choix=='6'){
	    saveDone='0';
	  }
	  else if(choix=='7'){
	    saveDone='0';
	  }
	  else if(choix=='8'){
	    saveDone='1';
	  }
	  else if(choix=='9'){
	    if(saveDone=='0'){
	      printf("Vous n'avez pas sauvegardé, voulez-vous quand même quitter l'application ? (O/N)\n");
	      scanf("%c%*c",&confirmQuit);
	      if(confirmQuit=='O' || confirmQuit=='o'){
		saveDone='1';
	      }
	    }
	  }
	  else{
	    printf("Erreur: valeur non valide\n");
	  }
	  if(choix=='9' && saveDone=='1'){
	    printf("La bise <3\n");
	    return;
	  }
	  menu();
	  scanf("%c%*c",&choix);
	}
}
	  
int main(void){
  appli();
  return 0;
}
