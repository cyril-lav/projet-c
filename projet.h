#include <stdio.h>

typedef enum booleen{FAUX=0,VRAI=1} Booleen;
typedef enum civilite{Mr,Mme} Civilite;
typedef enum type{chambre,studio,T1,T2} Type;

typedef struct etudiant{
	char idEtud[6];
	char *nom;
	char *prenom;
	Civilite civ;
	Booleen boursier;
	int echelon;
	Booleen handicap;
}Etudiant;

typedef struct logement{
	char idLoge[6];
	char *cite;
	Type type;
	Booleen dispo;
	Booleen handicapAdapt;
	char idEtudOccup[6];
}Logement;

typedef struct demande{
	char idDemande[6];
	char idEtudDemande[6];
	int echelonEtud;
	char *citeDemande;
	Type typeDemande;
}Demande;