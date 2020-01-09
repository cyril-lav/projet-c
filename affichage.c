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


void triBulle(Logement* tabLoge[],int nb){
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

void affichLogeOccup(Logement loge){
  printf(" %s %s\t%s\t%d %d \t/*%s*/ \n",loge.idLoge,loge.cite,loge.type,loge.handicapAdapte,loge.dispo/*,loge.idEtudOccup*/);
}
  

// Menu -> 1)
void affichLogeDispo(Logement loge){
  printf(" %s ",loge.idLoge);
  printf("\t\t\t\t\t\t\t||idLoge||\n");
  printf(" %s ",loge.cite);
  printf("\t\t\t||cite||\n");
  printf(" %s ",loge.type);
  printf("\t\t\t\t\t\t\t||type||\n");
  printf(" %d ",loge.handicapAdapte);
  printf("\t\t\t\t\t\t\t||handicapAdapte||\n");
  printf(" %d ",loge.dispo);
  printf("\t\t\t\t\t\t\t||dispo||\n\n");
}

// printf(" %s\n||%s\n\t%s\n || \t%d || %d\n",loge.idLoge,loge.cite,loge.type,loge.handicapAdapte,loge.dispo);
