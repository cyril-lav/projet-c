#include "projet.h"
#include <string.h>
#include <stdlib.h>


/*
Fonction: triBulleDemande
Finalité: trier (Bulle) les Demandes par ordre décroissant des Echelons Boursiers

Paramètres (entrant/sortant): 
	tabDemande : tableau des Demandes

Paramètre (entrant): 
	nbDemande : nombre de Demandes

Variables: 	
	i : indice de boucle
	cpt : compteur (si == 0 alors aucun changement)
*/
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

/*
Fonction: posMin
Finalité: Donne la position de la cité alphabetiquement dernière

Paramètres (entrant/sortant): 
	tabLoge : tableau de Logements

Paramètre (entrant) : 
	nbLoge : nombre de Logements

Variables: 	
	i : indice de boucle
	pos : position du Logement à échanger
	logeCite : cité du Logement

Valeur retournée: 
	pos : position du Logement à échanger
*/
int posMin(Logement* tabLoge[], int nbLoge){
	char* logeCite=tabLoge[0]->cite;
  	int pos=0, i;
  	for(i=1 ; i<nbLoge ; i++){
    	if(strcmp(tabLoge[i]->cite,logeCite)>0){
      	logeCite=tabLoge[i]->cite;
      	pos=i;
    	}
  	}
  	return pos;
}

/*
Fonction: triSelectEchLoge
Finalité: trier (SelectEchange) les Logements par ordre alphabtique

Paramètres (entrant/sortant): 
	tabLoge : tableau de Logements

Paramètre (entrant) : 
	nbLoge : nombre de Logements

Variables: 
	pos : position du Logement à échanger avec le premier Logement
	loge : Logement provisoire
*/
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

/*
Fonction: partitionner
Finalité: ///

Paramètres (entrant/sortant): 
	tabEtud : tableau d'Etudiants

Paramètre (entrant) : 
	deb :	position du premier élément
	fin :	position du dernier élément

Variables: 
	pivot : 
	w : sauvegarde temporaire d'un étudiant pour intervetir 2 éléments du tableau
	i :	position à partir de laquelle tous les éléments précédents sont inférieurs au pivot
	j :

Valeur retournée:
	i : 
*/
int partitionner(Etudiant tabEtud[], int deb, int fin){
	Etudiant pivot=tabEtud[fin], w;
	int i=deb;
	for(int j=deb;j<=fin-1;j++){
		if(strcmp(tabEtud[j].idEtud,pivot.idEtud)<0){
			w=tabEtud[i];
			tabEtud[i]=tabEtud[j];
			tabEtud[j]=w;
			i++;
		}
	}
	w=tabEtud[i];
	tabEtud[i]=tabEtud[fin];
	tabEtud[fin]=w;
	return i;
}

/*
Fonction: triRapide
Finalité: ///

Paramètre (entrant/sortant): 
	tabEtud : tableau d'Etudiants

Paramètres (entrants) : 
	deb :	position du premier élément du tableau
	fin :

Variables: 
	posPivot : position du pivot
*/
void triRapide(Etudiant tabEtud[], int deb, int fin){
	int posPivot;
	if(deb<fin){
		posPivot=partitionner(tabEtud,deb,fin);
		triRapide(tabEtud,deb,posPivot-1);
		triRapide(tabEtud,posPivot+1,fin);
	}
}

/*
Fonction: rechercheDichoEtud
Finalité: recherche 

Paramètres (entrant/sortant): 
	tab : tableau d'Etudiants
	trouve : vaut 1 si trouvé, sinon 0
	etud : chaine de caractères Etudiant cherché

Paramètres (entrant) : 
	nbEtud : nombre d'Etudiants

Variables :
	deb : position de début dans le tableau
	m : moyenne de début+fin
	fin : position de fin dans le tableau
	cmp : compteur
	
Valeur retournée:
	m : la position de l'Etudiant cherché OU -1 si non trouvé
*/
int rechercheDichoEtud(Etudiant* tab, char etud[6], int nbEtud, int* trouve){
	int deb=0, m, fin=nbEtud-1, cmp;
	while(deb <= fin){
		m=(deb+fin)/2;
		cmp=strcmp(etud, tab[m].idEtud);
		if(cmp == 0){
			*trouve=1;
			return m;
		}
		if (cmp < 0)
			fin=m-1;
		else deb=m+1;
	}
	return -1;
}

