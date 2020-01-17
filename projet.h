#include <stdio.h>


typedef enum booleen{FAUX=0,VRAI=1} Booleen;

typedef struct etudiant{
	char idEtud[6];
	char *nom;
	char *prenom;
	char civ[4];
	Booleen handicap;
	Booleen boursier;
	int echelon;
}Etudiant;


typedef struct logement{
	char idLoge[6];
	char *cite;
	char type[8];
	Booleen handicapAdapte;
	Booleen dispo;
	char idEtudOccup[6];
}Logement;


typedef struct demande{
	char idDemande[6];
	char idEtudDemande[6];
	int echelonEtud;
	char citeDemande[30];
	char type[8];
}Demande;

typedef struct MailleDema {
    Demande demande;
    struct MailleDema* suiv;
} MaillonDemande;

typedef MaillonDemande *ListeDemande;


//Chargement
Etudiant lireEtud(FILE *fe);
Etudiant* chargeEtudiant(int* nbEtud);
Logement lireLogement(FILE *feLoge);
int chargeLogement(Logement* tab[], int tmax);
ListeDemande ajouterDemandeEnTete(ListeDemande listeDemandes, Demande demande);
ListeDemande ajouterDecroissant(ListeDemande listeDemandes, Demande demande);
ListeDemande listeVide(void);
ListeDemande chargeDemande(int* nbIdDemande);
void sauvEtud(Etudiant tEtud[], int nbEtud);
void sauvLoge(Logement* tabLoge[], int nbLoge);
void sauvDemande(ListeDemande listeDemandes, FILE *fsDem);
void liberationTabLog(Logement** tabLog, int nbLog);
ListeDemande liberationListeDem(ListeDemande l);

// Affichage
void menu(void);
void affichLogeOccup(Logement *tabLoge[], int nbLoge);
void affichLogeDispo(Logement *tabLoge[], int nbLoge);
void affichEtud(Etudiant *tab,int nbEtud);
void affichDemande(ListeDemande l);


// Traitement
void triBulleDemande(Demande* tabDemande[],int nbDemande);
int posMin(Logement* tabLoge[], int nbLoge);
void triSelectEchLoge(Logement* tabLoge[], int nb);
int partitionner(Etudiant tabEtud[], int deb, int fin);
void triRapide(Etudiant tabEtud[], int deb, int fin);
int rechercheDichoEtud(Etudiant* tab, char etud[6], int nbEtud, int* trouve);
Etudiant saisieEtudControle(void);
void autoId(int nbIdEtud, char idDemande[]);
Demande saisieDemande(Etudiant e, int nbIdDemande);
Etudiant* nouveauEtud(Etudiant *tabEtud, int* nbEtud, int* pos);
ListeDemande nouvelleDemande(Etudiant *tabEtud, ListeDemande l, int nbEtud, int* nbIdDemande, int pos);
int verifHandicap(Etudiant tabEtud[], char id[], int nbEtud);
ListeDemande rechercheEtSuppressionDemande(char cite[], char type[], int handicapAdapte, ListeDemande listeDemandes,Etudiant tabEtud[], char idEtud[], int nbEtud);
ListeDemande traitementDemandeAttente(ListeDemande listeDemandes, Logement *tabLoge[], Etudiant tabEtud[], int nbLoge, int nbEtud);
ListeDemande supprimerEnTete(ListeDemande listeDemandes);
ListeDemande supprimerMaillonDemande(ListeDemande listeDemandes,char idDemande[], int *trouve);
ListeDemande annulationDemande(ListeDemande listeDemandes);
int rechercheParcoursLoge(Logement **tabLoge, int nbLoge, char idLoge[]);
void changementDispoLoge(Logement ** tabLoge,char idLoge[],int nbLoge, int pos);
void liberationLogement(Logement ** tabLoge,int nbLoge);
