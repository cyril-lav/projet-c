#include "projet.h"
#include <string.h>
#include <stdlib.h>


/* 
   Fonction: lireEtud
   Finalité: Lis un etudiant dans le fichier

	Paramètre entrant/sortant :
		fe		- flot entrant

    Variables : 
        e		-un étudiant
		l		-longueur de la chaine de caractère
		chaine	-chaine de caractère lu

	Valeur retournée : 
   		étudiant lu
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
    fscanf(fe,"%s %d %d %d%*c", e.civ, &e.handicap, &e.boursier,&e.echelon);

  return e;
}


/* 
   Fonction: chargeEtudiant
   Finalité: Chargement des étudiants du fichier dans un tableau

	Paramètre entrant/sortant :
		nbEtud		- nombre d'étudiants

    Variables : 
        feEtud		-flot d'entrée
		tab			-tableau d'étudiants
		i			-index

	Valeur retournée : 
   		Le tableau chargé
*/
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
   Finalité: Lis un logement dans le fichier

	Paramètre entrant/sortant :
		feLoge		- flot entrant

    Variables : 
        l				-un logement
		tailleCite		-longueur de la chaine de caractère
		nomCite			-chaine de caractère lu

	Valeur retournée : 
   		Logement lu
*/
Logement lireLogement(FILE *feLoge){
    Logement l;
    int tailleCite;
    char nomCite[50];

    //id logement
    fscanf(feLoge,"%s%*c",l.idLoge);

    //nom de la cite
    fgets(nomCite, 50, feLoge);
    tailleCite=strlen(nomCite);
    if (nomCite[tailleCite-1] == '\n'){
        nomCite[tailleCite-1] = '\0';
        tailleCite--;
    }
    l.cite=(char*)malloc(sizeof(char)*(tailleCite+1));
    if (l.cite == NULL)exit(1);
    strcpy(l.cite, nomCite);

    //Type de logement
    fscanf(feLoge,"%s%*c",l.type);

    //logement pour handicap
    fscanf(feLoge,"%d%*c", &l.handicapAdapte);

    //logement diponible
    fscanf(feLoge,"%d%*c", &l.dispo);

    //Id de l'etusiant qui occupe
    if(l.dispo==0){
        fscanf(feLoge,"%s%*c",l.idEtudOccup);
    }
    
    return l;
}


/* 
   Fonction: chargeLogement
   Finalité: Chargement des logements du fichier dans un tableau de pointeurs

	Paramètre entrant/sortant :
		tab		- tableau de pointeurs de logements


	Paramètre entrant :
		tmax	-taille maximal du tableau

    Variables : 
        feLoge		-flot d'entrée
		l			-un logement
		i			-index
		nbLo		-nombre de logements

	Valeur retournée : 
   		nombre de logements
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
   Fonction: ajouterDemandeEnTete
   Finalité: Ajoute un maillon en tête dans une liste chainée

	Paramètres entrants :
		listeDemandes		-liste chainée de demande
		demande				-une demande

    Variables : 
        tmp		-pointeur temporaire sur une demande

	Valeur retournée : 
   		liste de demande
*/
ListeDemande ajouterDemandeEnTete(ListeDemande listeDemandes, Demande demande) {
  	MaillonDemande* tmp;

  	tmp = (MaillonDemande*) malloc(sizeof(MaillonDemande));
  	if(tmp == NULL) {
        printf("Problème allocation mémoire\n");
    	exit(1);
 	 }

	tmp->demande=demande;
	tmp->suiv = listeDemandes;
  	listeDemandes=tmp;
  	return listeDemandes;
}

/* 
   Fonction: ajouterDecroissant
   Finalité: ajoute un maillon de façon décroissant dans la liste de damande

	Paramètres entrants :
		listeDemandes		-liste chainée de demande
		demande				-une demande

	Valeur retournée : 
   		liste de demande
*/
ListeDemande ajouterDecroissant(ListeDemande listeDemandes, Demande demande){

    if(listeDemandes == NULL){
        listeDemandes=ajouterDemandeEnTete(listeDemandes, demande);
    }
    else{
        if (demande.echelonEtud <= listeDemandes->demande.echelonEtud){
            listeDemandes->suiv=ajouterDecroissant(listeDemandes->suiv, demande);
        }
        else{
            listeDemandes=ajouterDemandeEnTete(listeDemandes, demande);
        }
    }
    return listeDemandes;
}


