#include "projet.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// J'adore Cyril

/* 
   Fonction: lireEtud
   finalité: Lit un etudiant dans le fichier
   paramètre entrant/sortant :
		 fe			- flot entrant
   valeur retournée : l'article lu

*/
Etudiant lireEtud(FILE *fe){
  Etudiant e;
  int taille;
  char chaine[50];

  fgets(e.idEtud, 7, fe);
  taille=strlen(e.idEtud);
  if (e.idEtud[taille-1] == '\n'){
    e.idEtud[taille-1] = '\0';
  }


  fgets(chaine, 50, fe);
  taille=strlen(chaine);
  if (chaine[taille-1] == '\n'){
    chaine[taille-1] = '\0';
	taille--;
  }
  e.nom=(char*)malloc(sizeof(char)*(taille+1));
  if (e.nom == NULL)exit(1);
  strcpy(e.nom, chaine);


  fgets(chaine, 50, fe);
  taille=strlen(chaine);
  if (chaine[taille-1] == '\n'){
    chaine[taille-1] = '\0';
	taille--;
  }
  e.prenom=(char*)malloc(sizeof(char)*(taille+1));
  if (e.prenom == NULL)exit(1);
  strcpy(e.prenom, chaine);


  fscanf(fe,"%s %d %d %d",e.civ, &e.handicap, &e.boursier, &e.echelon);

  return e;
}

/* 
   Fonction: lireLogement
   finalité: Lit un logement dans le fichier
   paramètre entrant/sortant :
		 fe			- flot entrant
   valeur retournée : l'article lu

*/
Logement lireLogement(FILE *fe){
  Logement l;
  int taille;
  char chaine[50];

  fgets(l.idLoge, 7, fe);
  taille=strlen(l.idLoge);
  if (l.idLoge[taille-1] == '\n'){
    l.idLoge[taille-1] = '\0';
  }


  fgets(chaine, 50, fe);
  taille=strlen(chaine);
  if (chaine[taille-1] == '\n'){
    chaine[taille-1] = '\0';
	taille--;
  }
  l.cite=(char*)malloc(sizeof(char)*(taille+1));
  if (l.cite == NULL)exit(1);
  strcpy(l.cite, chaine);


  fscanf(fe,"%s %d %d %s",l.type, &l.handicapAdapte, &l.dispo, l.idEtudOccup);

  return l;
}

/* 
   Fonction: chargeEtudiant
   finalité: Charge les etudiants dans un tableau
   
   paramètre entrant/sortant :
         fe		    - flot d'entrée
	     nbEtud		- nombre d'étudiants
		 
   valeur retournée : 
         le tableau d'étudiants

*/
Etudiant* chargeEtudiant(FILE* fe, int* nbEtud){
	Etudiant* tab;
	int i;

	fscanf(fe, "%d ", nbEtud);
	tab=(Etudiant*)malloc(sizeof(Etudiant)* *nbEtud);
	if(tab == NULL){
		printf("problème allocation mémoire etudiant");
		exit(1);
	}
	for(i=0; i < *nbEtud; i++){
		tab[i]= lireEtud(fe);
	}
	return tab;
}

/* 
   Fonction: chargeEtudiant
   finalité: Charge les logements dans un tableau de pointeurs
   
   paramètre entrant/sortant :
         fe		    - flot d'entrée
		 tab		- tableau de logements

   paramètre entrant : 
	     tmax		- taille max du tableau
		 
   valeur retournée : 
         nombre de logement

*/
int chargeLogement(Logement* tab[], int tmax, FILE* fe){
	Logement l;
	int nbLo=0, i;

	l=lireLogement(fe);
	while(feof(fe) == 0){
		if(nbLo == tmax){
			printf("tableau trop petit");
			for(i=0; i < nbLo; i++){
				free(tab[i]);
			}
			return -1;
		}
		tab[nbLo]=(Logement*)malloc(sizeof(Logement));
		if(tab[nbLo] == NULL){
			printf("problème allocation mémoire logement");
			for(i=0; i < nbLo; i++){
				free(tab[i]);
			}
			return -1;
		}
		*tab[nbLo]=l;
		l=lireLogement(fe);
		nbLo++;
	}
	return nbLo;
}

/* 
   Fonction: chargeDemande
   finalité: Charge les logements dans un tableau
   
   paramètre entrant/sortant :
         fe		    - flot d'entrée
		 nbLog		- nombre de logement
		 
   valeur retournée : 
         le tableau de logement

*/
MaillonDemande* chargeDemande(FILE* fe, int* nbLog){
	MaillonDemande* tab;

	fread(nbLog, sizeof(int), 1, fe);

	tab=(MaillonDemande*)malloc(sizeof(MaillonDemande)* *nbLog);
	if(tab==NULL){  
    	printf("Problème d'allocation de la mémoire\n");  
    	exit(1);                                           
  	}
	fread(tab, sizeof(MaillonDemande), *nbLog, fe);

	return tab;
}

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
void affichLogeOccup(Logement tabLoge[], int nbLoge){
	int i;
	for(i=0;i<nbLoge;i++){
		if(tabLoge[i].idEtudOccup!=NULL){ // mettre * si tableau de pointeurs
			printf("%s\t%s\t%s\t%d\t%d\t%s\n",tabLoge[i].idLoge, tabLoge[i].cite, tabLoge[i].type, tabLoge[i].handicapAdapte, tabLoge[i].dispo, tabLoge[i].idEtudOccup);
		}
	}
}

// Menu -> 1)
void affichLogeDispo(Logement tabLoge[], int nbLoge){
	int i;
	for(i=0;i<nbLoge;i++){
		if(tabLoge[i].idEtudOccup==NULL){ // mettre * si tableau de pointeurs
			printf("%s\t%s\t%s\t%d\t%d\n",tabLoge[i].idLoge, tabLoge[i].cite, tabLoge[i].type, tabLoge[i].handicapAdapte, tabLoge[i].dispo, tabLoge[i].idEtudOccup);
		}
	}
}
