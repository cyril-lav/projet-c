#define TAILLE 100
#include "projet.h"
#include <string.h>
#include <stdlib.h>


/*
Fonction : appli
Finalité : fonction générale

Variables :
    choix : différents choix dans le menu
    sauvegarde : indice de sauvegarde (0 si sauvegarde à faire)
    nbLoge : nombre de Logements
    nbEtud : nombre d'Etudiants
    nbIdDemande : nombre d'Id d'Etudiants
    posEtudiant : position d'un Etudiant
    confirmerQuitter : confirmation quand on quitte sans sauvegarder
    fsDemande : flot pour sauvegarder les Demandes
    tabLoge : tableau de Logements
    tabEtud : tableau d'Etudiants
    listeDemandes : liste de Demandes
*/
void appli(void){
    int choix=0; // Choix dans le menu
    int sauvegarde=1;
    int nbLoge, nbEtud, nbIdDemande=0, posEtudiant;
    char confirmerQuitter='X';
    FILE *fsDemande;
    Logement* tabLoge[80];
    Etudiant *tabEtud;
    ListeDemande listeDemandes;
    listeDemandes=listeVide();

    nbLoge=chargeLogement(tabLoge, 80);
    tabEtud=chargeEtudiant(&nbEtud);
    triRapide(tabEtud,0,nbEtud-1);
    listeDemandes=chargeDemande(&nbIdDemande);

    menu();
    scanf("%d%*c",&choix);

    while(1){
        switch(choix){
            case 1:
	            affichLogeDispo(tabLoge,nbLoge);
                break;
            case 2:
                affichLogeOccup(tabLoge,nbLoge);
                break;
            case 3:
                printf("N°Demande\tN°Etudiant\tEchelon\t  Type\t\t\tCité\n\n");
                affichDemande(listeDemandes);
                break;
            case 4:
                tabEtud=nouveauEtud(tabEtud, &nbEtud, &posEtudiant);
                listeDemandes=nouvelleDemande(tabEtud,listeDemandes,nbEtud,&nbIdDemande, posEtudiant);
                if(posEtudiant==nbEtud-1)
                    triRapide(tabEtud,0,nbEtud-1);
                sauvegarde=0;
                break;
            case 5:
                listeDemandes=annulationDemande(listeDemandes);
                sauvegarde=0;
                break;
            case 6:
                liberationLogement(tabLoge,nbLoge);
                listeDemandes=traitementDemandeAttente(listeDemandes, tabLoge, tabEtud, nbLoge, nbEtud);
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
                sauvDemande(listeDemandes,fsDemande);
                fclose(fsDemande);
                sauvegarde=1;
                printf("Sauvegarde effectuée\n");
                break;
            case 8:
                affichEtud(tabEtud,nbEtud);
                break;
            case 9:
                if(sauvegarde==0){
                    printf("Vous n'avez pas sauvegardé, voulez-vous quand même quitter l'application ? (O/N)\n");
                    scanf("%c%*c",&confirmerQuitter);
                    if(confirmerQuitter!='O' && confirmerQuitter!='o'){
                        break;
                    }
                }
                free(tabEtud);
                liberationTabLog(tabLoge, nbLoge);
                liberationListeDem(listeDemandes);
                return;
                default:
                printf("Erreur: valeur non valide\n");
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
