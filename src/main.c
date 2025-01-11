#include <stdio.h>
#include "voiture.h"
#include "session.h"

int main() {
    int numeros_voitures[] = {1, 11, 44, 63, 16, 55, 4, 81, 14, 18, 10, 31, 23, 2, 22, 3, 77, 24, 20, 27};
    int nombre_voitures = 20;
    Voiture voitures[nombre_voitures];

    // Initialisation des voitures
    for (int i = 0; i < nombre_voitures; i++) {
        initialiser_voiture(&voitures[i], numeros_voitures[i]);
    }

    // Simulation de la session d'essais (5 tours)
    printf("Début de la séance d'essais...\n");
    for (int tour = 0; tour < 5; tour++) {
        printf("Tour %d :\n", tour + 1);
        for (int i = 0; i < nombre_voitures; i++) {
            generer_temps(&voitures[i]);
            printf("Voiture %d : %.2f s\n", voitures[i].numero, voitures[i].meilleur_temps);
        }
        printf("\n");
    }

    // Sauvegarde des résultats des essais
    sauvegarder_resultats(voitures, nombre_voitures, "essais_libres_P1");

    // Simulation des qualifications
    simuler_qualification(voitures, nombre_voitures);

    // Simulation de la course principale (50 tours)
    simuler_course(voitures, 10, 50);


    return 0;
}
