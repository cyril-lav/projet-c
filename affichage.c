#include "projet.h"
#include <string.h>
#include <stdlib.h>

/*
Fonction : menu
Finalité : afficher le menu général
*/
void menu(void){
  printf("\n#####################################################\n");
  printf("#  1-Affichage des Logements Disponibles            #\n");
  printf("#  2-Affichage des Logements Occupés                #\n");
  printf("#  3-Affichage des Demandes Logements en Attente    #\n");
  printf("#  4-Création d'une Demande de Logement             #\n");
  printf("#  5-Annulation d'une Demande de Logement           #\n");
  printf("#  6-Libération d'un Logement                       #\n");
  printf("#  7-Sauvegarde des fichiers                        #\n");
  printf("#  9-Quitter                                        #\n");
  printf("#####################################################\n\n");
}


/*
Fonction : affichLogeOccup
Finalité : afficher la liste des Logements Occupés avec leur Etudiant attaché

Paramètres (entrant/sortant): 
    tabLoge[] : tableau de pointeurs sur Logements

Paramètres (entrant): 
    nbLog : nombre de logements
Variables : 
    i : indice de boucle
*/
void affichLogeOccup(Logement* tabLoge[],int nbLog){
  int i;
  triSelectEchLoge(tabLoge,nbLog);
  printf("N°Logement\t\t\tCité\t\tType\t\ttHandicap\tN°Etudiant\n\n");
  for(i=0; i < nbLog; i++){
    if(tabLoge[i]->dispo == 0){
      printf("%s %30s\t\t%s\t\t%d\t\t%s\n",tabLoge[i]->idLoge, tabLoge[i]->cite, tabLoge[i]->type, tabLoge[i]->handicapAdapte, tabLoge[i]->idEtudOccup);
    }
  }
}
  
/*
Fonction : affichLogeOccup
Finalité : afficher la liste des Logements Disponibles

Paramètres (entrant/sortant): 
    tabLoge[] : tableau de pointeurs sur Logements

Paramètres (entrant): 
    nbLog : nombre de logements
    
Variables : 
    i : indice de boucle
*/
void affichLogeDispo(Logement* tabLoge[],int nbLog){
  int i;
  triSelectEchLoge(tabLoge,nbLog);
  printf("N°Logement\tType\t\tHandicap\tCité\n\n");
  for(i=0; i < nbLog; i++){
    if(tabLoge[i]->dispo == 1){
      printf("%s\t\t%s\t\t%d\t\t%s\n", tabLoge[i]->idLoge, tabLoge[i]->type, tabLoge[i]->handicapAdapte, tabLoge[i]->cite);
    }
  }
}

/*
Fonction : affichEtud
Finalité : afficher la liste des Etudiants

Paramètres (entrant/sortant): 
    tab : tableau d'Etudiants

Paramètres (entrant): 
    nbEtud : nombre d'Etudiants

Variables : 
    i : indice de boucle
*/
void affichEtud(Etudiant* tab,int nbEtud){
	int i;
  printf("N°Etudiant\t\tNom\t\t\tPrénom\t\tCivilité\tHandicap\tBoursier\tEchelon\n\n");
  	for(i=0;i<nbEtud;i++){
    	printf("%s\t%20s\t%20s\t\t%s\t\t%d\t\t%d",tab[i].idEtud,tab[i].nom,tab[i].prenom,tab[i].civ,tab[i].handicap,tab[i].boursier);
    	if(tab[i].boursier==1){
            printf("\t\t%d",tab[i].echelon); 
    	}
		printf("\n");
  	}
}

/*
Fonction : affichDemande
Finalité : afficher la liste des Demandes

Paramètres : 
    l : liste de Demande
*/
void affichDemande(ListeDemande l){
	if(l == NULL)return;
	printf("%s\t\t%s\t\t%d\t  %10s%30s\n",l->demande.idDemande, l->demande.idEtudDemande, l->demande.echelonEtud, l->demande.type, l->demande.citeDemande);
	affichDemande(l->suiv);
}


