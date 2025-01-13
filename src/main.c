#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "essais.h"
#include "qualifications.h"
#include "course.h"
#include "voiture.h"

#define NOMBRE_VOITURES 20

int main() {
    Voiture listePilotes[NOMBRE_VOITURES];
    int nombre_pilotes = NOMBRE_VOITURES;

    srand(time(NULL));

    initialiserPilotes(listePilotes, nombre_pilotes);

    int choix;
    do {
        printf("\n=== Menu Principal ===\n");
        printf("1. Lancer les essais libres P1\n");
        printf("2. Lancer les essais libres P2\n");
        printf("3. Lancer les essais libres P3\n");
        printf("4. Lancer les qualifications\n");
        printf("5. Lancer la course principale\n");
        printf("6. Afficher les résultats finaux\n");
        printf("7. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: lancerEssaisP1(listePilotes, nombre_pilotes); break;
            case 2: lancerEssaisP2(listePilotes, nombre_pilotes); break;
            case 3: lancerEssaisP3(listePilotes, nombre_pilotes); break;
            case 4: lancerQualifications(listePilotes, nombre_pilotes); break;
            case 5: lancerCourse(listePilotes, nombre_pilotes); break;
            case 6: afficherClassementFinal(listePilotes, nombre_pilotes); break;
            case 7: printf("Merci d'avoir utilisé le programme. Au revoir !\n"); break;
            default: printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 7);

    return 0;
}
