/* session.c : Mise à jour pour gestion des essais conformément aux exigences */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "session.h"
#include "voiture.h"

// Fonction de comparaison pour qsort
int comparer_voitures(const void *a, const void *b) {
    Voiture *voitureA = (Voiture *)a;
    Voiture *voitureB = (Voiture *)b;
    if (voitureA->meilleur_temps < voitureB->meilleur_temps) {
        return -1;
    } else if (voitureA->meilleur_temps > voitureB->meilleur_temps) {
        return 1;
    } else {
        return 0;
    }
}

void sauvegarder_resultats(Voiture *voitures, int nombre_voitures, const char *nom_session) {
    char nom_fichier[50];
    sprintf(nom_fichier, "data/resultats_%s.txt", nom_session);

    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de la création du fichier %s\n", nom_fichier);
        return;
    }

    fprintf(fichier, "Résultats de la session %s :\n\n", nom_session);

    // Trier les voitures ayant terminé la course par leur meilleur temps
    qsort(voitures, nombre_voitures, sizeof(Voiture), comparer_voitures);

    // Sauvegarder les résultats triés des voitures ayant terminé
    fprintf(fichier, "Voitures ayant terminé la course (classées) :\n");
    for (int i = 0; i < nombre_voitures; i++) {
        fprintf(fichier, "Position %d : Voiture %d, Temps : %.2f s (S1: %.2f, S2: %.2f, S3: %.2f)\n",
                i + 1, voitures[i].numero, voitures[i].meilleur_temps,
                voitures[i].secteurs[0], voitures[i].secteurs[1], voitures[i].secteurs[2]);
    }

    // Déterminer et afficher les meilleurs temps par secteur et le meilleur tour global
    float meilleurS1 = 9999.0, meilleurS2 = 9999.0, meilleurS3 = 9999.0, meilleurTour = 9999.0;
    for (int i = 0; i < nombre_voitures; i++) {
        if (voitures[i].secteurs[0] < meilleurS1) {
            meilleurS1 = voitures[i].secteurs[0];
        }
        if (voitures[i].secteurs[1] < meilleurS2) {
            meilleurS2 = voitures[i].secteurs[1];
        }
        if (voitures[i].secteurs[2] < meilleurS3) {
            meilleurS3 = voitures[i].secteurs[2];
        }
        if (voitures[i].meilleur_temps < meilleurTour) {
            meilleurTour = voitures[i].meilleur_temps;
        }
    }

    fprintf(fichier, "\nMeilleurs temps par secteur :\n");
    fprintf(fichier, "S1 : %.2f s\n", meilleurS1);
    fprintf(fichier, "S2 : %.2f s\n", meilleurS2);
    fprintf(fichier, "S3 : %.2f s\n", meilleurS3);
    fprintf(fichier, "Meilleur tour : %.2f s\n", meilleurTour);

    fclose(fichier);
    printf("Résultats sauvegardés dans %s\n", nom_fichier);
}

void lancerEssais(Voiture *pilotes, int nombre_pilotes, const char *nom_session) {
    printf("\n=== Début des essais %s ===\n", nom_session);

    int nombre_tours = 5;  // Chaque voiture effectue 5 tours
    float meilleur_temps_global = 9999.0;  // Meilleur temps global de la séance

    // Tableau pour stocker les meilleurs temps par secteur
    float meilleurs_secteurs[3] = {9999.0, 9999.0, 9999.0};

    // Simulation des tours
    for (int tour = 1; tour <= nombre_tours; tour++) {
        printf("\n--- Tour %d ---\n", tour);
        for (int i = 0; i < nombre_pilotes; i++) {
            float temps_total = 0.0;

            // Générer les temps des 3 secteurs
            for (int secteur = 0; secteur < 3; secteur++) {
                float temps_secteur = (float)(rand() % 21 + 25);  // Temps entre 25 et 45 secondes
                pilotes[i].secteurs[secteur] = temps_secteur;
                temps_total += temps_secteur;

                // Mettre à jour le meilleur temps du secteur
                if (temps_secteur < meilleurs_secteurs[secteur]) {
                    meilleurs_secteurs[secteur] = temps_secteur;
                }
            }

            // Mettre à jour le meilleur temps de la voiture
            if (temps_total < pilotes[i].meilleur_temps) {
                pilotes[i].meilleur_temps = temps_total;
            }

            printf("Voiture %d : %.2f s (S1: %.2f, S2: %.2f, S3: %.2f)\n",
                   pilotes[i].numero, temps_total, pilotes[i].secteurs[0],
                   pilotes[i].secteurs[1], pilotes[i].secteurs[2]);

            // Mettre à jour le meilleur temps global
            if (temps_total < meilleur_temps_global) {
                meilleur_temps_global = temps_total;
            }
        }
    }

    // Trier les voitures par leur meilleur temps
    qsort(pilotes, nombre_pilotes, sizeof(Voiture), comparer_voitures);

    // Afficher les résultats finaux avec les différences de temps
    printf("\n--- Résultats finaux des essais %s ---\n", nom_session);
    for (int i = 0; i < nombre_pilotes; i++) {
        if (i == 0) {
            printf("Position %d : Voiture %d, Temps : %.2f s\n", i + 1, pilotes[i].numero, pilotes[i].meilleur_temps);
        } else {
            printf("Position %d : Voiture %d, Temps : %.2f s (+%.2f s)\n",
                   i + 1, pilotes[i].numero, pilotes[i].meilleur_temps,
                   pilotes[i].meilleur_temps - pilotes[0].meilleur_temps);
        }
    }

    // Afficher les meilleurs temps par secteur
    afficherMeilleursTempsParSecteur(pilotes, nombre_pilotes);

    // Sauvegarder les résultats dans un fichier
    sauvegarder_resultats(pilotes, nombre_pilotes, nom_session);


    printf("\n=== Fin des essais %s ===\n", nom_session);
}

