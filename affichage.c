#include "projet.h"
#include <string.h>
#include <stdlib.h>


#define BLEUCLAIR "\033[01;34m"
#define ROUGE "\033[00;31m"
#define BLEU "\033[00;34m"





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
  printf("#  8-Sauvegarde des fichier                   #\n");
  printf("#  9-Quitter                                  #\n");
  printf("###############################################\n\n");
}



void affichLogeOccup(Logement* tabLoge[],int nbLog){
  int i;
  for(i=0; i < nbLog; i++){
    if(tabLoge[i]->dispo == 0){
      printf("%s %s %s \t %d %d %s \n", tabLoge[i]->idLoge, tabLoge[i]->cite, tabLoge[i]->type, tabLoge[i]->handicapAdapte, tabLoge[i]->dispo, tabLoge[i]->idEtudOccup);
    }
  }
}
  

// Menu -> 1)
void affichLogeDispo(Logement* tabLoge[],int nbLog){
  int i;
  for(i=0; i < nbLog; i++){
    if(tabLoge[i]->dispo == 1){
      printf("%s %s %s \t %d %d \n", tabLoge[i]->idLoge, tabLoge[i]->cite, tabLoge[i]->type, tabLoge[i]->handicapAdapte, tabLoge[i]->dispo);
    }
  }
}

void affichEtud(Etudiant *tab,int nbEtud){
	for(int i=0;i<nbEtud;i++)
		printf("%s %s %s %s %d %d %d",tab[i].idEtud, tab[i].nom, tab[i].prenom, tab[i].civ, tab[i].handicap, tab[i].boursier, tab[i].echelon);
}

void affichDemande(ListeDemande l){
	if(l == NULL)return;
	printf("%s %s %d %s %s\n",l->demande.idDemande, l->demande.idEtudDemande, l->demande.echelonEtud, l->demande.citeDemande, l->demande.type);
	affichDemande(l->suivant);
}


/////////////////////////////////////////////////////////////////:

void sauvEtud(Etudiant tEtud[], char nomFichier[30], int nbEtud){
  FILE* fs;
  fs=fopen(nomFichier,"wb");
  if(fs==NULL){
    printf("Problème ouverture fichier\n");
    return;
  }
  fprintf(fs,"%d",nbEtud);
  fwrite(tEtud,sizeof(Etudiant),nbEtud,fs);
  fclose(fs);
}

Etudiant* restaureEtud(char nomFichier[30], int *nbEtud){
  FILE* fe;
  Etudiant* d;
  fe=fopen(nomFichier,"rb");
  if(fe==NULL){
    printf("Problème ouverture fichier\n");
    exit(1);
  }
  fscanf(fe,"%d",*nbEtud);
  d=(Etudiant*)malloc(sizeof(Etudiant)* *nbEtud);
  if(d==NULL){
    printf("Problème allocation mémoire\n");
    exit(1);
  }
  fread(d,sizeof(Etudiant),*nbEtud,fe);
  fclose(fe);
  return d;
}

void sauvLoge(Logement* tabLoge[], char nomFichier[30], int nbLoge){
  FILE* fs;
  int i;
  fs=fopen(nomFichier,"w");
  if(fs==NULL){
    printf("Problème ouverture fichier\n");
    return;
  }
  fprintf(fs,"%d\n",nbLoge);
  for(i=0 ; i<nbLoge ; i++){
    if(tabLoge[i]->dispo == 1){
      printf("%s %s %s \t %d %d \n", tabLoge[i]->idLoge, tabLoge[i]->cite, tabLoge[i]->type, tabLoge[i]->handicapAdapte, tabLoge[i]->dispo);
    }
    if(tabLoge[i]->dispo == 0){
      printf("%s %s %s \t %d %d %s \n", tabLoge[i]->idLoge, tabLoge[i]->cite, tabLoge[i]->type, tabLoge[i]->handicapAdapte, tabLoge[i]->dispo, tabLoge[i]->idEtudOccup);
    }
  }
}

void sauvDemande(){

}
