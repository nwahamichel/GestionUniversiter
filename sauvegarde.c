#include "prototype.h"

void sauvegarderDonnees(InfoUniversite info,Faculter *universite, Etudiant *listeEtudiants, const char *nomFichier) {
    cJSON *racine = cJSON_CreateObject();
    
    // 1. SAUVEGARDE DES INFORMATIONS GÉNÉRALES
    cJSON *objInfo = cJSON_CreateObject();
    cJSON_AddStringToObject(objInfo, "nom", info.nom);
    cJSON_AddStringToObject(objInfo, "sigle", info.sigle);
    cJSON_AddStringToObject(objInfo, "adresse", info.adresse);
    cJSON_AddStringToObject(objInfo, "telephone", info.telephone);
    cJSON_AddStringToObject(objInfo, "email", info.email);

    cJSON_AddItemToObject(racine, "infos_generales", objInfo);

    // --- A. SAUVEGARDE DES FACULTÉS ---
    cJSON *arrayFacultes = cJSON_CreateArray();
    Faculter *f = universite;
    
    while (f != NULL) {
        cJSON *objFac = cJSON_CreateObject();
        cJSON_AddStringToObject(objFac, "codeFaculter", f->codeFaculter); // Assurez-vous des noms de champs dans vos structures
        cJSON_AddStringToObject(objFac, "nomFaculter", f->nomFaculter);
        
        // Filières
        cJSON *arrayFilieres = cJSON_CreateArray();
        Filiere *fi = f->listeFiliere;
        while (fi != NULL) {
            cJSON *objFil = cJSON_CreateObject();
            cJSON_AddStringToObject(objFil, "nomFiliere", fi->nomFilier);
            
            // Cours / UEs
            cJSON *arrayCours = cJSON_CreateArray();
            Cours *c = fi->listeCours;
            while (c != NULL) {
                cJSON *objCours = cJSON_CreateObject();
                cJSON_AddStringToObject(objCours, "codeCours", c->code);
                cJSON_AddStringToObject(objCours, "nomUE", c->nomUE);
                cJSON_AddStringToObject(objCours, "enseignant", c->nomEnseignant);
                cJSON_AddStringToObject(objCours, "contenuCours", c->contenu);
                
                // Questions / QCM
                cJSON *arrayQ = cJSON_CreateArray();
                Question *q = c->listeQuestion;
                while (q != NULL) {
                    cJSON *objQ = cJSON_CreateObject();
                    cJSON_AddStringToObject(objQ, "enonce", q->enonce);
                    cJSON_AddStringToObject(objQ, "optA", q->optA);
                    cJSON_AddStringToObject(objQ, "optB", q->optB);
                    cJSON_AddStringToObject(objQ, "optC", q->optC);
                    cJSON_AddStringToObject(objQ, "optD", q->optD);
                    
                    char repStr[2] = {q->bonneRep, '\0'};
                    cJSON_AddStringToObject(objQ, "reponseCorrecte", repStr);
                    
                    cJSON_AddItemToArray(arrayQ, objQ);
                    q = q->suiv;
                }
                cJSON_AddItemToObject(objCours, "questions", arrayQ);
                cJSON_AddItemToArray(arrayCours, objCours);
                c = c->suiv;
            }
            cJSON_AddItemToObject(objFil, "cours", arrayCours);
            cJSON_AddItemToArray(arrayFilieres, objFil);
            fi = fi->suiv;
        }
        cJSON_AddItemToObject(objFac, "filieres", arrayFilieres);
        cJSON_AddItemToArray(arrayFacultes, objFac);
        f = f->suiv;
    }
    cJSON_AddItemToObject(racine, "facultes", arrayFacultes);

    // --- B. SAUVEGARDE DES ÉTUDIANTS ---
    cJSON *arrayEtudiants = cJSON_CreateArray();
    Etudiant *e = listeEtudiants;
    
    while (e != NULL) {
        cJSON *objEtu = cJSON_CreateObject();
        cJSON_AddStringToObject(objEtu, "matricule", e->matricule);
        cJSON_AddStringToObject(objEtu, "nom", e->nom);
        cJSON_AddStringToObject(objEtu, "prenom", e->prenom);
        cJSON_AddNumberToObject(objEtu, "age", e->age);
        cJSON_AddStringToObject(objEtu, "faculter", e->faculterChoisie);
        cJSON_AddStringToObject(objEtu, "filiere", e->filiereChoisie);

        // Notes
        cJSON *arrayNotes = cJSON_CreateArray();
        Note *n = e->listeNote;
        while (n != NULL) {
            cJSON *objNote = cJSON_CreateObject();
            cJSON_AddStringToObject(objNote, "codeCours", n->codeCours);
            cJSON_AddNumberToObject(objNote, "note", n->valeurNote);
            cJSON_AddItemToArray(arrayNotes, objNote);
            n = n->suiv;
        }
        cJSON_AddItemToObject(objEtu, "notes", arrayNotes);
        cJSON_AddItemToArray(arrayEtudiants, objEtu);
        e = e->suiv;
    }
    cJSON_AddItemToObject(racine, "etudiants", arrayEtudiants);

    // --- C. ÉCRITURE DANS LE FICHIER ---
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier != NULL) {
        char *jsonTexte = cJSON_Print(racine); // Formatage lisible
        fputs(jsonTexte, fichier);
        fclose(fichier);
        free(jsonTexte);
        printf(GREEN "\nDonnees sauvegardees avec succes dans %s !\n" RESET, nomFichier);
    } else {
        printf(RED "\nErreur lors de l'ouverture du fichier de sauvegarde.\n" RESET);
    }

    cJSON_Delete(racine);
}

