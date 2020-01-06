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


// Menu -> 2)
void affichLogeOccup(Logement *tabLoge[], int nbLoge){
	int i;
	for(i=0;i<nbLoge;i++){
		if(tabLoge[i]->idEtudOccup!=NULL){ // mettre * si tableau de pointeurs
			printf("%s\t%s\t%s\t%d\t%d\t%s\n",tabLoge[i]->idLoge, tabLoge[i]->cite, tabLoge[i]->type, tabLoge[i]->handicapAdapte, tabLoge[i]->dispo, tabLoge[i]->idEtudOccup);
		}
	}
}

// Menu -> 1)
void affichLogeDispo(Logement *tabLoge[], int nbLoge){
	int i;
	for(i=0;i<nbLoge;i++){
		if(tabLoge[i]->idEtudOccup==NULL){ // mettre * si tableau de pointeurs
			printf("%s\t%s\t%s\t%d\t%d\n",tabLoge[i]->idLoge, tabLoge[i]->cite, tabLoge[i]->type, tabLoge[i]->handicapAdapte, tabLoge[i]->dispo);
		}
	}
}
