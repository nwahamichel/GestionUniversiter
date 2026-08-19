#include "prototype.h"
Faculter *menuAdmin(Faculter *Universite,Etudiant *listeEtudiant, InfoUniversite *univ)
{
    int choixAdmin = 0;
    char codeFac[10],nomFac[50],nomFil[50];
    char codeCours[10],nomUE[50],prof[30],contenuCours[1000];
    char enonceQ[200],optA[100],optB[100],optC[100],optD[100],repQ;
    //Variable config
    char nom[100],sigle[20], adresse[150], telephone[30], email[50];
    do 
    {
        trace1();
        printf(MAGENTA"\n\t      ESPACE ADMINISTRATION 📚\n"RESET);
        trace1();
        printf(CYAN"1.Configurer les information de l'universiter\n"RESET);
        printf(CYAN"2. Ajouter une faculter\n"RESET);
        printf(CYAN"3. Ajouter une filiere dans une faculter\n"RESET);
        printf(CYAN"4. Ajouter une UE dans une filiere\n"RESET);
        printf(CYAN"5. Ajouter une / des question a un cours\n"RESET);
        printf(CYAN"6. Afficher la structure complete de l'universite\n"RESET);
        printf(CYAN"7. Voir les statistique de l'universiter\n"RESET);
        printf(CYAN"8. Suppression\n"RESET);
        printf(CYAN"0. Retour au menu principale\n"RESET);
        trace1();
        printf("Votre choix :");
        scanf("%d",&choixAdmin);
        getchar();
        switch(choixAdmin)
        {
            case 1:
                printf("\n=== CONFIGURATION DE L'UNIVERSITER ===\n");
                printf("Entrez le nom de l'universiter :");
                fgets(nom,sizeof (nom),stdin);
                nom[strcspn(nom, "\n")] = '\0';

                printf("Entrez le sigle (ex: UY1, UDs) :");
                fgets(sigle,sizeof (sigle),stdin);
                sigle[strcspn(sigle, "\n")] = '\0';

                printf("Entrez l'adresse :");
                fgets(adresse,sizeof (adresse),stdin);
                adresse[strcspn(adresse, "\n")] = '\0';

                printf("Entrez le numero de telephone :");
                fgets(telephone,sizeof (telephone),stdin);
                telephone[strcspn(telephone, "\n")] = '\0';

                printf("Entrez l'adresse email :");
                fgets(email,sizeof (email),stdin);
                email[strcspn(email, "\n")] = '\0';

                configurationInfoUni(univ,nom,sigle,adresse,telephone,email);
                 printf(GREEN"[+] Information de l'universiter enregistrees avec succes\n"RESET);
                break;
            case 2:
                printf("Entrer le code de la faculter (ex : FS) :");
                fgets(codeFac,sizeof(codeFac),stdin);
                codeFac[strcspn(codeFac,"\n")] = 0;

                printf("Entrer le nom de la faculter(ex:Faculter des science) :");
                fgets(nomFac,sizeof(nomFac),stdin);
                nomFac[strcspn(nomFac,"\n")] = 0;

                Universite = AjouterFac(Universite,codeFac,nomFac);
                break;
            case 3:
                printf("Code de la faculter cible :");
                fgets(codeFac,sizeof(codeFac),stdin);
                codeFac[strcspn(codeFac,"\n")] = 0;

                printf("Nom de la nouvelle filiere :");
                fgets(nomFil,sizeof(nomFil),stdin);
                nomFil[strcspn(nomFil,"\n")] = 0;

                Universite = ajouterFiliere(Universite,codeFac,nomFil);
                break;
            case 4:
                printf("code de la faculter :");
                fgets(codeFac,sizeof(codeFac),stdin);
                codeFac[strcspn(codeFac,"\n")] = 0;

                printf("Nom de la filiere :");
                fgets(nomFil,sizeof(nomFil),stdin);
                nomFil[strcspn(nomFil,"\n")] = 0;

                printf("Code du cours (ex:INF 122):");
                fgets(codeCours,sizeof(codeCours),stdin);
                codeCours[strcspn(codeCours,"\n")] = 0;

                printf("Nom de L'UE :");
                fgets(nomUE,sizeof(nomUE),stdin);
                nomUE[strcspn(nomUE,"\n")] = 0;

                printf("Nom de L'enseignant :");
                fgets(prof,sizeof(prof),stdin);
                prof[strcspn(prof,"\n")] = 0;

                printf("Contenu/chapitre : ");
                fgets(contenuCours,sizeof(contenuCours),stdin);
                contenuCours[strcspn(contenuCours,"\n")] = 0;

                ajouterCours(Universite,codeFac,nomFil,codeCours,nomUE,prof,contenuCours);
                break;
            case 5:
                printf("Code du cours :");
                fgets(codeCours,sizeof(codeCours),stdin);
                codeCours[strcspn(codeCours,"\n")] = 0;

                printf("Entrer l'enonce(question) :");
                fgets(enonceQ,sizeof(enonceQ),stdin);
                enonceQ[strcspn(enonceQ,"\n")] = 0;

                printf("Option A :");
                fgets(optA,sizeof(optA),stdin);
                optA[strcspn(optA,"\n")] = 0;

                printf("Option B :");
                fgets(optB,sizeof(optB),stdin);
                optB[strcspn(optB,"\n")] = 0;

                printf("Option C :");
                fgets(optC,sizeof(optC),stdin);
                optC[strcspn(optC,"\n")] = 0;

                printf("Option D :");
                fgets(optD,sizeof(optD),stdin);
                optD[strcspn(optD,"\n")] = 0;

                printf("Entrer la lettre de la bonne reponse :");
                scanf("%c",&repQ);
                getchar();

                ajouterQuestion(Universite,codeCours,enonceQ,optA,optB,optC,optD,repQ);
                break;
            case 6:
                aficherConfig(Universite);
                break;
            case 7:
                afficherStat(Universite,listeEtudiant);
                break;
            case 8:
                trace1();
                printf("            MENU DE SUPPRESSION\n");
                trace1();
                printf("1. Supprimer une faculter\n");
                printf("2. Supprimer une filiere\n");
                printf("3. Supprimer un cours\n");
                printf("0. Retour au menu principale\n");
                trace1();
                printf("Votre choix :");
                int choixSuppression;
                scanf("%d",&choixSuppression);
                getchar();
                switch(choixSuppression)
                {
                    case 1:
                        printf("Entrer le code de la faculter a supprimer :");
                        fgets(codeFac,sizeof(codeFac),stdin);
                        codeFac[strcspn(codeFac,"\n")] = 0;

                        Universite = supprimerFaculte(*univ,Universite,listeEtudiant,codeFac);
                        break;
                    case 2:
                        printf("Entrer le code de la faculter :");
                        fgets(codeFac,sizeof(codeFac),stdin);
                        codeFac[strcspn(codeFac,"\n")] = 0;

                        printf("Entrer le nom de la filiere a supprimer :");
                        fgets(nomFil,sizeof(nomFil),stdin);
                        nomFil[strcspn(nomFil,"\n")] = 0;

                        supprimerFiliere(*univ,Universite,listeEtudiant,codeFac,nomFil);
                        break;
                    case 3:
                        printf("Entrer le code du cours a supprimer :");
                        fgets(codeCours,sizeof(codeCours),stdin);
                        codeCours[strcspn(codeCours,"\n")] = 0;

                        supprimerCours(*univ,Universite,listeEtudiant,codeCours);
                        break;
                    case 0:
                        printf("Retour au menu principale \n");
                        break;
                    default:
                        printf(RED"Choix invallide\n"RESET);
                        break;
                }
                break;
            case 0:
                printf("Retour au menu principale \n");
                break;
            default:
                printf(RED"Choix invallide\n"RESET);
                break;
        }
    }while(choixAdmin != 0);
    return Universite;
}

