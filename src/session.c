#include <stdio.h>
#include <stdlib.h>
#include "session.h"
#include "voiture.h"

int comparer_voitures(const void *a, const void *b) {
    Voiture *voitureA = (Voiture *)a;
    Voiture *voitureB = (Voiture *)b;
    return (voitureA->meilleur_temps > voitureB->meilleur_temps) - (voitureA->meilleur_temps < voitureB->meilleur_temps);
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
    for (int i = 0; i < nombre_voitures; i++) {
        fprintf(fichier, "Position %d : Voiture %d, Temps : %.2f s\n",
                i + 1, voitures[i].numero, voitures[i].meilleur_temps);
    }

    fclose(fichier);
    printf("Résultats sauvegardés dans %s\n", nom_fichier);
}

void afficherMeilleursTemps(Voiture *voitures, int nombre_voitures) {
    float meilleurS1 = 9999.0, meilleurS2 = 9999.0, meilleurS3 = 9999.0, meilleurTour = 9999.0;
    int voitureS1 = -1, voitureS2 = -1, voitureS3 = -1, voitureTour = -1;

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
        if (voitures[i].meilleur_temps < meilleurTour) {
            meilleurTour = voitures[i].meilleur_temps;
            voitureTour = voitures[i].numero;
        }
    }

    printf("\n=== Meilleurs temps ===\n");
    printf("Meilleur tour : Voiture %d, Temps : %.2f s\n", voitureTour, meilleurTour);
    printf("Secteur 1 : Voiture %d, Temps : %.2f s\n", voitureS1, meilleurS1);
    printf("Secteur 2 : Voiture %d, Temps : %.2f s\n", voitureS2, meilleurS2);
    printf("Secteur 3 : Voiture %d, Temps : %.2f s\n", voitureS3, meilleurS3);
}
