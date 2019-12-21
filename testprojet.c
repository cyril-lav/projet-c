#include "projet.h"

void global(void){
char choix='0';
menu();
scanf("%c%*c",&choix);
while(choix!='9'){
	switch(choix){
		case 1:
			affichLogeDispo(tabLoge, nbLoge);
		case 2:
			affichLogeOccup(tabLoge, nbLoge);
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		default:
			printf("Erreur: valeur non valide\n");
	}
	menu();
	scanf("%c%*c",&choix);
}
return;
}
