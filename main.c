#define TAILLE 100
#include "projet.h"
#include <string.h>
#include <stdlib.h>

void appli(void){
    int choix=0; // Choix dans le menu
    int sauvegarde=1;
    int nbLoge, nbEtud, nbIdDemande, posEtudiant;
    char confirmerQuitter='X';
    FILE *fsDemande;
    Logement* tabLoge[80];
    Etudiant *tabEtud;
    ListeDemande listeDemandes;
    listeDemandes=listeVide();

    nbLoge=chargeLogement(tabLoge, 80);
    tabEtud=chargeEtudiant(&nbEtud);
    triDichoEtud(tabEtud,nbEtud);
    listeDemandes=chargeDemande(&nbIdDemande);

    menu();
    scanf("%d%*c",&choix);

    while(!(choix == 9)){
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
                tabEtud=nouveauEtud(tabEtud, &nbEtud, &posEtudiant);
                if(posEtudiant==nbEtud-1)
                    triDichoEtud(tabEtud,nbEtud);
                listeDemandes=nouvelleDemande(tabEtud,listeDemandes,nbEtud,&nbIdDemande, posEtudiant);
                sauvegarde=0;
                break;
            case 5:
                listeDemandes=annulationDemande(listeDemandes);
                sauvegarde=0;
                break;
            case 6:
                liberationLogement(tabLoge,nbLoge);
                sauvegarde=0;
                break;
            case 7:
                sauvEtud(tabEtud,nbEtud);
                sauvLoge(tabLoge,nbLoge);
                fsDemande=fopen("demandes.bin","wb");
                if(fsDemande==NULL){
                    printf("Problème sauvegarde, écriture fichier \"demandes.bin\" impossible\n");
                    break;
                }
                fwrite(&nbIdDemande,sizeof(int),1,fsDemande);
                sauvDemande(listeDemandes,fsDemande,&nbIdDemande);
                fclose(fsDemande);
                sauvegarde=1;
                break;
            case 8:
                affichEtud(tabEtud,nbEtud);
                break;
            case 9:
                if(sauvegarde=='0'){
                    printf("Vous n'avez pas sauvegardé, voulez-vous quand même quitter l'application ? (O/N)\n");
                    scanf("%c%*c",&confirmerQuitter);
                    if(confirmerQuitter=='O' || confirmerQuitter=='o'){
                        sauvegarde=1;
                    }
                }
                break;
            default:
                printf("Erreur: valeur non valide\n");
        }
        if(choix==9 && sauvegarde==1){
            return;
        }
        menu();
        scanf("%d%*c",&choix);
    }
    return;
}




int main(void){
	appli();
    return 0;
}


