#include <stdio.h>

typedef enum booleen{FAUX=0,VRAI=1} Booleen;
typedef enum civilite{MR,MME} Civilite;
typedef enum type{CHAMBRE,STUDIO,T1,T2} Type;

typedef struct etudiant{
	char idEtud[6];
	char *nom;
	char *prenom;
	Civilite civ;
	Booleen handicap;
	Booleen boursier;
	int echelon;
}Etudiant;

typedef struct logement{
	char idLoge[6];
	char *cite;
	Type type;
	Booleen handicapAdapte;
	Booleen dispo;
	char idEtudOccup[6];
}Logement;

typedef struct demande{
	char idDemande[6];
	char idEtudDemande[6];
	int echelonEtud;
	char *citeDemande;
	Type typeDemande;
}Demande;