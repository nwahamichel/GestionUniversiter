#include "prototype.h"
int main() 
{
    
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Faculter *maUniversite = NULL;
    Etudiant *listeEtudiants = NULL;
    InfoUniversite univ ;

    int choixPrincipal = 0;
    char motDePasse[20];

    printf(BLUE"\nChargement des donnees de l'universite en cours...\n"RESET);
    maUniversite = chargerDonnees(&univ,&maUniversite, &listeEtudiants, "sauvegarde.json");

    // MESSAGE DE BIENVENUE A TOUT LE MONDE
    printf("\n");
    printf(GREEN"  \n 👨‍👩‍👧 BIENVENUE (WELCOME) a tous et toutes dans 'MIN-NOIRES UNIVERSITY (MIN-UNI)'\n"RESET);
    printf(CYAN"  Que vous soyez Enseignant ou Etudiant,         \n"RESET);
    printf(CYAN"  nous vous souhaitons une excellente session de travail !       \n"RESET);
    printf("\n");

    do {
        trace1();
        printf(YELLOW"\n               🏠 ACCUEIL PRINCIPAL                \n"RESET);
        trace1();
        printf(GREEN BOLD" 1. Se connecter a l'Espace Administration 👤\n"RESET);
        printf(GREEN BOLD" 2. Acceder a l'Espace Etudiant 👥\n"RESET);
        printf(GREEN BOLD" 3. Quitter l'application ❌\n"RESET);
        trace1();
        printf("Votre choix : ");
        
        if (scanf("%d", &choixPrincipal) != 1) {
            choixPrincipal = 0;
        }
        
        // Nettoyage robuste du tampon de saisie (consomme tout jusqu'au '\n')
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choixPrincipal) {
            case 1:
                printf("\nSaisir le code secret d'acces : ");
                fgets(motDePasse, sizeof(motDePasse), stdin);
                motDePasse[strcspn(motDePasse, "\n")] = 0; // Enlever le \n

                if (strcmp(motDePasse, "admin123") == 0) {
                    // Passage par adresse (&) pour que le menu puisse modifier les deux listes
                    printf(BLUE"Bienvenue \\ Welcome NWAHA-MICHEL-TRESOR 😊\n"RESET);
                    maUniversite = menuAdmin(maUniversite, listeEtudiants, &univ);
                } else {
                    printf(RED"\n[Erreur] Code secret incorrect ! Acces refuse. ❌\n"RESET);
                }
                break;

            case 2:
                // Passage par adresse (&) également ici pour la cohérence et la sécurité
                listeEtudiants = menuEtudiant(maUniversite,listeEtudiants);
                break;

            case 3:
                printf("\nSauvegarde des donnees en cours...\n");
                // Sauvegarde automatique lors de la fermeture
                sauvegarderDonnees(univ,maUniversite, listeEtudiants, "sauvegarde.json");
                printf("Au revoir !\n");
                break;
            default:
                printf(RED"\nChoix indisponible ⁉. Veuillez selectionner 1, 2 ou 3.\n"RESET);
                break;
        }
    } while (choixPrincipal != 3);
    return 0;
}