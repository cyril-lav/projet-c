#include <stdio.h>


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
	char citeDemande[30];
	char type[8];
}Demande;

typedef struct MailleDema {
    Demande demande;
    struct MailleDema* suivant;
} MaillonDemande;

typedef MaillonDemande *ListeDemande;


//Chargement
Logement lireLogement(FILE *feLoge);
Etudiant lireEtud(FILE *fe);
ListeDemande ajouterDemandeEnTete(ListeDemande listeDemandes, Demande demande);
ListeDemande ajouterDecroissant(ListeDemande listeDemandes, Demande demande);
ListeDemande listeVide(void);

Etudiant* chargeEtudiant(int* nbEtud);
int chargeLogement(Logement* tab[], int tmax);
ListeDemande chargeDemande(void);

// Affichage
void menu(void);
void affichLogeOccup(Logement *tabLoge[], int nbLoge);
void affichLogeDispo(Logement *tabLoge[], int nbLoge);
void affichDemande(ListeDemande l);
void appli(void);
void triBulleLoge(Logement *tabLoge[], int nb);
void triBulleDemande(Demande *tabDemande[], int nbDemande);

void sauvEtud(Etudiant tEtud[], char nomFichier[30], int nbEtud);
Etudiant* restaureEtud(char nomFichier[30], int *nbEtud);
void sauvLoge(Logement* tabLoge[], char nomFichier[30], int nbLoge);
void sauvDemande();

void affichEtud(Etudiant *tab,int nbEtud);

void conversion(void);

// Traitement
void copier(Etudiant *tabEtud,int deb, int fin, Etudiant tab[]);
void fusion(Etudiant tab1[],int nbtab1, Etudiant tab2[], int nbtab2,Etudiant tabEtud[]);
void triDichoEtud(Etudiant *tabEtud,int nbEtud);