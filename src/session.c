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
        fprintf(fichier, "Position %d : Voiture %d, Temps : %.2f s\n",
                i + 1, voitures[i].numero, voitures[i].meilleur_temps);
    }

    fclose(fichier);
    printf("Résultats sauvegardés dans %s\n", nom_fichier);
}

void lancerEssais(Voiture *pilotes, int nombre_pilotes, const char *nom_session) {
    printf("\n=== Début des essais %s ===\n", nom_session);

    // Simulation de plusieurs tours pour les essais
    for (int tour = 0; tour < 5; tour++) {
        printf("\n--- Tour %d ---\n", tour + 1);
        for (int i = 0; i < nombre_pilotes; i++) {
            generer_temps(&pilotes[i]);
            printf("Voiture %d : %.2f s\n", pilotes[i].numero, pilotes[i].meilleur_temps);
        }
    }

    // Trier les voitures par leur meilleur temps
    qsort(pilotes, nombre_pilotes, sizeof(Voiture), comparer_voitures);

    // Afficher les résultats des essais avec différences de temps
    printf("\n--- Résultats des essais %s ---\n", nom_session);
    for (int i = 0; i < nombre_pilotes; i++) {
        if (i == 0) {
            printf("Position %d : Voiture %d, Temps : %.2f s\n", i + 1, pilotes[i].numero, pilotes[i].meilleur_temps);
        } else {
            printf("Position %d : Voiture %d, Temps : %.2f s (+%.2f s)\n",
                   i + 1, pilotes[i].numero, pilotes[i].meilleur_temps,
                   pilotes[i].meilleur_temps - pilotes[i - 1].meilleur_temps);
        }
    }

    // Sauvegarder les résultats finaux dans un fichier
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
    for (int i = 0; i < nombre_pilotes; i++) {
        pilotes[i].numero = i + 1;
        pilotes[i].meilleur_temps = 9999.0;  // Temps élevé pour commencer
        pilotes[i].status = 'R';             // La voiture roule au départ
        pilotes[i].points = 0;               // Points initialisés à zéro

        // Initialisation des secteurs à zéro
        for (int j = 0; j < 3; j++) {
            pilotes[i].secteurs[j] = 0.0;
        }

        sprintf(pilotes[i].prenom, "Prenom%d", i + 1);
        sprintf(pilotes[i].nom, "Nom%d", i + 1);
    }
}

