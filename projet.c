#include "projet.h"

// J'adore Cyril

// 3)
void affichLogeOccup(Logement tabLoge[], int nbLoge){
	int i;
	for(i=0;i<nbLoge;i++){
		if(tabLoge[0].idEtudOccup!=NULL){ // mettre * si tableau de pointeurs
			printf("%s\t%s\t%s\t%d\t%d\t%s\n",tabLoge[i].idLoge, tabLoge[i].cite, tabLoge[i].type, tabLoge[i].handicapAdapte, tabLoge[i].dispo, tabLoge[i].idEtudOccup);
}


