#include "projet.h"
#include <string.h>
#include <stdlib.h>

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

void triBulleLoge(Logement* tabLoge[],int nb){
  int i, cpt=0;
  Logement* logementReserve;
  if(nb==0 || nb==1) return;
  for(i=0;i<nb-1;i++){
    if(strcmp(tabLoge[i]->cite,tabLoge[i+1]->cite)>0){
      logementReserve=tabLoge[i+1];
      tabLoge[i+1]=tabLoge[i];
      tabLoge[i]=logementReserve;
      cpt++;
    }
  }
  if(cpt!=0){
    triBulleLoge(tabLoge,nb-1);
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

int rechercheDichoEtud(Etudiant* tabEtud, int tlog, char etud[]){
	int deb=0, m, fin=tlog-1, cmp;
	while(deb <= fin){
		m=(deb+fin)/2;
		cmp=strcmp(etud, tabEtud[m].idEtud);
		if(cmp == 0)return m;
		if (cmp < 0)fin=m-1;
		else deb=m+1;
	}
	return -1;
}

void saisieEtudControle(Etudiant* tabEtud, int* tlog){
	int res, l;
	char etudSaisie[6], chaine[50];
	Etudiant e;

	printf("Veuillez saisir l'ID de l'étudiant: ");
	scanf("%s ", etudSaisie);
	
	res=rechercheDichoEtud(tabEtud, *tlog, etudSaisie);
	if (res == -1){
		strcpy(e.idEtud, etudSaisie);

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
		
	}

	
}


void nouvelleDemande(Etudiant *tabEtud, ListeDemande l){
	
}


ListeDemande rechercheEtSuppressionDemande(char cite[], char type[], ListeDemande listeDemandes, char idEtud[]){
	int cmpCite, cmpType;
	MaillonDemande *tmp;
	if(listeDemandes==NULL)
		return listeDemandes;
	cmpCite=strcmp(listeDemandes->suiv->demande.citeDemande,cite);
	cmpType=strcmp(listeDemandes->suiv->demande.type,type);
	if(cmpCite==0 && cmpType==0){
		strcpy(idEtud,listeDemandes->suiv->demande.idEtudDemande);
		tmp=listeDemandes;
		listeDemandes=tmp->suiv;
		free(tmp);
	}
	else
		listeDemandes->suiv=echercheEtSuppressionDemande(cite, type, listeDemandes->suiv, idEtud);
	return listeDemandes;
}

ListeDemande traitementDemandeAttente(ListeDemande listeDemandes, Logement *tabLoge[], int nbLoge){
	int pos;
	char idEtud[6]="00000";

	for(int i=0; i<nbLoge;i++){
		if(listeDemandes==NULL)
			return NULL;
		if(tabLoge[i]->dispo==1){
			listeDemandes=rechercheEtSuppressionDemande(tabLoge[i]->cite, tabLoge[i]->type,listeDemandes, idEtud);
			if(idEtud!=00000){
				tabLoge[i]->dispo=0;
				strcpy(tabLoge[i]->idEtudOccup,idEtud);
				strcpy(idEtud,"00000");
			}
		}	
	}
	return listeDemandes;
}
