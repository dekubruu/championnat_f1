#ifndef VOITURE_H
#define VOITURE_H

typedef struct {
    int numero;         // Numéro de la voiture
    float meilleur_temps;  // Meilleur temps total
    float secteurs[3];   // Temps des secteurs S1, S2, S3
    char status;        // Statut : 'R' (roule), 'P' (stands), 'O' (out)
} Voiture;

// Prototypes des fonctions
void initialiser_voiture(Voiture *v, int numero);
void generer_temps(Voiture *v);

#endif // VOITURE_H
