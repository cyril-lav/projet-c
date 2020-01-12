#define TAILLE 100
#include "projet.h"
#include <string.h>
#include <stdlib.h>

void appli(void){
    int choix=0; // Choix dans le menu
    int saveDone=1;
    int nbLoge, nbEtud;
    char confirmQuit='X';
    Logement* tabLoge[80];
    Etudiant *tab;
    ListeDemande *listeDemandes;

    nbLoge=chargeLogement(tabLoge, 80);
    tab=chargeEtudiant(&nbEtud);
    listeDemandes=chargeDemande();

    menu();
    scanf("%d%*c",&choix);

    while(!(choix == 9 && saveDone == 1)){
        switch(choix){
            case 1:
	         affichLogeDispo(tabLoge,nbLoge);
                break;
            case 2:
                affichLogeOccup(tabLoge,nbLoge);
                break;
            case 3:
                affichDemande(listeDemandes);
                break;
            case 4:
                affichEtud(tab,nbEtud);
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
                if(saveDone=='0'){
                    printf("Vous n'avez pas sauvegardé, voulez-vous quand même quitter l'application ? (O/N)\n");
                    scanf("%c%*c",&confirmQuit);
                    if(confirmQuit=='O' || confirmQuit=='o'){
                        saveDone=1;
                    }
                }
                break;
            default:
                printf("Erreur: valeur non valide\n");
        }
        if(choix==9 && saveDone==1){
            return;
        }
        menu();
        scanf("%d%*c",&choix);
    }
    return;
}




int main(void){
	appli();
    //conversion();
}


