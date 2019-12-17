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
	char *citeDemande;
	char typeDemande[8];
}Demande;