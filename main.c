#define TAILLE 100
#include "projet.h"

void appli(void){
    int choix=0; // Choix dans le menu
    int saveDone=1;
    int nbLoge;
    char confirmQuit='X';
    Logement* tabLoge[80];
    FILE *feLoge;

    feLoge=fopen("logements.don","r");
    
    if(feLoge==NULL){
        printf("Erreur ouverture fichier \"logements.don\"\n");
    return;
    }
    nbLoge=chargeLogement(tabLoge, 80, feLoge);
    fclose(feLoge);
    menu();
    scanf("%d%*c",&choix);

    while(!(choix == 9 && saveDone == 1)){
        switch(choix){
            case 1:
                affichLogeDispo(tabLoge, nbLoge);
                break;
            case 2:
                break;
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
}


