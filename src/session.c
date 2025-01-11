#include <stdio.h>
#include <stdlib.h>
#include "session.h"


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
    Voiture voitures_terminees[nombre_voitures];
    int compteur_terminees = 0;

    for (int i = 0; i < nombre_voitures; i++) {
        if (voitures[i].status != 'O') { // Si la voiture n'a pas abandonné
            voitures_terminees[compteur_terminees++] = voitures[i];
        }
    }

    qsort(voitures_terminees, compteur_terminees, sizeof(Voiture), comparer_voitures);

    // Sauvegarder les résultats triés des voitures ayant terminé
    fprintf(fichier, "Voitures ayant terminé la course (classées) :\n");
    for (int i = 0; i < compteur_terminees; i++) {
        fprintf(fichier, "Position %d : Voiture %d, Temps : %.2f s\n",
                i + 1, voitures_terminees[i].numero, voitures_terminees[i].meilleur_temps);
    }

    // Sauvegarder les voitures ayant abandonné
    fprintf(fichier, "\nVoitures ayant abandonné :\n");
    for (int i = 0; i < nombre_voitures; i++) {
        if (voitures[i].status == 'O') { // Si la voiture a abandonné
            fprintf(fichier, "Voiture %d : Abandon\n", voitures[i].numero);
        }
    }

    fclose(fichier);
    printf("Résultats sauvegardés dans %s\n", nom_fichier);
}




void simuler_qualification(Voiture *voitures, int nombre_voitures) {
    int voitures_restantes = nombre_voitures;
    int phase = 1;

    while (voitures_restantes > 10) {
        printf("\nDébut de la phase Q%d...\n", phase);

        // Simulation des tours pour cette phase
        for (int tour = 0; tour < 10; tour++) {
            printf("Tour %d :\n", tour + 1);
            for (int i = 0; i < voitures_restantes; i++) {
                generer_temps(&voitures[i]);
                printf("Voiture %d : %.2f s\n", voitures[i].numero, voitures[i].meilleur_temps);
            }
            printf("\n");
        }

        // Trier les voitures par leur meilleur temps
        qsort(voitures, voitures_restantes, sizeof(Voiture), comparer_voitures);

        // Afficher les résultats de la phase
        printf("Résultats de la phase Q%d :\n", phase);
        for (int i = 0; i < voitures_restantes; i++) {
            printf("Voiture %d : %.2f s\n", voitures[i].numero, voitures[i].meilleur_temps);
        }

        // Éliminer les 5 voitures les plus lentes
        printf("Voitures éliminées après Q%d :\n", phase);
        for (int i = voitures_restantes - 5; i < voitures_restantes; i++) {
            printf("Voiture %d : %.2f s\n", voitures[i].numero, voitures[i].meilleur_temps);
        }
        voitures_restantes -= 5;
        phase++;
    }

    // Sauvegarder les résultats finaux de Q3
    sauvegarder_resultats(voitures, 10, "qualification_finale");
}

void simuler_course(Voiture *voitures, int nombre_voitures, int nombre_tours) {
    printf("\nDébut de la course principale...\n");

    // Initialisation des arrêts aux stands (chaque voiture doit faire un arrêt obligatoire)
    int arrets_stands[nombre_voitures];
    for (int i = 0; i < nombre_voitures; i++) {
        arrets_stands[i] = 0;  // 0 signifie que la voiture n'a pas encore fait d'arrêt
    }

    for (int tour = 1; tour <= nombre_tours; tour++) {
        printf("\nTour %d :\n", tour);

        for (int i = 0; i < nombre_voitures; i++) {
            if (voitures[i].status == 'O') continue;  // Ignorer les voitures abandonnées

            // Simuler un arrêt au stand aléatoire (tous les 5 à 7 tours environ)
            if (tour % (rand() % 3 + 5) == 0 && arrets_stands[i] == 0) {
                voitures[i].status = 'P';  // La voiture est au stand
                printf("Voiture %d est au stand.\n", voitures[i].numero);
                arrets_stands[i] = 1;  // Indiquer que la voiture a fait son arrêt obligatoire
                continue;
            }

            // Simuler un abandon aléatoire (probabilité faible)
            if (rand() % 100 < 3) {  // 3% de probabilité d'abandon
                voitures[i].status = 'O';  // O pour "Out"
                printf("Voiture %d abandonne la course.\n", voitures[i].numero);
                continue;
            }

            // Simuler un tour normal
            generer_temps(&voitures[i]);
            printf("Voiture %d : %.2f s\n", voitures[i].numero, voitures[i].meilleur_temps);
        }

        // Trier les voitures par leur meilleur temps total
        qsort(voitures, nombre_voitures, sizeof(Voiture), comparer_voitures);

        // Afficher le classement temporaire
        printf("Classement provisoire après le tour %d :\n", tour);
        for (int i = 0; i < nombre_voitures; i++) {
            if (voitures[i].status == 'O') continue;  // Ne pas afficher les voitures abandonnées
            printf("Position %d : Voiture %d, Temps : %.2f s\n", i + 1, voitures[i].numero, voitures[i].meilleur_temps);
        }
    }

    // Sauvegarder les résultats finaux de la course
    sauvegarder_resultats(voitures, nombre_voitures, "course_principale");
}
