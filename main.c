#define TAILLE 100
#include "projet.h"
#include <string.h>
#include <stdlib.h>

void appli(void){
    int choix=0; // Choix dans le menu
    int saveDone=1;
    int nbLoge, nbEtud, nbDemande;
    char confirmQuit='X';
    Logement* tabLoge[80];
    Etudiant *tab;
    ListeDemande l;

    nbLoge=chargeLogement(tabLoge, 80);
    tab=chargeEtudiant(&nbEtud);
    l=chargeDemande(&nbDemande);

    menu();
    scanf("%d%*c",&choix);

    while(!(choix == 9 && saveDone == 1)){
        switch(choix){
            case 1:
	         affichLogeDispo(tabLoge,nbLoge);
                break;
            case 2:
                affichLogeOccup(tabLoge,nbLoge);
                break;
            case 3:
                affichDemande(l);
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                if(saveDone=='0'){
                    printf("Vous n'avez pas sauvegardé, voulez-vous quand même quitter l'application ? (O/N)\n");
                    scanf("%c%*c",&confirmQuit);
                    if(confirmQuit=='O' || confirmQuit=='o'){
                        saveDone=1;
                    }
                }
                break;
            default:
                printf("Erreur: valeur non valide\n");
        }
        if(choix==9 && saveDone==1){
            return;
        }
        menu();
        scanf("%d%*c",&choix);
    }
    return;
}

// etudiant.don -> etudiants.bin
void conversion(void){
    FILE *fe, *fs;
    int nbetud, l;
    char chaine[50];
    Etudiant tab[50];
    fe=fopen("etudiants.don","r");
    fs=fopen("etudiants.bin","wb");
    if(fs==NULL)
        printf("BIM BAM BOUM\n");
    fscanf(fe,"%d",&nbetud);
    for(int i=0;i<nbetud;i++){
        fscanf(fe,"%s%*c",tab[i].idEtud);
        fgets(chaine,50,fe);
        l=strlen(chaine);
        if(chaine[l-1]=='\n'){
            chaine[l-1]='\0';
            l--;
        }
        tab[i].nom=(char*)malloc(sizeof(char)*l);
        if(tab[i].nom==NULL)
            exit(1);
        strcpy(tab[i].nom,chaine);
        
        fgets(chaine,50,fe);
        l=strlen(chaine);
        if(chaine[l-1]=='\n'){
            chaine[l-1]='\0';
            l--;
        }
        tab[i].prenom=(char*)malloc(sizeof(char)*(l+1));
        if(tab[i].prenom==NULL)
            exit(1);
        strcpy(tab[i].prenom,chaine);
        fscanf(fe,"%s %d %d ",tab[i].civ, &tab[i].handicap, &tab[i].boursier);
        if(tab[i].boursier==1)
            fscanf(fe,"%d%*c",&tab[i].echelon);
    }
    printf("\n\nAFFICHAGE ETUDIANTS\n\n");
    for(int i=0;i<nbetud;i++){
        printf("%s %s %s %s %d %d",tab[i].idEtud,tab[i].nom,tab[i].prenom,tab[i].civ,tab[i].handicap,tab[i].boursier);
        if(tab[i].boursier==1)
            printf("%d",tab[i].echelon);
        printf("\n"); 
    }
    fclose(fe);
    fwrite(&nbetud,sizeof(int),1,fs);
    for(int i=0;i<nbetud;i++){
        fwrite(tab[i].idEtud,sizeof(char)*6,1,fs);
        l=strlen(tab[i].nom);
        fwrite(tab[i].nom,sizeof(char)*(l+1),1,fs);
        l=strlen(tab[i].prenom);
        fwrite(tab[i].prenom,sizeof(char)*(l+1),1,fs);
        l=strlen(tab[i].civ);
        fwrite(tab[i].civ,sizeof(char)*(l+1),1,fs);
        fwrite(&(tab[i].handicap),sizeof(int),1,fs);
        fwrite(&(tab[i].boursier),sizeof(int),1,fs);
        if(tab[i].boursier==1)
            fwrite(&(tab[i].echelon),sizeof(int),1,fs);
    } 
    fclose(fs);
}



//#####################################

int main(void){
	appli();
    //conversion();
}


