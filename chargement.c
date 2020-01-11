#include "projet.h"
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
Logement lireLogement(FILE *fe){
    Logement l;
    int tailleCite;
    char nomCite[50];

    //id logement
    fscanf(fe,"%s%*c",l.idLoge);

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
    fscanf(fe,"%s%*c",l.type);

    //logement pour handicap
    fscanf(fe,"%d%*c", &l.handicapAdapte);

    //logement diponible
    fscanf(fe,"%d%*c", &l.dispo);

    //Id de l'etusiant qui occupe
    if(l.dispo==0){
        fscanf(fe,"%s%*c",l.idEtudOccup);
    }
    
    return l;
}



ListeDemande ajouterDemandeEnTete(ListeDemande listeDemande, Demande demande) {
  MaillonDemande* tmp;

  int tailleCite;

  tmp = (MaillonDemande*) malloc(sizeof(MaillonDemande));
  if(tmp == NULL) {
      printf("Problème mémoire");
      exit(1);
  }

  //copie id logement
  strcpy(tmp->demande.idDemande, demande.idDemande);

  //copie id etud
  strcpy(tmp->demande.idEtudDemande, demande.idEtudDemande);

  //copie echelon
  tmp->demande.echelonEtud = demande.echelonEtud;

  //copie cite demande
  tailleCite = strlen(demande.citeDemande);
  tmp->demande.citeDemande = (char*)malloc(sizeof(char)* tailleCite + 1);
  strcpy(tmp->demande.citeDemande, demande.citeDemande);

  //copie type de logement demande
  strcpy(tmp->demande.type, demande.type);
  
  tmp->suivant = listeDemande;
  listeDemande=tmp;

  return listeDemande;
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
Etudiant* chargeEtudiant(int* nbEtud){
	FILE *feEtud;
	Etudiant* tab;
	int i;
	feEtud=fopen("etudiants.bin","rb");
	if(feEtud==NULL){
		printf("Erreur lecture fichier \"etudiants.don\"\n");
		return NULL;
	}
	fread(nbEtud,sizeof(int),1,feEtud);
	tab=(Etudiant*)malloc(sizeof(Etudiant)* *nbEtud);
	if(tab==NULL){
		printf("Problème allocation mémoire\n");
		return NULL;
  	}
	fread(tab,sizeof(Etudiant),*nbEtud,feEtud);
	fclose(feEtud);
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
int chargeLogement(Logement* tab[], int tmax){
	Logement l;
	FILE *feLoge;
	int nbLo=0, i;

	feLoge=fopen("logements.don","r");
	if(feLoge==NULL){
		printf("Erreur lecture fichier \"logements.don\"\n");
		return -1;
	}
	
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
        nbLo++;
		l=lireLogement(feLoge);
	}
	fclose(feLoge);
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
ListeDemande listeVide(void){
  return NULL;
}

/*
ListeDemande chargeDemande(FILE* feDem, int* nbLoge){
	ListeDemande demandes;
	MaillonDemande* tmp;
	int nbDem, i;
  
	demandes = listeVide();

	fread(nbDem,sizeof(int),1,feDem);
	for(i=0;i < nbDem;i++){
		lireDemande(feDem,tmp);
	}
	return demandes;
}
*/