/*
Fonction: saisieEtudControle
Finalité: saisir un nouvel Etudiant
	
Variables :
	e : Etudiant
	chaine : chaine de caractères saisie sur stdin, le nom de l'Etudiant
	l : longueur de la chaine (e.nom)
	
Valeur retournée:
	e : Etudiant 
*/
Etudiant saisieEtudControle(void){
	int l;
	char chaine[50];
	Etudiant e;


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
	scanf("%s%*c", e.civ);
	while (strcmp(e.civ,"Mr")!=0 && strcmp(e.civ,"Mme")!=0){
		printf("Erreur de saisie veuillez retaper (Mr/Mme) :");
		scanf("%s%*c", e.civ);
	}

	printf("Saisir si l'étudiant possède un handicape (0/1) :");
	scanf("%d%*c", &e.handicap);
	while (e.handicap > 1 || e.handicap < 0){
		printf("Erreur de saisie veuillez retaper (0/1) :");
		scanf("%d%*c", &e.handicap);
	}

	printf("Saisir si l'étudiant est boursier (0/1) :");
	scanf("%d%*c", &e.boursier);
	while (e.boursier > 1 || e.boursier < 0){
		printf("Erreur de saisie veuillez retaper (0/1) :");
		scanf("%d%*c", &e.boursier);
	}

	if (e.boursier == 0){
		e.echelon= 0;
	}
	else{	    
		printf("Saisir l'échelon de bourse de l'étudiant (1 à 7): ");
		scanf("%d%*c", &e.echelon);
		while (e.echelon<1 || e.echelon>7){
			printf("Erreur de saisie veuillez retaper (1 à 7) :");
			scanf("%d%*c", &e.echelon);
		}
	}
	return e;
}

/*
Fonction: autoId
Finalité: saisir un nouvel Etudiant
	
Paramètre (entrant/sortant) :
	idDemande : nombre d'Id d'Etudiants

Paramètre :
	nbIdEtud : nombre après '0' dans une demande (ex: 42)
	
Variables :
	zeros : chaine de caractères constituée de 0
*/
void autoId(int nbIdEtud,char idDemande[]){
	char zeros[4];
	nbIdEtud++;
	if(nbIdEtud<10)
		strcpy(zeros,"000\0");
	else if(nbIdEtud<100)
		strcpy(zeros,"00\0");
	else if(nbIdEtud<1000)
		strcpy(zeros,"0\0");
	else
		strcpy(zeros,"\0");
	FILE *flot;
	flot=fopen("buffer.don","w");
    if(flot==NULL){
		strcpy(idDemande,"\0");
        return;
	}
	fprintf(flot,"D%s%d",zeros,nbIdEtud);
	fclose(flot);
	flot=fopen("buffer.don","r");
    if(flot==NULL){
		strcpy(idDemande,"\0");
        return;
	}
	fscanf(flot,"%s",idDemande);
	fclose(flot);
	idDemande[5]='\0';
}

