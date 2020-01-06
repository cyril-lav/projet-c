#include "projet.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
Logement lireLogement(FILE *feLoge){
    Logement l;
    int taille;
    char chaine[50];

    fscanf(feLoge,"%s",l.idLoge);

    fgets(chaine, 50, feLoge);
    taille=strlen(chaine);
    if (chaine[taille-1] == '\n'){
        chaine[taille-1] = '\0';
        taille--;
    }
    l.cite=(char*)malloc(sizeof(char)*(taille+1));
    if (l.cite == NULL)exit(1);
    strcpy(l.cite, chaine);


    fscanf(feLoge," %s %d %d",l.type, &l.handicapAdapte, &l.dispo);
    if(l.dispo==0)
        fscanf(feLoge," %s",l.idEtudOccup);
    return l;
}



ListeDemande ajouterDemandeListe(ListeDemande listeDemande, Demande demande) {
  MaillonDemande* tmp;

  int taille;

  tmp = (MaillonDemande*) malloc(sizeof(MaillonDemande));
  if(tmp == NULL) {
      printf("Problème mémoire");
      exit(1);
  }

  strcpy(tmp->demande.idDemande, demande.idDemande);

  taille = strlen(demande.citeDemande);
  tmp->demande.citeDemande = (char*)malloc(sizeof(char)* taille + 1);

  strcpy(tmp->demande.citeDemande, demande.citeDemande);
  strcpy(tmp->demande.typeDemande, demande.typeDemande);
  strcpy(tmp->demande.idEtudDemande, demande.idEtudDemande);
  tmp->demande.echelonEtud = demande.echelonEtud;

  tmp->suivant = listeDemande;

    return tmp;
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
int chargeLogement(Logement* tab[], int tmax, FILE* feLoge){
	Logement l;
	int nbLo=0, i;

	l=lireLogement(feLoge);
	while(feof(feLoge) == 0){
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
		l=lireLogement(feLoge);
		nbLo++;
	}
	return nbLo;
}





/* 
   Fonction: chargeDemande
   finalité: Charge les logements dans une liste chainée
   
   paramètre entrant/sortant :
         fe		    - flot d'entrée
		 nbLog		- nombre de logement
		 
   valeur retournée : 
         la liste de logement

*/
ListeDemande chargeDemande(FILE* fe, int* nbLog){
	ListeDemande demandes = NULL;
    Demande* tab;
    int i;

	fread(nbLog, sizeof(int), 1, fe);

	tab=(Demande*)malloc(sizeof(Demande)* *nbLog);
	if(tab==NULL){  
    	printf("Problème d'allocation de la mémoire\n");  
    	exit(1);                                           
  	}
	fread(tab, sizeof(MaillonDemande), *nbLog, fe);

    for(i=0; i < *nbLog; i++){
        demandes=ajouterDemandeListe(demandes, tab[i]);
    }
	free(tab);
	return demandes;
}