// ==========================================
// 2. CHARGER LES DONNÉES DEPUIS LE JSON
// ==========================================
Faculter* chargerDonnees(InfoUniversite *info,Faculter **universite, Etudiant **listeEtudiants, const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (!fichier) {
        printf(YELLOW "\nAucun fichier de sauvegarde trouve (%s). Demarrage a vide.\n" RESET, nomFichier);
        return NULL;
    }

    // Lire tout le contenu du fichier JSON
    fseek(fichier, 0, SEEK_END);
    long longueur = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);
    
    char *tampon = (char *)malloc(longueur + 1);
    fread(tampon, 1, longueur, fichier);
    tampon[longueur] = '\0';
    fclose(fichier);

    cJSON *racine = cJSON_Parse(tampon);
    free(tampon);

    if (!racine) {
        printf(RED "\nErreur de lecture du fichier JSON !\n" RESET);
        return NULL;
    }

    // 1. LECTURE DES INFORMATIONS GÉNÉRALES
    cJSON *objInfo = cJSON_GetObjectItemCaseSensitive(racine, "infos_generales");
    if (objInfo != NULL) {
        cJSON *nom = cJSON_GetObjectItemCaseSensitive(objInfo, "nom");
        cJSON *sigle = cJSON_GetObjectItemCaseSensitive(objInfo, "sigle");
        cJSON *adresse = cJSON_GetObjectItemCaseSensitive(objInfo, "adresse");
        cJSON *tel = cJSON_GetObjectItemCaseSensitive(objInfo, "telephone");
        cJSON *email = cJSON_GetObjectItemCaseSensitive(objInfo, "email");

        if (nom && nom->valuestring) strcpy(info->nom, nom->valuestring);
        if (sigle && sigle->valuestring) strcpy(info->sigle, sigle->valuestring);
        if (adresse && adresse->valuestring) strcpy(info->adresse, adresse->valuestring);
        if (tel && tel->valuestring) strcpy(info->telephone, tel->valuestring);
        if (email && email->valuestring) strcpy(info->email, email->valuestring);
    }

    // --- CHARGER FACULTÉS ---
    cJSON *facultes = cJSON_GetObjectItemCaseSensitive(racine, "facultes");
    cJSON *fac = NULL;
    cJSON_ArrayForEach(fac, facultes) {
        cJSON *codeFac = cJSON_GetObjectItemCaseSensitive(fac, "codeFaculter");
        cJSON *nomFac = cJSON_GetObjectItemCaseSensitive(fac, "nomFaculter");

        *universite = AjouterFac(*universite, codeFac->valuestring, nomFac->valuestring);

        // Filières
        cJSON *filieres = cJSON_GetObjectItemCaseSensitive(fac, "filieres");
        cJSON *fil = NULL;
        cJSON_ArrayForEach(fil, filieres) {
            cJSON *nomFil = cJSON_GetObjectItemCaseSensitive(fil, "nomFiliere");
            *universite = ajouterFiliere(*universite, codeFac->valuestring, nomFil->valuestring);

            // Cours
            cJSON *coursList = cJSON_GetObjectItemCaseSensitive(fil, "cours");
            cJSON *crs = NULL;
            cJSON_ArrayForEach(crs, coursList) {
                cJSON *codeC = cJSON_GetObjectItemCaseSensitive(crs, "codeCours");
                cJSON *nomUE = cJSON_GetObjectItemCaseSensitive(crs, "nomUE");
                cJSON *prof = cJSON_GetObjectItemCaseSensitive(crs, "enseignant");
                cJSON *contenu = cJSON_GetObjectItemCaseSensitive(crs, "contenuCours");

                ajouterCours(*universite, codeFac->valuestring, nomFil->valuestring,
                             codeC->valuestring, nomUE->valuestring, prof->valuestring, contenu->valuestring);

                // Questions
                cJSON *questions = cJSON_GetObjectItemCaseSensitive(crs, "questions");
                cJSON *q = NULL;
                cJSON_ArrayForEach(q, questions) {
                    cJSON *enonce = cJSON_GetObjectItemCaseSensitive(q, "enonce");
                    cJSON *optA = cJSON_GetObjectItemCaseSensitive(q, "optA");
                    cJSON *optB = cJSON_GetObjectItemCaseSensitive(q, "optB");
                    cJSON *optC = cJSON_GetObjectItemCaseSensitive(q, "optC");
                    cJSON *optD = cJSON_GetObjectItemCaseSensitive(q, "optD");
                    cJSON *rep = cJSON_GetObjectItemCaseSensitive(q, "reponseCorrecte");

                    ajouterQuestion(*universite, codeC->valuestring, enonce->valuestring,
                                    optA->valuestring, optB->valuestring, optC->valuestring,
                                    optD->valuestring, rep->valuestring[0]);
                }
            }
        }
    }
   


    // --- CHARGER ÉTUDIANTS ---
    cJSON *etudiants = cJSON_GetObjectItemCaseSensitive(racine, "etudiants");
    cJSON *etu = NULL;
    cJSON_ArrayForEach(etu, etudiants) {
        cJSON *mat = cJSON_GetObjectItemCaseSensitive(etu, "matricule");
        cJSON *nom = cJSON_GetObjectItemCaseSensitive(etu, "nom");
        cJSON *prenom = cJSON_GetObjectItemCaseSensitive(etu, "prenom");
        cJSON *age = cJSON_GetObjectItemCaseSensitive(etu, "age");
        cJSON *nomFac = cJSON_GetObjectItemCaseSensitive(etu, "faculter");
        cJSON *nomFil = cJSON_GetObjectItemCaseSensitive(etu, "filiere");

        *listeEtudiants = AjouterEtudiant(*listeEtudiants,mat->valuestring,
                                         nom->valuestring, prenom->valuestring,
                                         age->valueint, nomFac->valuestring,nomFil->valuestring);
    }

    cJSON_Delete(racine);
    printf(GREEN "\nSauvegarde chargee avec succes !\n" RESET);
    return *universite;
}