/*
Fonction: saisieDemande
Finalité: saisir une nouvelle Demande
	
Paramètre :
	nbIdEtud : nombre d'Id d'Etudiants
	e : Etudiant
	
Variables :
	demande : Demande
	l : longueur de la chaine de caractères (demande.idDemande)

Valeur retournée :
	demande : nouvelle Demande
*/
Demande saisieDemande(Etudiant e, int nbIdEtud){
	Demande demande;
	int l;
	char chaine[50];
	
	autoId(nbIdEtud,demande.idDemande);
	
	if(strlen(demande.idDemande)==0)
		return demande;

	printf("Saisir cité : ");

	fgets(chaine,50,stdin);
	l=strlen(chaine);
	if(chaine[l-1]=='\n'){
    	chaine[l-1]='\0';
    	l--;
	}
	strcpy(demande.citeDemande,chaine);

	printf("Saisir type logement (CHAMBRE / STUDIO / T1 / T2) : ");
	scanf("%s%*c",demande.type);

	while(strcmp(demande.type,"CHAMBRE")!=0 && strcmp(demande.type,"STUDIO")!=0 && strcmp(demande.type,"T1")!=0 && strcmp(demande.type,"T2")!=0){
		printf("Erreur de saisie veuillez recommencer (CHAMBRE / STUDIO / T1 / T2) : ");
		scanf("%s%*c",demande.type);
	}
	strcpy(demande.idEtudDemande,e.idEtud);
	
	demande.echelonEtud=e.echelon;
	return demande;
}

/*
Fonction: nouveauEtud
Finalité: ajouter un Etudiant
	
Paramètres (entrant/sortant) :
	tabEtud : tableau d'Etudiants
	nbEtud : nombre d'Etudiants
	pos : position de l'Etudiant
	
Variables :
	trouve : valeur retournée de rechercheDichoEtud (0 si non trouvée, 1 si trouvé)
	etudSaisie : chaine de caractères saisie sur stdin, l'ID de l'Etudiant
	e : Etudiant
	tab : tableau d'Etudiants faisant le Realloc

Valeur retournée :
	tabEtud : tableau d'Etudiants
*/
Etudiant* nouveauEtud(Etudiant *tabEtud, int* nbEtud, int* pos){
	int trouve=0;
	char etudSaisie[6];
	Etudiant e;
	Etudiant* tab;


	printf("Veuillez saisir l'ID de l'étudiant: ");
	scanf("%s%*c", etudSaisie);
	
	*pos=rechercheDichoEtud(tabEtud, etudSaisie, *nbEtud, &trouve);

	if (trouve == 0){
		e=saisieEtudControle();
		strcpy(e.idEtud, etudSaisie);

		tab=(Etudiant*)realloc(tabEtud,(*nbEtud+1)*sizeof(Etudiant));
		if (tab == NULL){
			printf("problème de réallocation");
			exit(1);
		}
		tabEtud=tab;
		tabEtud[*nbEtud]=e;	
		*pos=*nbEtud;
		(*nbEtud)++;
		
	}
	return tabEtud;
}


/* 
   Fonction: nouvelleDemande
   Finalité: Active une nouvelle requête de demande

   	Paramètre entrant/sortant :
		tabEtud			- tableau d'étudiants
		nbIdDemande		- nombre d'id étudiant

	Paramètres entrants :
		l				-liste de demande
		nbEtud			-nombre d'étudiant
		pos				-position de l'étudiant qui fait la demande

    Variable : 
        demande				-une demande

	Valeur retournée : 
   		la liste de demande
*/
ListeDemande nouvelleDemande(Etudiant *tabEtud, ListeDemande l, int nbEtud, int* nbIdDemande, int pos){
	Demande demande;
	
	demande=saisieDemande(tabEtud[pos], *nbIdDemande);
	if(strlen(demande.idDemande)==0){
		printf("Erreur génération idDemande. Demande annulée\n");
		return l;
	}
	l=ajouterDecroissant(l, demande);
	(*nbIdDemande)++;
	return l;
}


/* 
   Fonction: verifHandicap
   Finalité: vérifie si l'étudiant est handicapé

   	Paramètre entrant/sortant :
		tabEtud		- tableau d'étudiants
		id				-id de l'étudiant saisie

	Paramètres entrants :
		nbEtud				-nombre d'étudiant

    Variable : 
        i				-index

	Valeur retournée : 
   		la valeur binaire si handicapé ou non
*/
int verifHandicap(Etudiant tabEtud[], char id[], int nbEtud){
	for(int i=0;i<nbEtud;i++)
		if(strcmp(tabEtud[i].idEtud,id)==0)
			return tabEtud[i].handicap;
}