/* 
   Fonction: chargeLogement
   Finalité: créé une liste vide

	Valeur retournée : 
   		NULL 
*/
ListeDemande listeVide(void){
  return NULL;
}

/* 
   Fonction: chargeDemande
   Finalité: Chargement des logements dans une liste chainée

	Paramètre entrant/sortant :
		nbIdDemande		- nombre d'id d'étudiant présent dans le fichier

    Variables : 
        feDemande			-flot d'entrée
		listeDemandes		-liste chaînée de demande
		i					-index
		demande				-une demande

	Valeur retournée : 
   		liste de demandes
*/
ListeDemande chargeDemande(int* nbIdDemande){
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
    fread(nbIdDemande, sizeof(int),1,feDemande);
	fread(&demande,sizeof(Demande),1,feDemande);
	while(!feof(feDemande)){
		listeDemandes=ajouterDecroissant(listeDemandes, demande);
		fread(&demande,sizeof(Demande),1,feDemande);
	}
    fclose(feDemande);
	return listeDemandes;
}


/* 
   Fonction: sauvEtud
   Finalité: Sauvgarde les étudiants dans un fichier

	Paramètre entrant/sortant :
		tEtud		-tableau d'étudiants

	Paramètre entrant :
		nbEtud		-nombre d'étudiants

    Variables : 
        fsEtud				-flot de sortie
*/
void sauvEtud(Etudiant tEtud[], int nbEtud){
    FILE* fsEtud;
    fsEtud=fopen("etudiants.don","w");
    if(fsEtud==NULL){
    	printf("Erreur sauvegarde étudiants (écriture de \"logements.don\" impossible\n");
    	return;
    }
    fprintf(fsEtud,"%d",nbEtud);
    for(int i=0;i<nbEtud;i++){
        fprintf(fsEtud,"\n%s\n%s\n%s\n%s %d %d %d\n",tEtud[i].idEtud,tEtud[i].nom,
        tEtud[i].prenom,tEtud[i].civ,tEtud[i].handicap,tEtud[i].boursier,tEtud[i].echelon);
    }
    fclose(fsEtud);
}


/* 
   Fonction: sauvLoge
   Finalité: Sauvgarde les logements dans un fichier

	Paramètre entrant/sortant :
		tabLoge		-tableau de pointeur de logement

	Paramètre entrant :
		nbLoge		-nombre de logements

    Variables : 
        fsLoge				-flot de sortie
		i					-index
*/
void sauvLoge(Logement* tabLoge[], int nbLoge){
	FILE* fsLoge;
  	int i;
  	fsLoge=fopen("logements.don","w");
  	if(fsLoge==NULL){
		printf("Erreur sauvegarde logement (écriture de \"logements.don\" impossible\n");
		return;
  	}
  	for(i=0 ; i<nbLoge ; i++){
        fprintf(fsLoge,"%s\n%s\n%s\n%d\n%d\n", tabLoge[i]->idLoge, tabLoge[i]->cite, tabLoge[i]->type, tabLoge[i]->handicapAdapte, tabLoge[i]->dispo);
        if(tabLoge[i]->dispo == 0){
      	    fprintf(fsLoge,"%s\n",tabLoge[i]->idEtudOccup);
        }
    }
	fclose(fsLoge);
}


/* 
   Fonction: sauvDemande
   Finalité: Sauvgarde les logements dans un fichier

	Paramètre entrant/sortant :
		fsDem		-flots sortant

	Paramètre entrant :
		l		-liste de demande
*/
void sauvDemande(ListeDemande l,FILE* fsDem){
    if(l==NULL)return;
    fwrite(&(l->demande),sizeof(Demande),1,fsDem);
    sauvDemande(l->suiv,fsDem);
}


/* 
   Fonction: liberationTabLog
   Finalité: libère la mémoire du tableau de logement

	Paramètre entrant/sortant :
		tabLog		-tableau de logement

	Paramètre entrant :
		nbLog		-nombre de logement
*/
void liberationTabLog(Logement** tabLog, int nbLog){
    int i;

    for(i=0; i < nbLog; i++){
	    free(tabLog[i]);
	}
}


/* 
   Fonction: liberationListeDem
   Finalité: libère la liste de demande

	Paramètre entrant :
		l		-liste de demande
*/
ListeDemande liberationListeDem(ListeDemande l){
    if(l == NULL)return l;
    l->suiv=liberationListeDem(l->suiv);
    l=supprimerEnTete(l);
    return l;
}