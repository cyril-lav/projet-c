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

