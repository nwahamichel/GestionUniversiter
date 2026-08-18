#include "prototype.h"

//Configuration des informations de l'universiter
void configurationInfoUni(InfoUniversite *univ,char nom[100],char sigle[20],char adresse[15],char numTel[30],char email[50])
{
    if (univ == NULL)
    {
        return;
    }
    strcpy(univ->nom,nom);
    strcpy(univ->sigle,sigle);
    strcpy(univ->adresse,adresse);
    strcpy(univ->telephone,numTel);
    strcpy(univ->email,email);
}

//Ajouter une faculter
Faculter *AjouterFac(Faculter *li,char code[10],char nom[50])
{
    Faculter *nouv = (Faculter*)malloc(sizeof(Faculter));
    if(nouv == NULL)
    {
        printf("Allocation echouer\n");
        return li;
    }
    strcpy(nouv->codeFaculter,code);
    strcpy(nouv->nomFaculter,nom); 
    nouv->listeFiliere = NULL;
    nouv->suiv = NULL;
    if(li == NULL)
    {
        printf("Faculter [%s] creee avec succes\n",nom);
        return nouv;
    }else{
        Faculter *tmp = li;
        while(tmp->suiv != NULL)
        {
            tmp = tmp->suiv;
        }
        tmp->suiv = nouv;
        printf("Faculter [%s] creee avec succes\n",nom);
        return li;
    }
}

//Ajouter filiere
Faculter *ajouterFiliere(Faculter *li,char codeFac[10],char nomFiliere[50])
{
    if(li == NULL)
    {
        printf("Aucune faculter.\n");
        return li;
    }
    Faculter *tmpFac = li;
    while(tmpFac != NULL && strcmp(tmpFac->codeFaculter,codeFac)!= 0)
    {
        tmpFac = tmpFac->suiv;
    }
    if(tmpFac == NULL)
    {
        printf("Erreur : La faculter avec le code [%s] n'existe pas\n",codeFac);
        return li;
    }
    Filiere *nouvFil = (Filiere*)malloc(sizeof(Filiere));
    if (nouvFil == NULL)
    {
        printf("Allocation echouer\n");
        return li;
    }
    strcpy(nouvFil->nomFilier,nomFiliere);
    nouvFil->listeCours = NULL;
    nouvFil->suiv = NULL;

    if(tmpFac->listeFiliere == NULL)
    {
        tmpFac->listeFiliere = nouvFil;
    }else
    {
        Filiere *tmpFil = tmpFac->listeFiliere;
        while(tmpFil->suiv != NULL)
        {
            tmpFil = tmpFil->suiv;
        }
        tmpFil->suiv = nouvFil;
    }
    printf("Filiere [%s] ajoutee avec succes dans la faculter '%s'\n",nomFiliere,tmpFac->nomFaculter);
    return li;
}

//ajouter un cours
void ajouterCours(Faculter *li,char codeFac[10],char nomFiliere[50],char codeCours[10],char nomUE[30],char nomE[30],char contenu[1000])
{
    if(li == NULL)
    {
        printf("Aucune faculter\n");
        return ;
    }
    Faculter *tmpFac = li;
    while(tmpFac != NULL && strcmp(tmpFac->codeFaculter,codeFac)!= 0)
    {
        tmpFac = tmpFac->suiv;
    }
    if(tmpFac == NULL)
    {
        printf("Erreur: La faculter avec le code [%s] n'existe pas\n",codeFac);
        return ;
    }
    if(tmpFac->listeFiliere == NULL)
    {
        printf("Erreur: Aucune filiere\n");
        return ;
    }
    Filiere *tmpFil = tmpFac->listeFiliere;
    while(tmpFil != NULL && strcmp(tmpFil->nomFilier , nomFiliere)!= 0)
    {
        tmpFil = tmpFil->suiv;
    }
    if(tmpFil == NULL)
    {
        printf("Erreur : Aucune filiere avec le nom [%s] dans la faculter [%s]\n",nomFiliere,tmpFac->nomFaculter);
        return ;
    }
    Cours *nouvCours = (Cours*)malloc(sizeof(Cours*));
    if(nouvCours == NULL)
    {
        printf("Erreur : Allocation echouer\n");
        return ;
    }
    strcpy(nouvCours->code,codeCours);
    strcpy(nouvCours->nomUE,nomUE);
    strcpy(nouvCours->nomEnseignant,nomE);
    strcpy(nouvCours->contenu,contenu);
    nouvCours->listeQuestion = NULL;
    nouvCours->suiv = NULL;
    if(tmpFil->listeCours == NULL)
    {
        tmpFil->listeCours = nouvCours;
    }else
    {
        Cours *tmpCours = tmpFil->listeCours;
        while(tmpCours->suiv != NULL)
        {
            tmpCours = tmpCours->suiv;
        }
        tmpCours->suiv = nouvCours;
    }
    printf("Cours [%s]->'%s' ajoute avec succes dans la filiere %s \n",codeCours,nomUE,nomFiliere);
}

