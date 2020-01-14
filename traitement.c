#include "projet.h"
#include <string.h>
#include <stdlib.h>


/*
Fonction: triBulleDemande
Finalité: trier (Bulle) les Demandes par ordre décroissant des Echelons Boursiers
Paramètres: tabDemande : tableau des Demandes
			nbDemande : nombre de Demandes
Variables: i : indice de boucle
			cpt : compteur (si == 0 alors aucun changement)
*/
void triBulleDemande(Demande* tabDemande[],int nbDemande){
  int i, cpt=0;
  Demande* d;
  if(nbDemande==0 || nbDemande==1) return;
  for(i=0;i<nbDemande-1;i++){
    if(tabDemande[i]->echelonEtud < tabDemande[i+1]->echelonEtud){
      d=tabDemande[i+1];
      tabDemande[i+1]=tabDemande[i];
      tabDemande[i]=d;
      cpt++;
    }
  }
  if(cpt!=0){
    triBulleDemande(tabDemande,nbDemande-1);
  }
}


int posMin(Logement* tabLoge[], int nbLoge){
  char* min=tabLoge[0]->cite;
  int pos=0, i;
  for(i=1 ; i<nbLoge ; i++){
    if(strcmp(tabLoge[i]->cite,min)>0){
      min=tabLoge[i]->cite;
      pos=i;
    }
  }
  return pos;
}

void triSelectEchLoge(Logement* tabLoge[], int nb){
  int pos;
  Logement* loge;
  if(nb==0 || nb==1){
    return;
  }
  pos=posMin(tabLoge,nb);
  if(pos!=0){
    loge=tabLoge[0];
    tabLoge[0]=tabLoge[pos];
    tabLoge[pos]=loge;
    triSelectEchLoge(tabLoge+1,nb-1);
  }
}


void copier(Etudiant *tabEtud,int deb, int fin, Etudiant tab[]){
    int i=0;
    while(deb<fin){
        tab[i]=tabEtud[deb];
        deb++;
        i++;
    }
}


void fusion(Etudiant tab1[],int nbtab1, Etudiant tab2[], int nbtab2,Etudiant tabEtud[]){
    int cpt1, cpt2, cptEtud;
    while(cpt1<nbtab1 && cpt2<nbtab2){
        if(strcmp(tab1[cpt1].idEtud,tab2[cpt2].idEtud)<0){
            tabEtud[cptEtud]=tab1[cpt1];
            cpt1++;
            cptEtud++;
        }
        else{
            tabEtud[cptEtud]=tab2[cpt2];
            cpt2++;
            cptEtud++;
        }
    }
}

void triDichoEtud(Etudiant *tabEtud,int nbEtud){
    Etudiant *tab1, *tab2;
    if(nbEtud==1)
        return;
    tab1=(Etudiant*)malloc((nbEtud/2)*sizeof(Etudiant));
    if(tab1==NULL){
        printf("Problème allocation mémoire (triDichoEtud)\n");
        return;
    }
    tab2=(Etudiant*)malloc((nbEtud-nbEtud/2)*sizeof(Etudiant));
    if(tab2==NULL){
        printf("Problème allocation mémoire (triDichoEtud)\n");
        return;
    }
    copier(tabEtud,0,nbEtud/2,tab1);
    copier(tabEtud,nbEtud/2,nbEtud,tab2);
    triDichoEtud(tab1,nbEtud/2);
    triDichoEtud(tab2,nbEtud-nbEtud/2);
    fusion(tab1,nbEtud/2,tab2,nbEtud-nbEtud/2,tabEtud);
    free(tab1);
    free(tab2);
}

int rechercheDichoEtud(Etudiant* tab, char etud[6], int nbEtud, int* trouve){
	int deb=0, m, fin=nbEtud-1, cmp;
	while(deb <= fin){
		m=(deb+fin)/2;
		cmp=strcmp(etud, tab[m].idEtud);
		if(cmp == 0)return m;
		if (cmp < 0)fin=m-1;
		else deb=m+1;
	}
	return -1;
}

