#include <stdio.h>
#include <stdlib.h>
#include "voiture.h"

void initialiser_voiture(Voiture *v, int numero) {
    v->numero = numero;
    v->meilleur_temps = 9999.0;  // Temps initial très élevé pour comparaison
    v->status = 'R';             // La voiture roule par défaut
    v->points = 0;               // Initialisation des points à zéro

    // Initialisation des secteurs et des meilleurs secteurs à zéro
    for (int i = 0; i < 3; i++) {
        v->secteurs[i] = 0.0;
        v->meilleur_secteur[i] = 9999.0; // Temps initial élevé pour chaque secteur
    }
}

void generer_temps(Voiture *v) {
    if (v->status == 'R') {  // Si la voiture est en mode "roule"
        float temps_total = 0.0;
        for (int i = 0; i < 3; i++) {
            v->secteurs[i] = (float)(rand() % 21 + 20);  // Temps aléatoire entre 20 et 40 secondes
            temps_total += v->secteurs[i];

            // Mise à jour du meilleur temps dans le secteur
            if (v->secteurs[i] < v->meilleur_secteur[i]) {
                v->meilleur_secteur[i] = v->secteurs[i];
            }
        }
        v->meilleur_temps = temps_total;  // Mise à jour du meilleur temps total
    } else {
        printf("La voiture %d est hors course ou au stand.\n", v->numero);
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
