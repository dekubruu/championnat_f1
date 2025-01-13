#include <stdio.h>
#include <stdlib.h>
#include "essais.h"
#include "voiture.h"
#include "session.h"  // Pour sauvegarder les résultats et afficher les meilleurs temps

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

    // Sauvegarder les résultats dans un fichier
    sauvegarder_resultats(pilotes, nombre_pilotes, nom_session);

    // Afficher les meilleurs temps par secteur et le tour le plus rapide
    afficherMeilleursTemps(pilotes, nombre_pilotes);

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
