#include <stdio.h>
#include <stdlib.h>
#include "voiture.h"

void initialiser_voiture(Voiture *v, int numero) {
    v->numero = numero;
    v->meilleur_temps = 9999.0;  // Temps initial très élevé pour comparaison
    v->status = 'R';             // La voiture roule par défaut
    v->points = 0;               // Initialisation des points à zéro

    for (int i = 0; i < 3; i++) {
        v->secteurs[i] = 0.0;
    }
}

void initialiserPilotes(Voiture *pilotes, int nombre_pilotes) {
    int numeros_fixes[20] = {1, 11, 44, 63, 16, 55, 4, 81, 14, 18, 10, 31, 23, 2, 22, 3, 77, 24, 20, 27};

    for (int i = 0; i < nombre_pilotes; i++) {
        initialiser_voiture(&pilotes[i], numeros_fixes[i]);
        sprintf(pilotes[i].prenom, "Prenom%d", i + 1);
        sprintf(pilotes[i].nom, "Nom%d", i + 1);
    }
}

void generer_temps(Voiture *v) {
    if (v->status == 'R') {
        int random_event = rand() % 100;
        if (random_event < 5) {
            v->status = 'O';
            printf("Voiture %d : Abandon\n", v->numero);
            return;
        } else if (random_event < 15) {
            v->status = 'P';
            printf("Voiture %d : Aux stands\n", v->numero);
            return;
        }

        float temps_total = 0.0;
        for (int i = 0; i < 3; i++) {
            v->secteurs[i] = (float)(rand() % 21 + 25);
            temps_total += v->secteurs[i];
        }
        v->meilleur_temps = temps_total;
    }
}

void afficherClassementFinal(Voiture *pilotes, int nombre_pilotes) {
    printf("Classement final :\n");
    for (int i = 0; i < nombre_pilotes; i++) {
        printf("Position %d : %s %s (Voiture %d), Points : %d, Meilleur temps : %.2f s\n",
               i + 1, pilotes[i].prenom, pilotes[i].nom, pilotes[i].numero, pilotes[i].points, pilotes[i].meilleur_temps);
    }
}

void attribuerPoints(Voiture *pilotes, int nombre_pilotes) {
    int bareme_points[] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
    for (int i = 0; i < 10 && i < nombre_pilotes; i++) {
        pilotes[i].points += bareme_points[i];
    }
}