Etudiant saisieEtudControle(void){
	int l;
	char etudSaisie[6], chaine[50];
	Etudiant e;


	printf("Veuillez saisir le nom de l'étudiant: ");
	fgets(chaine,50,stdin);
	l=strlen(chaine);
	if(chaine[l-1]=='\n'){
    	chaine[l-1]='\0';
    	l--;
	}
	e.nom=(char*)malloc(sizeof(char)*(l+1));
	if(e.nom==NULL)
    	exit(1);
	strcpy(e.nom,chaine);

	printf("Veuillez saisir le prénom de l'étudiant: ");
    fgets(chaine,50,stdin);
	   l=strlen(chaine);
    if(chaine[l-1]=='\n'){
        chaine[l-1]='\0';
       	l--;
	}
	e.prenom=(char*)malloc(sizeof(char)*(l+1));
	if(e.prenom==NULL)
    	exit(1);
	strcpy(e.prenom,chaine);
		
	printf("Saisir la civilité de l'étudiant (Mr/Mme): ");
	scanf("%s%*c", e.civ);
	while (strcmp(e.civ,"Mr")!=0 && strcmp(e.civ,"Mme")!=0){
		printf("Erreur de saisie veuillez retaper (Mr/Mme) :");
		scanf("%s%*c", e.civ);
	}

	printf("Saisir si l'étudiant possède un handicape (0/1) :");
	scanf("%d%*c", &e.handicap);
	while (e.handicap > 1 || e.handicap < 0){
		printf("Erreur de saisie veuillez retaper (0/1) :");
		scanf("%d%*c", &e.handicap);
	}

	printf("Saisir si l'étudiant est boursier (0/1) :");
	scanf("%d%*c", &e.boursier);
	while (e.boursier > 1 || e.boursier < 0){
		printf("Erreur de saisie veuillez retaper (0/1) :");
		scanf("%d%*c", &e.boursier);
	}

	if (e.boursier == 0){
		e.echelon= 0;
	}
	else{	    
		printf("Saisir l'échelon de bourse de l'étudiant (1 à 7): ");
		scanf("%d%*c", &e.echelon);
		while (e.echelon<1 || e.echelon>7){
			printf("Erreur de saisie veuillez retaper (1 à 7) :");
			scanf("%d%*c", &e.echelon);
		}
	}
	return e;
}

void autoId(int nbIdEtud,char idDemande[]){
	char zeros[4];
	nbIdEtud++;
	if(nbIdEtud<10)
		strcpy(zeros,"000\0");
	else if(nbIdEtud<100)
		strcpy(zeros,"00\0");
	else if(nbIdEtud<1000)
		strcpy(zeros,"0\0");
	else
		strcpy(zeros,"\0");
	FILE *flot;
	flot=fopen("buffer.don","w");
    if(flot==NULL){
		strcpy(idDemande,"\0");
        return;
	}
	fprintf(flot,"D%s%d",zeros,nbIdEtud);
	fclose(flot);
	flot=fopen("buffer.don","r");
    if(flot==NULL){
		strcpy(idDemande,"\0");
        return;
	}
	fscanf(flot,"%s",idDemande);
	fclose(flot);
	idDemande[5]='\0';
}

Demande saisieDemande(Etudiant e, int nbIdEtud){
	Demande demande;
	int trouve, l;
	char chaine[50];
	autoId(nbIdEtud,demande.idDemande);
	if(strlen(demande.idDemande)==0)
		return demande;
	printf("Saisir cité : ");
	fgets(chaine,50,stdin);
	l=strlen(chaine);
	if(chaine[l-1]=='\n'){
    	chaine[l-1]='\0';
    	l--;
	}
	strcpy(demande.citeDemande,chaine);
	printf("Saisir type logement (Chambre / Studio / T1 / T2) : ");
	scanf("%s%*c",demande.type);
	while(strcmp(demande.type,"Chambre")!=0 && strcmp(demande.type,"Studio")!=0 && strcmp(demande.type,"T1")!=0 && strcmp(demande.type,"T2")!=0){
		printf("Erreur de saisie veuillez recommencer (Chambre / Studio / T1 / T2) : ");
		scanf("%s%*c",demande.type);
	}
	strcpy(demande.idEtudDemande,e.idEtud);
	demande.echelonEtud=e.echelon;
	return demande;
}

Etudiant* nouveauEtud(Etudiant *tabEtud, int* nbEtud, int* pos){
	int trouve, t;
	char etudSaisie[6];
	Etudiant e;
	Etudiant* tab;


	printf("Veuillez saisir l'ID de l'étudiant: ");
	scanf("%s%*c", etudSaisie);
	
	*pos=rechercheDichoEtud(tabEtud, etudSaisie, *nbEtud, &trouve);

	if (trouve == 0){
		e=saisieEtudControle();
		strcpy(e.idEtud, etudSaisie);

		tab=(Etudiant*)realloc(tabEtud,(*nbEtud+1)*sizeof(Etudiant));
		if (tab == NULL){
			printf("problème de réallocation");
			exit(1); 
		}
		tabEtud=tab;
		tabEtud[*nbEtud]=e;	
		*pos=*nbEtud;
		(*nbEtud)++;
		
	}
	return tabEtud;
}

ListeDemande nouvelleDemande(Etudiant *tabEtud, ListeDemande l, int nbEtud, int* nbIdDemande, int pos){
	Demande demande;
	
	demande=saisieDemande(tabEtud[pos], *nbIdDemande);
	if(strlen(demande.idDemande)==0){
		printf("Erreur génération idDemande. Demande annulée\n");
		return l;
	}
	l=ajouterDecroissant(l, demande);
	(*nbIdDemande)++;
	return l;
}


