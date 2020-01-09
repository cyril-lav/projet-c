#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum booleen{FAUX=0,VRAI=1} Booleen;

typedef enum typelog{
    CHAMBRE, 
    STUDIO,
    T1,
    T2
} Type;

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
	Type type;
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
	Type type;
}Demande;

typedef struct MailleDema {
    Demande demande;
    struct MailleDema* suivant;
} MaillonDemande;

typedef MaillonDemande *ListeDemande;


//Chargement
Etudiant lireEtud(FILE *fe);
Logement lireLogement(FILE *feLoge);
ListeDemande ajouterDemandeEnTete(ListeDemande listeDemande, Demande demande);

Etudiant* chargeEtudiant(FILE *fe, int* nbEtud);
int chargeLogement(Logement* tab[], int tmax, FILE* feLoge);
ListeDemande chargeDemande(FILE* fe, int* nbLog);

// Affichage
void menu(void);
void affichLogeOccup(Logement *tabLoge[], int nbLoge);
void affichLogeDispo(Logement *tabLoge[], int nbLoge);
void appli(void);
void triBulle(Logement *tabLoge[], int nb);

