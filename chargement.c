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
  int tailleNom, taillePrenom;
  char nom[50], prenom[50];

  //id etudiant
  fscanf(fe,"%s",e.idEtud);

  //nom
  fgets(nom, 50, fe);
  tailleNom=strlen(nom);
  if (nom[tailleNom-1] == '\n'){
    nom[tailleNom-1] = '\0';
	tailleNom--;
  }
  e.nom=(char*)malloc(sizeof(char)*(tailleNom+1));
  if (e.nom == NULL)exit(1);
  strcpy(e.nom, nom);

  //prenom
  fgets(prenom, 50, fe);
  taillePrenom=strlen(prenom);
  if (prenom[taillePrenom-1] == '\n'){
    prenom[taillePrenom-1] = '\0';
	taillePrenom--;
  }
  e.prenom=(char*)malloc(sizeof(char)*(taillePrenom+1));
  if (e.prenom == NULL)exit(1);
  strcpy(e.prenom, prenom);

  //civilité
  fscanf(fe,"%s",e.civ);

  //handicap
  fscanf(fe,"%d%*c", &e.handicap);

  //boursier et si oui echelon
  fscanf(fe,"%d%*c",&e.boursier);
  if (e.boursier){
    fscanf(fe,"%d%*c",&e.echelon);
  }

  return e;
}

/* 
   Fonction: lireLogement
   finalité: Lit un logement dans le fichier
   paramètre entrant/sortant :
		 fe			- flot entrant
   valeur retournée : l'article lu

*/
<<<<<<< HEAD
Logement lireLogement(FILE *fe){
=======

/*Logement lireLogement(FILE *feLoge){
>>>>>>> 136d30802f01b4d0cc3b0e9fba4c1b00d166969e
    Logement l;
    int tailleCite;
    char nomCite[50];

    //id logement
    fscanf(fe,"%s",l.idLoge);

    //nom de la cite
    fgets(nomCite, 50, fe);
    tailleCite=strlen(nomCite);
    if (nomCite[tailleCite-1] == '\n'){
        nomCite[tailleCite-1] = '\0';
        tailleCite--;
    }
    l.cite=(char*)malloc(sizeof(char)*(tailleCite+1));
    if (l.cite == NULL)exit(1);
    strcpy(l.cite, nomCite);

    //Type de logement
    fscanf(fe," %s",l.type);

    //logement pour handicap
    fscanf(fe,"%d%*c", &l.handicapAdapte);

    //logement diponible
    fscanf(fe,"%d%*c", &l.dispo);

    //Id de l'etusiant qui occupe
    if(l.dispo==0){
        fscanf(fe," %s",l.idEtudOccup);
    }
    
    return l;
}
*/
Logement lireLogement(FILE *feLoge){
  char cite[50];
  int taille;
  Logement loge;
  fscanf(feLoge,"%s",loge.idLoge);
  fgets(cite,50,feLoge);
  taille=strlen(cite);
  if (cite[taille-1] == '\n'){
     cite[taille-1] = '\0';
     taille--;
  }
  loge.cite=(char*)malloc(sizeof(char)*(taille+1));
  if(loge.cite==NULL) exit(1);
  strcpy(loge.cite,cite);
  fscanf(feLoge," %s %d %d ",loge.type,&loge.handicapAdapte/*,&loge.dispo*/);
  if(loge.dispo==1){
    fscanf(feLoge,"%s",loge.idEtudOccup);
  }
  else{
    strcpy(loge.idEtudOccup,loge.idLoge);
  }
  return loge;
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

/*
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
*/
Logement* chargeLogement(FILE* feLoge, int* nbLoge){
  Logement* loge;
  int i;
  fscanf(feLoge,"%d ",nbLoge);
  loge=(Logement*)malloc(sizeof(Logement)* *nbLoge);
  if(loge==NULL){
    printf("pb alloc\n");
    exit(1);
  }
  for(i=0;i<*nbLoge;i++){
    loge[i]=lireLogement(feLoge);
  }
  return loge;
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