int verifHandicap(Etudiant tabEtud[], char id[], int nbEtud){
	for(int i=0;i<nbEtud;i++)
		if(strcmp(tabEtud[i].idEtud,id)==0)
			return tabEtud[i].handicap;
}

ListeDemande rechercheEtSuppressionDemande(char cite[], char type[], int handicapAdapte, ListeDemande listeDemandes,Etudiant tabEtud[], char idEtud[], int nbEtud){
	int cmpCite, 
	cmpType, handicap;
	MaillonDemande *tmp;
	if(listeDemandes==NULL)
		return listeDemandes;
	handicap=verifHandicap(tabEtud,listeDemandes->suiv->demande.idEtudDemande, nbEtud);
	if(handicap==handicapAdapte){
		cmpCite=strcmp(listeDemandes->suiv->demande.citeDemande,cite);
		cmpType=strcmp(listeDemandes->suiv->demande.type,type);
		if(cmpCite==0 && cmpType==0){
			strcpy(idEtud,listeDemandes->suiv->demande.idEtudDemande);
			tmp=listeDemandes;
			listeDemandes=tmp->suiv;
			free(tmp);
		}
	}
	else
		listeDemandes->suiv=rechercheEtSuppressionDemande(cite, type, handicapAdapte, listeDemandes->suiv, tabEtud, idEtud, nbEtud);
	return listeDemandes;
}

ListeDemande traitementDemandeAttente(ListeDemande listeDemandes, Logement *tabLoge[], Etudiant tabEtud[], int nbLoge, int nbEtud){
	int pos;
	char idEtud[6]="00000";

	for(int i=0; i<nbLoge;i++){
		if(listeDemandes==NULL)
			return NULL;
		if(tabLoge[i]->dispo==1){
			listeDemandes=rechercheEtSuppressionDemande(tabLoge[i]->cite, tabLoge[i]->type, tabLoge[i]->handicapAdapte,listeDemandes, tabEtud, idEtud, nbEtud);
			if(strcmp(idEtud,"00000")!=0){
				tabLoge[i]->dispo=0;
				strcpy(tabLoge[i]->idEtudOccup,idEtud);
				strcpy(idEtud,"00000");
			}
		}	
	}
	return listeDemandes;
}

ListeDemande supprimerEnTete(ListeDemande listeDemandes){
	MaillonDemande *tmp;
	tmp=listeDemandes;
	listeDemandes=tmp->suiv;
	free(tmp);
	return listeDemandes;
}


ListeDemande supprimerMaillonDemande(ListeDemande listeDemandes,char idDemande[], int *trouve){
	if(listeDemandes==NULL)
		return listeDemandes;
	if(strcmp(listeDemandes->demande.idDemande,idDemande)==0){
		listeDemandes=supprimerEnTete(listeDemandes);
		*trouve=1;
	}
	else
		listeDemandes->suiv=supprimerMaillonDemande(listeDemandes->suiv, idDemande, trouve);
	return listeDemandes;
}

ListeDemande annulationDemande(ListeDemande listeDemandes){
	char idDemandeSupp[6];
	int trouve=0;
	
	printf("Veuillez saisir l'ID de la demande à annuler : ");
	scanf("%s", idDemandeSupp);

	listeDemandes=supprimerMaillonDemande(listeDemandes, idDemandeSupp, &trouve);
	if (trouve==0)
		printf("Erreur, ID introuvable\n");
	return listeDemandes;
}

int rechercheParcoursLoge(Logement **tabLoge, int nbLoge, char idLoge[]){
	for(int i=0; i<nbLoge; i++)
		if(strcmp(tabLoge[i]->idLoge,idLoge)==0)
			return i;
	return -1;
}




void changementDispoLoge(Logement ** tabLoge,char idLoge[],int nbLoge, int pos){
	if(tabLoge[pos]->dispo==0){
		strcpy(tabLoge[pos]->idEtudOccup,"\0");
		tabLoge[pos]->dispo=1;
	}
	else{
		printf("Erreur, le logement est déjà libre\n");
		return;
	}
}

void liberationLogement(Logement ** tabLoge,int nbLoge){
	char idLogementLib[6];
	int pos;
	printf("Veuillez saisir l'ID de logement à libérer : ");
	scanf("%s", idLogementLib);
	pos = rechercheParcoursLoge(tabLoge,nbLoge,idLogementLib);
	if(pos==-1){
		printf("Erreur, le logement recherché n'existe pas\n");
		return;
	}
	changementDispoLoge(tabLoge, idLogementLib, nbLoge, pos);
}


