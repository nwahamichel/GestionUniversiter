#include "prototype.h"
//Inscrire un etudiant
Etudiant *AjouterEtudiant(Etudiant *li,char mat[30],char nom[50],char prenom[30],int age,char fac[50],char fil[50])
{
    Etudiant *nouv = (Etudiant*)malloc(sizeof(Etudiant));
    if(nouv == NULL)
    {
        printf("Allocation echouer\n");
        return li;
    }
    strcpy(nouv->matricule,mat);
    strcpy(nouv->nom,nom);
    strcpy(nouv->prenom,prenom);
    nouv->age = age;
    strcpy(nouv->faculterChoisie,fac);
    strcpy(nouv->filiereChoisie,fil);

    nouv->listeNote = NULL;
    nouv->suiv = NULL;
    if(li == NULL)
    {
        printf(GREEN"Etudiant %s inscrit avec succes\n"RESET,nom);
        return nouv;
    }
    Etudiant *tmp = li;
    while (tmp->suiv != NULL)
    {
        tmp = tmp->suiv;
    }
    tmp->suiv = nouv;
    printf(GREEN"Etudiant %s inscrit avec succes\n"RESET,nom);
    return li;
}

//Passer QCMs
void passerQcm(Etudiant *li,Faculter *liFac,char mat[30],char codeCours[10])
{
    Etudiant *e = li;
    while(e != NULL && strcmp(e->matricule,mat)!= 0)
    {
        e = e->suiv;
    }
    if(e == NULL)
    {
        printf(RED"Erreur : Etudiant avec le matricule [%s] introuvable\n"RESET,mat);
        return ;
    }
    Cours *coursCible = NULL;
    Faculter *f = liFac;
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
        printf(RED"Erreur : Le cours %s n'existe pas \n"RESET,codeCours);
        return ;
    }
    if(coursCible->listeQuestion == NULL)
    {
        printf(RED"Erreur : Aucun QCM n'est disponible pour ce cours\n"RESET);
        return ;
    }
    trace1();
    printf("                 DEBUT DE L'EXAMEN\n");
    Question *q = coursCible->listeQuestion;
    int totalQuetion = 0;
    int bonneReponse = 0;
    char choixEtud;
    while(q != NULL)
    {
        totalQuetion ++;
        printf("Question %d : %s\n",totalQuetion,q->enonce);
        printf("A) %s\n",q->optA);
        printf("B) %s\n",q->optB);
        printf("C) %s\n",q->optC);
        printf("D) %s\n",q->optD);
        printf("Votre reponse :");
        scanf("%c",&choixEtud);
        getchar();

        if (choixEtud == q->bonneRep || choixEtud == (q->bonneRep + 32) || choixEtud == (q->bonneRep - 32))
        {
            printf(GREEN"Bonne reponse ✔\n"RESET);
            bonneReponse ++;
        } else
        {
            printf(RED"Mauvaise reponse ❌\n"RESET);
        }
        q = q->suiv;
    }
    float noteFinal = ((float)bonneReponse / totalQuetion) *20.0;
    printf("\nExamen termine ! Score : %d / %d | Note : %2.f / 20\n",bonneReponse,totalQuetion,noteFinal);
    Note *nouv = (Note*)malloc(sizeof(Note));
    if (nouv == NULL)
    {
        printf(RED"Erreur : Allocation echouer\n"RESET);
        return ;
    }
    strcpy(nouv->codeCours,codeCours);
    nouv->valeurNote = noteFinal;
    nouv->suiv = e->listeNote;
    printf(GREEN"Note enrgistree avec succes\n\n"RESET);
    return ;
}

//Aficher un etudiant 
void afficherProfilEtudiant(const Etudiant *listeGlobale, const char *matriculeRecherche) 
{
    // 1. On commence la recherche au début de la liste
    const Etudiant *tmp = listeGlobale;
    
    while (tmp != NULL) 
    {
        // 2. Si on trouve le matricule correspondant
        if (strcmp(tmp->matricule, matriculeRecherche) == 0) 
        {
            printf("\n==================================================\n");
            printf("                PROFIL DE L'ETUDIANT 🖼             \n");
            printf("==================================================\n");
            printf("  > Matricule   : %s\n", tmp->matricule);
            printf("  > Nom complet : %s %s\n", tmp->nom, tmp->prenom);
            printf("  > Age         : %d ans\n", tmp->age);
            printf("  > Orientation : [Faculte : %s] -> [Filiere : %s]\n", tmp->faculterChoisie, tmp->filiereChoisie);
            printf("--------------------------------------------------\n");
            printf("  > Resultats aux examens (QCM) :\n");
            
            // Parcours des notes de cet étudiant spécifique
            const Note *n = tmp->listeNote;
            if (n == NULL) 
            {
                printf("     └── Aucun examen passe pour le moment.\n");
            }
            while (n != NULL) 
            {
                printf("     └── [Cours: %s] : %.2f / 20\n", n->codeCours, n->valeurNote);
                n = n->suiv; // Note suivante
            }
            printf("==================================================\n");
            
            return; // On a trouvé et affiché, on quitte la fonction immédiatement
        }
        
        tmp = tmp->suiv; // Étudiant suivant dans la liste globale
    }

    // 3. Si on sort de la boucle sans avoir fait le "return", c'est que le matricule n'existe pas
    printf("\n[Erreur] Aucun etudiant avec le matricule '%s' n'a ete trouve.\n", matriculeRecherche);
}