//Creation des question pour chaque cours
void ajouterQuestion(Faculter *li,char codeCours[10],char enonce[200],char optA[100],char optB[100],char optC[100],char optD[100],char rep)
{
    if(li == NULL)
    {
        printf("Erreur : Aucune faculter \n");
        return ;
    }
    Cours *coursCible = NULL;
    Faculter *f = li;
    while(f != NULL && coursCible == NULL)
    {
        Filiere *fil = f->listeFiliere;
        while(fil != NULL && coursCible == NULL)
        {
            Cours *c = fil->listeCours;
            while(c != NULL)
            {
                if(strcmp(c->code,codeCours) == 0)
                {
                    coursCible = c;
                    break;
                }
                c = c->suiv;
            }
            fil = fil->suiv;
        }
    f = f->suiv;
    }
    if (coursCible == NULL)
    {
        printf("Erreur : Impossible de cree le QCMs. Le cours %s n'existe pas \n",codeCours);
        return ;
    }
    Question *nouvQ = (Question*)malloc(sizeof(Question));
    if(nouvQ == NULL)
    {
        printf("Erreur : Allocation echouer\n");
        return ;
    }   
    strcpy(nouvQ->enonce,enonce);
    strcpy(nouvQ->optA,optA);
    strcpy(nouvQ->optB,optB);
    strcpy(nouvQ->optC,optC);
    strcpy(nouvQ->optD,optD);
    nouvQ->bonneRep = rep;
    nouvQ->suiv = NULL;
    if(coursCible->listeQuestion == NULL)
    {
        coursCible->listeQuestion = nouvQ;
    }else
    {
        Question *tmpQ = coursCible->listeQuestion;
        while(tmpQ->suiv != NULL)
        {
            tmpQ = tmpQ->suiv;
        }
        tmpQ->suiv = nouvQ;
    }
    printf("Question ajouter avec succes au QCMs du cours %s \n",codeCours);
}

//Afficher configuration
void aficherConfig(Faculter *li)
{
    if(li == NULL)
    {
        printf("L'universiter ne contient aucune faculter pour le momment\n");
        return ;
    }
    Faculter *f = li;
    printf("-------------ARCHITECTURE DE L'UNIVERSITE (MIN-UNI)------------------\n");
    while(f != NULL)
    {
        printf("[Faculter] : %s (%s)\n",f->nomFaculter,f->codeFaculter);
        Filiere * fil = f->listeFiliere;
        if(fil == NULL)
        {
            printf("     |___Aucune filiere creee\n");
        }else
        {
            while(fil != NULL)
            {
                printf("      |__[Filiere] : %s\n",fil->nomFilier);
                Cours *c = fil->listeCours;
                if(c == NULL)
                {
                     printf("      |___(Aucun cours enregistre)\n6");
                }else
                {
                    while(c != NULL)
                    {   
                        printf("         |___[Cours] : %s - %s (par : %s)\n",c->code,c->nomUE,c->nomEnseignant);
                        c = c->suiv;
                    }
                }
                fil = fil->suiv;
            }
        }
        f = f->suiv;
    }
    return ;
}

