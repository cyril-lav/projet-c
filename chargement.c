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
  int l;
  char chaine[50];

  	fscanf(fe,"%s%*c", e.idEtud);

    fgets(chaine,50,fe);
    l=strlen(chaine);
    if(chaine[l-1]=='\n'){
        chaine[l-1]='\0';
        l--;
    }
    e.nom=(char*)malloc(sizeof(char)*(l+1));
    if(e.nom==NULL)
        exit(1);
    strcpy(e.nom,chaine);
        
    fgets(chaine,50,fe);
    l=strlen(chaine);
    if(chaine[l-1]=='\n'){
        chaine[l-1]='\0';
        l--;
    }
    e.prenom=(char*)malloc(sizeof(char)*(l+1));
    if(e.prenom==NULL)
        exit(1);
    strcpy(e.prenom,chaine);
    fscanf(fe,"%s %d %d ", e.civ, &e.handicap, &e.boursier);
	fscanf(fe,"%d%*c",&e.echelon);
	
  return e;
}


Etudiant* chargeEtudiant(int* nbEtud){
	FILE *feEtud;
	Etudiant* tab;
	int i;

	feEtud=fopen("etudiants.don","r");
	if(feEtud==NULL){
		printf("Erreur lecture fichier \"etudiants.don\"\n");
		return NULL;
	}

    fscanf(feEtud, "%d", nbEtud);

    tab=(Etudiant*)malloc(*nbEtud*sizeof(Etudiant));
    if (tab == NULL){
        printf("Problème d'allocation de mémoire pour le tab Etudiant");
        exit(1);
    }
    for(i=0; i < *nbEtud; i++){
        tab[i]=lireEtud(feEtud);
    }
    
	fclose(feEtud);
	return tab;
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





ListeDemande ajouterDemandeEnTete(ListeDemande listeDemandes, Demande demande) {
  MaillonDemande* tmp;

  tmp = (MaillonDemande*) malloc(sizeof(MaillonDemande));
  if(tmp == NULL) {
      printf("Problème allocation mémoire\n");
      exit(1);
  }

  //copie id logement
  strcpy(tmp->demande.idDemande, demande.idDemande);

  //copie id etud
  strcpy(tmp->demande.idEtudDemande, demande.idEtudDemande);

  //copie echelon
  tmp->demande.echelonEtud = demande.echelonEtud;

  //copie cite demande
  strcpy(tmp->demande.citeDemande, demande.citeDemande);

  //copie type de logement demande
  strcpy(tmp->demande.type, demande.type);
  
  tmp->suivant = listeDemandes;
  listeDemandes=tmp;

  return listeDemandes;
}

ListeDemande ajouterDecroissant(ListeDemande listeDemandes, Demande demande){

	if(listeDemandes == NULL){
		listeDemandes=ajouterDemandeEnTete(listeDemandes, demande);
	}
	else{
		if (demande.echelonEtud >= listeDemandes->demande.echelonEtud){
			listeDemandes=ajouterDemandeEnTete(listeDemandes, demande);
		}
		else{
			listeDemandes->suivant=ajouterDecroissant(listeDemandes->suivant, demande);
		}
	}
	return listeDemandes;
}

ListeDemande listeVide(void){
  return NULL;
}


ListeDemande chargeDemande(int *nbDem){
	FILE* feDemande;
	ListeDemande listeDemandes;
	Demande demande;
	int i;
  
	feDemande=fopen("demandes.bin","rb");
	if(feDemande == NULL){
		printf("Erreur lecture fichier \"demandes.bin\"\n");
		return NULL;
	}

	listeDemandes = listeVide();
    fread(nbDem,sizeof(int),1,feDemande);
	fread(&demande,sizeof(Demande),1,feDemande);
	for(i=0; i<*nbDem;i++){
		listeDemandes=ajouterDecroissant(listeDemandes, demande);
		fread(&demande,sizeof(Demande),1,feDemande);
	}

	return listeDemandes;
    fclose(feDemande);
}
