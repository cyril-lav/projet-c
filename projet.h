#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum booleen{FAUX=0,VRAI=1} Booleen;


//pointeur sur tableau (nombre d'étudiants indiqué dans le fichier.don)
typedef struct etudiant{
	char idEtud[6];
	char *nom;
	char *prenom;
	char civ[4];
	Booleen handicap;
	Booleen boursier;
	int echelon;
}Etudiant;


//tableau de pointeurs
typedef struct logement{
	char idLoge[6];
	char *cite;
	char type[8];
	Booleen handicapAdapte;
	Booleen dispo;
	char idEtudOccup[6];
}Logement;


//liste chaînée (nombre de demandes indiqué dans le fichier .bin)
typedef struct demande{
	char idDemande[6];
	char idEtudDemande[6];
	int echelonEtud;
	char *citeDemande;
	char typeDemande[8];
}Demande;

typedef struct MailleDema {
    Demande demande;
    struct MailleDema* suivant;
} MaillonDemande;

typedef MaillonDemande *ListeDemande;


//Chargement
Etudiant lireEtud(FILE *fe);
Logement lireLogement(FILE *feLoge);

Etudiant* chargeEtudiant(FILE *fe, int* nbEtud);
int chargeLogement(Logement* tab[], int tmax, FILE* feLoge);
ListeDemande chargeDemande(FILE* fe, int* nbLog);

// Affichage
void menu(void);
void affichLogeOccup(Logement *tabLoge[], int nbLoge);
void affichLogeDispo(Logement *tabLoge[], int nbLoge);
void appli(void);