//Espace Etudiant
Etudiant *menuEtudiant(Faculter *Universiter,Etudiant *liEtudiant)
{
    int choixEtudiant = 0;
    char mat[30],nomEtud[50],prenomEtud[30];
    int ageEtud;
    char nomFac[50],nomFil[50],codeCours[10];
    do
    {
        trace1();
        printf(YELLOW"\n\t     ESPACE ETUDIANT 📓\n"RESET);
        trace1();
        printf("1. S'inscrire(Nouvel Etudiant)\n");
        printf("2. Passer un examen\n");
        printf("3. Voir son profil et notes\n");
        printf("0. Retour au menu principale\n");
        trace1();
        printf("Votre choix :");
        scanf("%d",&choixEtudiant);
        getchar();
        switch(choixEtudiant)
        {
            case 0:
                printf("Retour au menu principale\n");
                break;
            case 1:
                printf("Entrer le matricule :");
                fgets(mat,sizeof(mat),stdin);
                mat[strcspn(mat,"\n")] = 0;

                printf("Entrer le nom :");
                fgets(nomEtud,sizeof(nomEtud),stdin);
                nomEtud[strcspn(nomEtud,"\n")] = 0;

                printf("Entrer le prenom :");
                fgets(prenomEtud,sizeof(prenomEtud),stdin);
                prenomEtud[strcspn(prenomEtud,"\n")] = 0;

                printf("Entrer l'age :");
                scanf("%d",&ageEtud);
                getchar();

                Faculter *fct = Universiter;
                if(fct == NULL)
                {
                    printf(RED"Aucune faculter disponible\n"RESET);
                    return liEtudiant;
                }
                int p = 1;
                trace2();
                printf("\n");
                printf("             Liste des faculter disponible\n");
                trace2();
                while(fct != NULL)
                {
                    printf("%d. %s\n",p,fct->nomFaculter);
                    p ++;
                    fct = fct->suiv;
                }
                trace2();
                printf("Entre le nom de la faculter choisie(ex:Faculter des science) :");
                fgets(nomFac,sizeof(nomFac),stdin);
                nomFac[strcspn(nomFac,"\n")] = 0;

                //teste si la faculter existe
                Faculter *f = Universiter;
                while(f != NULL && strcmp(f->nomFaculter ,nomFac) !=0)
                {
                    f = f->suiv;
                }   
                if(f == NULL)
                {
                    printf(RED"La faculter [%s] n'existe pas \n"RESET,nomFac);
                    return liEtudiant;
                }
                
                trace2();
                printf("\n");
                printf("          Liste des filiere de la %s\n",f->nomFaculter);
                trace2();
                Filiere *fl = f->listeFiliere;
                int n = 1;
                
                while(fl != NULL)
                {
                    printf("%d. %s\n",n,fl->nomFilier);
                    n ++;
                    fl = fl->suiv;
                }
                trace2();

                printf("Entrer le nom de la filiere :");
                fgets(nomFil,sizeof(nomFil),stdin);
                nomFil[strcspn(nomFil,"\n")] = 0;

                //tester si la filiere existe
                 Filiere *fi = f->listeFiliere;
                while(fi != NULL && strcmp(fi->nomFilier,nomFil) != 0)
                {
                    fi = fi->suiv;
                }
                if(fi == NULL)
                {
                    printf(RED"La filiere [%s] n'existe pas dans la faculter [%s] !\n"RESET,nomFil,f->nomFaculter);
                    return liEtudiant;
                }

                liEtudiant = AjouterEtudiant(liEtudiant,mat,nomEtud,prenomEtud,ageEtud,nomFac,nomFil);
                break;
            case 2:
                printf("Entrez votre matricule :");
                fgets(mat,sizeof(mat),stdin);
                mat[strcspn(mat,"\n")] = 0;

                printf("Entrez le code du cours (ex:INF 111):");
                fgets(codeCours,sizeof(codeCours),stdin);
                codeCours[strcspn(codeCours,"\n")] = 0;

                passerQcm(liEtudiant,Universiter,mat,codeCours);
                break;
            case 3:
                printf("Entrez le matricule :");
                fgets(mat,sizeof(mat),stdin);
                mat[strcspn(mat,"\n")] = 0;

                afficherProfilEtudiant(liEtudiant,mat);
                break;
            default:
                printf(RED"Choix invallide\n"RESET);
                break;
        }
    } while (choixEtudiant != 0);
   return liEtudiant; 
}

//trace 1
void trace1()
{
    printf(BLUE"================================================================\n"RESET);
}

//trace 2
void trace2()
{
    printf(GREEN"-----------------------------------------------------------------\n"RESET);
}