/* 
   Fonction: rechercheEtSuppressionDemande
   Finalité: recherche et supprime la demande saisie

   	Paramètre entrant/sortant :
		tabEtud				- tableau d'étudiants
		cite				-nom de la cité
		type				-type de logement
		idEtud				-id de l'étudiant saisie

	Paramètres entrants :
		listeDemandes		-liste chainée de demandes
		handicapAdapte		-adapté handicapé ou pas
		nbEtud				-nombre d'étudiant

    Variables : 
        cmpCite				-compare les citées
		cmpType				-compare les types
		handicap			-verification si handicapé
		tmp					-pointeur temporaire sur maillonDemande

	Valeur retournée : 
   		la liste de demande
*/
ListeDemande rechercheEtSuppressionDemande(char cite[], char type[], int handicapAdapte, ListeDemande listeDemandes,Etudiant tabEtud[], char idEtud[], int nbEtud){
	int cmpCite, cmpType, handicap;
	MaillonDemande *tmp;
	if(listeDemandes==NULL)
		return listeDemandes;
	handicap=verifHandicap(tabEtud,listeDemandes->demande.idEtudDemande, nbEtud);
	if(handicap==handicapAdapte){
		cmpCite=strcmp(listeDemandes->demande.citeDemande,cite);
		cmpType=strcmp(listeDemandes->demande.type,type);
		if(cmpCite==0 && cmpType==0){
			strcpy(idEtud,listeDemandes->demande.idEtudDemande);
			tmp=listeDemandes;
			listeDemandes=listeDemandes->suiv;
			free(tmp);
			return listeDemandes;
		}
	}
	listeDemandes->suiv=rechercheEtSuppressionDemande(cite, type, handicapAdapte, listeDemandes->suiv, tabEtud, idEtud, nbEtud);
	return listeDemandes;
}


/* 
   Fonction: traitementDemandeAttente
   Finalité: traite automatiquement les demandes en attentes

   	Paramètre entrant/sortant :
		tabLoge		- tableau de pointeurs de logements
		tabEtud		- tableau d'étudiants

	Paramètre entrant :
		listeDemandes		-liste chainée de demandes
		nbLoge				-nombre de logement
		nbEtud				-nombre d'étudiant

    Variable : 
        idEtud				-id d'étudiant saisie

	Valeur retournée : 
   		la liste de demande
*/
ListeDemande traitementDemandeAttente(ListeDemande listeDemandes, Logement *tabLoge[], Etudiant tabEtud[], int nbLoge, int nbEtud){
	char idEtud[6]="\0";
	for(int i=0; i<nbLoge;i++){
		if(listeDemandes==NULL)
			return NULL;
		if(tabLoge[i]->dispo==1){
			listeDemandes=rechercheEtSuppressionDemande(tabLoge[i]->cite, tabLoge[i]->type, tabLoge[i]->handicapAdapte,listeDemandes, tabEtud, idEtud, nbEtud);
			if(strlen(idEtud)!=0){
				tabLoge[i]->dispo=0;
				strcpy(tabLoge[i]->idEtudOccup,idEtud);
				strcpy(idEtud,"\0");
			}
		}	
	}
	return listeDemandes;
}


/* 
   Fonction: supprimerEnTete
   Finalité: Supprime un maillon en tête dans la liste

	Paramètre entrant :
		listeDemandes		-liste chainée de demandes

    Variable : 
        tmp					-pointeur temporaire sur maillon demande

	Valeur retournée : 
   		la liste de demande
*/
ListeDemande supprimerEnTete(ListeDemande listeDemandes){
	MaillonDemande *tmp;
	tmp=listeDemandes;
	listeDemandes=tmp->suiv;
	free(tmp);
	return listeDemandes;
}


