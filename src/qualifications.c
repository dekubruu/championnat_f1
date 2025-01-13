#include <stdio.h>
#include <stdlib.h>
#include "qualifications.h"
#include "voiture.h"
#include "session.h"  // Pour sauvegarder les résultats et afficher les meilleurs temps

extern void generer_temps(Voiture *voiture);  // Déclaration de la fonction generer_temps
extern int comparer_voitures(const void *a, const void *b);  // Déclaration de comparer_voitures

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
    sauvegarder_resultats(voitures, nombre_voitures, "qualification_finale");

    // Afficher les meilleurs temps par secteur et le meilleur tour
    afficherMeilleursTemps(voitures, nombre_voitures);

    printf("\n=== Fin des qualifications ===\n");
}

void lancerQualifications(Voiture *pilotes, int nombre_pilotes) {
    printf("\n=== Début des qualifications ===\n");
    simuler_qualification(pilotes, nombre_pilotes);
    printf("\n=== Fin des qualifications ===\n");
}
