#include <stdio.h>
#include <stdlib.h>
#include "course.h"
#include "voiture.h"
#include "session.h"  // Pour sauvegarder les résultats


extern void generer_temps(Voiture *voiture);  // Déclaration de la fonction generer_temps
extern int comparer_voitures(const void *a, const void *b);  // Déclaration de comparer_voitures


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

void lancerCourse(Voiture *pilotes, int nombre_pilotes) {
    int nombre_tours = 10;  // Exemple : course sur 10 tours
    simuler_course(pilotes, nombre_pilotes, nombre_tours);
}