/* 
   Fonction: supprimerMaillonDemande
   Finalité: supprime un maillon de la liste de demande

	Paramètres entrants :
		listeDemandes		-liste chainée de demandes
		idDemande			-Id de demande à supprimer

	Valeur retournée : 
   		la liste de demande
*/
ListeDemande supprimerMaillonDemande(ListeDemande listeDemandes,char idDemande[], int *trouve){
	if(listeDemandes==NULL)
		return listeDemandes;
	if(strcmp(listeDemandes->demande.idDemande,idDemande)==0){
		listeDemandes=supprimerEnTete(listeDemandes);
		*trouve=1;
	}
	else
		listeDemandes->suiv=supprimerMaillonDemande(listeDemandes->suiv, idDemande, trouve);
	return listeDemandes;
}


/* 
   Fonction: annulationDemande
   Finalité: Annule une demande en attente

	Paramètre entrant :
		listeDemandes		-liste chainée de demandes

    Variables : 
        idDemandeSupp	-chaine de caractère de l'id demande saisie
		trouve			-vérifie si l'Id est trouvé

	Valeur retournée : 
   		la liste de demande
*/
ListeDemande annulationDemande(ListeDemande listeDemandes){
	char idDemandeSupp[6];
	int trouve=0;
	
	printf("Veuillez saisir l'ID de la demande à annuler : ");
	scanf("%s", idDemandeSupp);

	listeDemandes=supprimerMaillonDemande(listeDemandes, idDemandeSupp, &trouve);
	if (trouve==0)
		printf("Erreur, ID introuvable\n");
	else 
		printf("Suppression effectuée\n");
	return listeDemandes;
}


/* 
   Fonction: rechercheParcoursLoge
   Finalité: recherche dans le tableau de logement

	Paramètre entrant/sortant :
		tabLoge		- tableau de pointeurs de logements

	Paramètres entrants :
		nbLoge		-nombre de logements
		idLoge		-chaine de caractère de l'id logement saisie

    Variable : 
		i				-index
	
	Valeur retournée : 
   		la position
*/
int rechercheParcoursLoge(Logement **tabLoge, int nbLoge, char idLoge[]){
	for(int i=0; i<nbLoge; i++)
		if(strcmp(tabLoge[i]->idLoge,idLoge)==0)
			return i;
	return -1;
}


/* 
   Fonction: changementDispoLoge
   Finalité: change l'état d'un logement
   
	Paramètre entrant/sortant :
		tabLoge		- tableau de pointeurs de logements

	Paramètres entrants :
		nbLoge		-nombre de logements
		idLoge		-chaine de caractère de l'id logement saisie
		pos			-position de l'id saisie

*/
void changementDispoLoge(Logement ** tabLoge,char idLoge[],int nbLoge, int pos){
	if(tabLoge[pos]->dispo==0){
		strcpy(tabLoge[pos]->idEtudOccup,"\0");
		tabLoge[pos]->dispo=1;
	}
	else{
		printf("Erreur, le logement est déjà libre\n");
		return;
	}
}


/* 
   Fonction: liberationLogement
   Finalité: Change l'état du logment saisie

	Paramètre entrant/sortant :
		tabLoge		- tableau de pointeurs de logements

	Paramètre entrant :
		nbLoge		-nombre de logements

    Variables : 
        idLogementLib	-chaine de caractère de l'id logement saisie
		pos				-position de l'id saisie
*/
void liberationLogement(Logement ** tabLoge,int nbLoge){
	char idLogementLib[6];
	int pos;
	printf("Veuillez saisir l'ID de logement à libérer : ");
	scanf("%s", idLogementLib);
	pos = rechercheParcoursLoge(tabLoge,nbLoge,idLogementLib);
	if(pos==-1){
		printf("Erreur, le logement recherché n'existe pas\n");
		return;
	}
	changementDispoLoge(tabLoge, idLogementLib, nbLoge, pos);
}