//Aicher statistique
void afficherStat(Faculter *listeFac, Etudiant *listeEtud)
{
    int nbFac = 0, nbFil = 0, nbCours = 0, nbEtudiants = 0;
    int totalQcmPasses = 0, totalReussites = 0;
    float sommeToutesNotes = 0.0;
    float moyenneGenerale = 0.0;

    // 1. Compter les structures de l'université
    Faculter *f = listeFac;
    while (f != NULL) 
    {
        nbFac++;
        Filiere *fil = f->listeFiliere;
        while (fil != NULL) 
        {
            nbFil++;
            Cours *c = fil->listeCours;
            while (c != NULL) {
                nbCours++;
                c = c->suiv;
            }
            fil = fil->suiv;
        }
        f = f->suiv;
    }

    // 2. Calculer le nombre d'étudiants, le taux de réussite global et la moyenne
    Etudiant *e = listeEtud;
    while (e != NULL) {
        nbEtudiants++;
        Note *n = e->listeNote;
        while (n != NULL) 
        {
            sommeToutesNotes += n->valeurNote;
            totalQcmPasses++;
            if (n->valeurNote >= 10.0) 
            { 
                totalReussites++;
            }
            n = n->suiv;
        }
        e = e->suiv;
    }

    // --- AFFICHAGE DU RAPPORT ET DES CHIFFRES ---
    printf("\n==================================================\n");
    printf("        TABLEAU DE BORD STATISTIQUE AVANCE        \n");
    printf("==================================================\n");
    printf("  > Nombre de Facultes   : %d\n", nbFac);
    printf("  > Nombre de Filieres   : %d\n", nbFil);
    printf("  > Nombre de Cours (UE) : %d\n", nbCours);
    printf("  > Total Inscriptions   : %d etudiants\n", nbEtudiants);
    printf("--------------------------------------------------\n");

    if (totalQcmPasses > 0) {
        moyenneGenerale = sommeToutesNotes / totalQcmPasses;
        float tauxReussite = ((float)totalReussites / totalQcmPasses) * 100.0;
        printf("  > Total des QCM passes : %d\n", totalQcmPasses);
        printf("  > Taux de Reussite     : %.2f%%\n", tauxReussite);
        printf("  > Moyenne Generale     : %.2f / 20\n", moyenneGenerale);
    } else {
        printf("  > Taux de Reussite     : 0.00%% (Aucun examen passe)\n");
        printf("  > Moyenne Generale     : N/A\n");
    }

    // 3. Recherche du meilleur étudiant (Major) par Filière
    printf("\n--------------------------------------------------\n");
    printf("           MAJORS PAR FILIERE (PERFORMANCE)        \n");
    printf("--------------------------------------------------\n");

    f = listeFac;
    while (f != NULL) {
        Filiere *fil = f->listeFiliere;
        while (fil != NULL) {
            
            Etudiant *majorFiliere = NULL;
            float meilleureMoyenneFiliere = -1.0;

            e = listeEtud;
            while (e != NULL) 
            {
                if (e->filiereChoisie != NULL && fil->nomFilier != NULL &&
                    strcmp(e->filiereChoisie, fil->nomFilier ) == 0)
                {
                    
                    float sommeEtud = 0.0;
                    int nbNotesEtud = 0;
                    Note *n = e->listeNote;
                    while (n != NULL) {
                        sommeEtud += n->valeurNote;
                        nbNotesEtud++;
                        n = n->suiv;
                    }

                    if (nbNotesEtud > 0) {
                        float moyenneEtud = sommeEtud / nbNotesEtud;
                        if (moyenneEtud > meilleureMoyenneFiliere) {
                            meilleureMoyenneFiliere = moyenneEtud;
                            majorFiliere = e;
                        }
                    }
                }
                e = e->suiv;
            }

            if (majorFiliere != NULL) {
                printf("  * Filiere [%s] : %s %s (Moyenne : %.2f/20)\n", 
                       fil->nomFilier, majorFiliere->nom, majorFiliere->prenom, meilleureMoyenneFiliere);
            } else {
                printf("  * Filiere [%s] : Aucun etudiant evalue.\n", fil->nomFilier);
            }

            fil = fil->suiv;
        }
        f = f->suiv;
    }

    // 4. Rapport d'analyse automatique (Utilisation de la variable réutilisée)
    printf("\n--------------------------------------------------\n");
    printf("               RAPPORT SYNTHETIQUE                \n");
    printf("--------------------------------------------------\n");
    if (nbEtudiants == 0) {
        printf(" L'universite est actuellement vide. En attente d'inscriptions.\n");
    } else if (totalQcmPasses == 0) {
        printf(" Les etudiants sont inscrits mais n'ont passe aucun examen.\n");
    } else {
        if (moyenneGenerale >= 12.0) {
            printf(" Globalement, le niveau academique est satisfaisant.\n Les etudiants s'adaptent bien aux evaluations par QCM.\n");
        } else if (moyenneGenerale >= 10.0) {
            printf(" Le niveau general est moyen. Les resultats sont stables\n mais une marge de progression reste possible.\n");
        } else {
            printf(" Attention : La moyenne generale est en dessous de la moyenne.\n Un suivi pedagogique ou une revision des cours est conseille.\n");
        }
    }
}

//Liste des profil et note
void affichetEtudiant(Etudiant *li)
{
    if(li == NULL)
    {
        printf("Erreur : Aucun etudiant inscrit pour le moment\n");
        return ;
    }
    Etudiant *tmp = li;
    printf("\n--------------------------------------------------\n");
    printf("                    LISTE DES ETUDIANTS               \n");
    printf("--------------------------------------------------\n");
    while(tmp != NULL)
    {
        printf("Matricule : %s\n",tmp->matricule);
        printf("Nom complet : %s %s | Age : %d\n",tmp->nom,tmp->prenom,tmp->age);
        printf("Orientation : %s -> %s \n",tmp->faculterChoisie,tmp->filiereChoisie);
        printf("Note obtenue aux QCm :\n");
        Note *n = tmp->listeNote;
        if(n == NULL)
        {
            printf("Erreur : Aucune note enregistree pour le moment \n");
        }else
        {
            while(n != NULL)
            {
                printf("   |__[Cours : %s] : %.2f / 20 \n",n->codeCours,n->valeurNote);
                n = n->suiv;
            }
            tmp = tmp->suiv;
        }
    }
}
