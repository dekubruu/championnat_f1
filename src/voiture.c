#include <stdio.h>
#include <stdlib.h>
#include "voiture.h"

void initialiser_voiture(Voiture *v, int numero) {
    v->numero = numero;
    v->meilleur_temps = 9999.0;  // Un temps élevé au départ
    v->status = 'R';             // La voiture roule au départ
    for (int i = 0; i < 3; i++) {
        v->secteurs[i] = 0.0;
    }
}

void generer_temps(Voiture *v) {
    if (v->status == 'R') {
        float temps_total = 0.0;
        for (int i = 0; i < 3; i++) {
            v->secteurs[i] = (float)(rand() % 21 + 25);  // Temps entre 25 et 45 secondes
            temps_total += v->secteurs[i];
        }
        if (temps_total < v->meilleur_temps) {
            v->meilleur_temps = temps_total;
        }
    }
}