void lancerEssaisP1(Voiture *pilotes, int nombre_pilotes) {
    lancerEssais(pilotes, nombre_pilotes, "essais_libres_P1");
}

void lancerEssaisP2(Voiture *pilotes, int nombre_pilotes) {
    lancerEssais(pilotes, nombre_pilotes, "essais_libres_P2");
}

void lancerEssaisP3(Voiture *pilotes, int nombre_pilotes) {
    lancerEssais(pilotes, nombre_pilotes, "essais_libres_P3");
}

void simuler_qualification(Voiture *voitures, int nombre_voitures) {
    int voitures_restantes = nombre_voitures;
    int phase = 1;

    while (voitures_restantes > 10) {
        printf("\n=== Début de la phase Q%d ===\n", phase);

        // Simulation de plusieurs tours pour cette phase
        for (int tour = 0; tour < 5; tour++) {
            printf("\n--- Tour %d ---\n", tour + 1);
            for (int i = 0; i < voitures_restantes; i++) {
                generer_temps(&voitures[i]);
                printf("Voiture %d : %.2f s\n", voitures[i].numero, voitures[i].meilleur_temps);
            }
        }

        // Trier les voitures par leur meilleur temps
        qsort(voitures, voitures_restantes, sizeof(Voiture), comparer_voitures);

        // Afficher les résultats de la phase
        printf("\n--- Résultats de la phase Q%d ---\n", phase);
        for (int i = 0; i < voitures_restantes; i++) {
            printf("Position %d : Voiture %d, Temps : %.2f s\n",
                   i + 1, voitures[i].numero, voitures[i].meilleur_temps);
        }

        // Éliminer les 5 voitures les plus lentes
        printf("\nVoitures éliminées après la phase Q%d :\n", phase);
        for (int i = voitures_restantes - 5; i < voitures_restantes; i++) {
            printf("Voiture %d : %.2f s\n", voitures[i].numero, voitures[i].meilleur_temps);
        }

        voitures_restantes -= 5;
        phase++;
    }

    // Sauvegarder les résultats finaux de Q3
    sauvegarder_resultats(voitures, 10, "qualification_finale");

    printf("\n=== Fin des qualifications ===\n");
}

void simuler_course(Voiture *voitures, int nombre_voitures, int nombre_tours) {
    printf("\n=== Début de la course principale ===\n");
    for (int tour = 1; tour <= nombre_tours; tour++) {
        printf("\n--- Tour %d ---\n", tour);
        for (int i = 0; i < nombre_voitures; i++) {
            generer_temps(&voitures[i]);
            printf("Voiture %d : %.2f s\n", voitures[i].numero, voitures[i].meilleur_temps);
        }
    }

    qsort(voitures, nombre_voitures, sizeof(Voiture), comparer_voitures);
    sauvegarder_resultats(voitures, nombre_voitures, "course_principale");
    printf("\n=== Fin de la course principale ===\n");
}

void lancerQualifications(Voiture *pilotes, int nombre_pilotes) {
    printf("\n=== Début des qualifications ===\n");
    simuler_qualification(pilotes, nombre_pilotes);
    printf("\n=== Fin des qualifications ===\n");
}

void lancerCourse(Voiture *pilotes, int nombre_pilotes) {
    int nombre_tours = 10;  // Exemple : course sur 10 tours
    simuler_course(pilotes, nombre_pilotes, nombre_tours);
}

void initialiserPilotes(Voiture *pilotes, int nombre_pilotes) {
    // Liste fixe des numéros de voitures
    int numeros_fixes[20] = {1, 11, 44, 63, 16, 55, 4, 81, 14, 18, 10, 31, 23, 2, 22, 3, 77, 24, 20, 27};

    for (int i = 0; i < nombre_pilotes; i++) {
        pilotes[i].numero = numeros_fixes[i];
        pilotes[i].meilleur_temps = 9999.0;  // Un temps élevé pour commencer
        pilotes[i].status = 'R';             // La voiture roule au départ
        pilotes[i].points = 0;               // Initialisation des points à zéro

        // Initialisation des secteurs à zéro
        for (int j = 0; j < 3; j++) {
            pilotes[i].secteurs[j] = 0.0;
        }

        sprintf(pilotes[i].prenom, "Prenom%d", i + 1);
        sprintf(pilotes[i].nom, "Nom%d", i + 1);
    }
}

void afficherMeilleursTempsParSecteur(Voiture *voitures, int nombre_voitures) {
    float meilleurS1 = 9999.0, meilleurS2 = 9999.0, meilleurS3 = 9999.0;
    int voitureS1 = -1, voitureS2 = -1, voitureS3 = -1;

    for (int i = 0; i < nombre_voitures; i++) {
        if (voitures[i].secteurs[0] < meilleurS1) {
            meilleurS1 = voitures[i].secteurs[0];
            voitureS1 = voitures[i].numero;
        }
        if (voitures[i].secteurs[1] < meilleurS2) {
            meilleurS2 = voitures[i].secteurs[1];
            voitureS2 = voitures[i].numero;
        }
        if (voitures[i].secteurs[2] < meilleurS3) {
            meilleurS3 = voitures[i].secteurs[2];
            voitureS3 = voitures[i].numero;
        }
    }

    printf("\nMeilleurs temps par secteur :\n");
    printf("S1 : %.2f s (Voiture %d)\n", meilleurS1, voitureS1);
    printf("S2 : %.2f s (Voiture %d)\n", meilleurS2, voitureS2);
    printf("S3 : %.2f s (Voiture %d)\n", meilleurS3, voitureS3);
}
