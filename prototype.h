#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include <windows.h>
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define BLACK "\033[0;30m"
#define BOLD "\033[1m"
#define BROWN "\033[0;33m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define SOURIRE "\U0001F600"
#define SAD "\U0001F641"
#define GOOD "\U0001F44D"
#define WRONG "\U0001F44E"
#define GOODBYE "\U0001F44B"
#define UNDERLINE "\033[4m"
#define RESET "\033[0m"

#ifndef PROTOTYPE_H
#define PROTOTYPE_H

//Information de l'universiter
typedef struct {
    char nom[100];
    char sigle[20];
    char adresse[150];
    char telephone[30];
    char email[50];
} InfoUniversite;

//0-Structure note
typedef struct Note
{
    char codeCours[10];
    float valeurNote;
    struct Note *suiv;
}Note;

//1-Structure Etudiant
typedef struct Etudiant
{
    char matricule[30];
    char nom[50];
    char prenom[30];
    int age;

    char faculterChoisie[50];
    char filiereChoisie[50];
    int nbr;
    struct Note *listeNote;
    struct Etudiant *suiv;
}Etudiant;

//Sructure Question
typedef struct Question
{
    char enonce[200];
    char optA[100];
    char optB[100];
    char optC[100];
    char optD[100];
    char bonneRep;
    struct Question *suiv;
}Question;

//2-Stucture cours(UE)
typedef struct Cours
{
    char code[10];
    char nomUE[30];
    char nomEnseignant[50];
    char contenu[1000];
    struct Question *listeQuestion;
    struct Cours *suiv;
}Cours;

//3-Structure Filiere
typedef struct Filiere
{
    char nomFilier[50];
    struct Cours *listeCours;
    struct Filiere *suiv;
}Filiere;

//4-Structure Faculter
typedef struct Faculter
{
    char nomFaculter[50];
    char codeFaculter[10];

    struct Filiere *listeFiliere;
    struct Faculter *suiv; 
}Faculter;

//FACULTER
Faculter *AjouterFac(Faculter *li,char code[10],char nom[50]);
Faculter *ajouterFiliere(Faculter *li,char codeFac[10],char nomFiliere[50]);
void ajouterCours(Faculter *li,char codeFac[10],char nomFiliere[50],char codeCours[10],char nomUE[30],char nomE[30],char contenu[1000]);
void ajouterQuestion(Faculter *li,char codeCours[10],char enonce[200],char optA[100],char optB[100],char optC[100],char optD[100],char rep);
void aficherConfig(Faculter *li);
void afficherStat(Faculter *listeFac, Etudiant *listeEtud);
void affichetEtudiant(Etudiant *li);

//ETUDIANT
Etudiant *AjouterEtudiant(Etudiant *li,char mat[30],char nom[50],char prenom[30],int age,char fac[50],char fil[50]);
void passerQcm(Etudiant *li,Faculter *liFac,char mat[30],char codeCours[10]);
void affichetEtudiant(Etudiant *li);
void afficherProfilEtudiant(const Etudiant *listeGlobale, const char *matriculeRecherche) ;

//Administration
Faculter *menuAdmin(Faculter *Universite,Etudiant *listeEtudiant, InfoUniversite *univ);
Etudiant *menuEtudiant(Faculter *Universiter,Etudiant *liEtudiant);

// Prototypes pour la gestion du fichier JSON
void sauvegarderDonnees(InfoUniversite info,Faculter *universite, Etudiant *listeEtudiants, const char *nomFichier) ;
Faculter* chargerDonnees(InfoUniversite *info,Faculter **universite, Etudiant **listeEtudiants, const char *nomFichier);

//Congiguration
void configurationInfoUni(InfoUniversite *univ,char nom[100],char sigle[20],char adresse[15],char numTel[30],char email[50]);

//trace
void trace1();
void trace2();
#endif //PROTOTYPE_H 