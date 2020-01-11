#include "projet.h"
#include <string.h>
#include <stdlib.h>

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

Demande lireDemande(FILE *fe){
    Demande d;
    int tailleCite;
    char nomCite[50];

    fscanf(fe,"%s%*c",d.idDemande);

    fscanf(fe,"%s%*c",d.idEtudDemande);

    fscanf(fe,"%d%*c", &d.echelonEtud);

    fgets(nomCite, 50, fe);
    tailleCite=strlen(nomCite);
    if (nomCite[tailleCite-1] == '\n'){
        nomCite[tailleCite-1] = '\0';
        tailleCite--;
    }
    d.citeDemande=(char*)malloc(sizeof(char)*(tailleCite+1));
    if (d.citeDemande == NULL)exit(1);
    strcpy(d.citeDemande, nomCite);

    fscanf(fe,"%s%*c", d.type);
  
    return d;
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

ListeDemande ajouterDecroissant(ListeDemande listeDemande, Demande demande){

	if(listeDemande == NULL){
		listeDemande=ajouterDemandeEnTete(listeDemande, demande);
	}
	else{
		if (demande.echelonEtud >= listeDemande->demande.echelonEtud){
			listeDemande=ajouterDemandeEnTete(listeDemande, demande);
		}
		else{
			listeDemande->suivant=ajouterDecroissant(listeDemande->suivant, demande);
		}
	}
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






ListeDemande listeVide(void){
  return NULL;
}



ListeDemande chargeDemande(int* nbDemande){
	FILE* feDemande;
	ListeDemande demandes;
	MaillonDemande* tmp;
	int nbDem, i;
  
	feDemande=fopen("demandes.don","r");
	if(feDemande == NULL){
		printf("Erreur lecture fichier \"demandes.don\"\n");
		return NULL;
	}

	demandes = listeVide();
	tmp->demande=lireDemande(feDemande);
	while(feof(feDemande) == 0){
		demandes=ajouterDecroissant(demandes, tmp->demande);
		tmp->demande=lireDemande(feDemande);
		*nbDemande++;
	}

	return demandes;
}
