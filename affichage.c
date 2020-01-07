#include "projet.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// J'adore Cyril



// Affichage menu
void menu(void){
  printf("\n###############################################\n");
  printf("#  1-Afficher Logements Disponibles           #\n");
  printf("#  2-Afficher Logements Occupés               #\n");
  printf("#  3-Afficher Demandes Logements en Attente   #\n");
  printf("#  4-Attribuer Demandes à des Logements       #\n");
  printf("#  5-Création Demande Logement                #\n");
  printf("#  6-Annulation Demande Logement              #\n");
  printf("#  7-Libération Logement -> Attribution Auto  #\n");
  printf("#  8-Sauvegarde                               #\n");
  printf("#  9-Quitter                                  #\n");
  printf("###############################################\n\n");
}


void triBulle(Logement* *tabLoge,int nb){
  int i, cpt=0;
  Logement* logementReserve;
  if(nb==0 || nb==1) return;
  for(i=0;i<nb-1;i++){
    if(strcmp(tabLoge[i]->cite,tabLoge[i+1]->cite)>0){
      logementReserve=tabLoge[i+1];
      tabLoge[i+1]=tabLoge[i];
      tabLoge[i]=logementReserve;
      cpt++;
    }
  }
  if(cpt!=0){
    triBulle(tabLoge,nb-1);
  }
}

void affichLogeOccup(Logement* *tabLoge, int nbLoge){
  int i;
  triBulle(tabLoge,nbLoge);
  for(i=0;i<nbLoge;i++){
    if(tabLoge[i]->idEtudOccup!=NULL){
      printf("%s\t%s\t%s\t%d\t%d\t%s\n",tabLoge[i]->idLoge, tabLoge[i]->cite, tabLoge[i]->type, tabLoge[i]->handicapAdapte, tabLoge[i]->dispo, tabLoge[i]->idEtudOccup);
    }
  }
}

// Menu -> 2)
/*void affichLogeOccup(Logement *tabLoge[], int nbLoge){
  int i;
  for(i=0;i<nbLoge;i++){
  if(tabLoge[i]->idEtudOccup!=NULL){ // mettre * si tableau de pointeurs
  printf("%s\t%s\t%s\t%d\t%d\t%s\n",tabLoge[i]->idLoge, tabLoge[i]->cite, tabLoge[i]->type, tabLoge[i]->handicapAdapte, tabLoge[i]->dispo, tabLoge[i]->idEtudOccup);
  }
  }
  }
*/

// Menu -> 1)
void affichLogeDispo(Logement* *tabLoge, int nbLoge){
  int i;
  for(i=0;i<nbLoge;i++){
    if(tabLoge[i]->idEtudOccup==NULL){ // mettre * si tableau de pointeurs
      printf("%s\t%s\t%s\t%d\t%d\n",tabLoge[i]->idLoge, tabLoge[i]->cite, tabLoge[i]->type, tabLoge[i]->handicapAdapte, tabLoge[i]->dispo);
    }
  }
}
