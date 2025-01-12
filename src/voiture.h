#ifndef VOITURE_H
#define VOITURE_H

typedef struct {
    int numero;            // Numéro de la voiture
    char prenom[50];       // Prénom du pilote
    char nom[50];          // Nom du pilote
    char equipe[50];       // Nom de l'équipe
    float meilleur_temps;  // Meilleur temps total
    float secteurs[3];     // Temps des secteurs S1, S2, S3
    char status;           // Statut : 'R' (roule), 'P' (stands), 'O' (out)
    int points;            // Points accumulés
    float meilleur_secteur[3]; // Meilleurs temps des secteurs S1, S2, S3
} Voiture;

// Prototypes des fonctions
void initialiser_voiture(Voiture *v, int numero);
void generer_temps(Voiture *v);
void afficherClassementFinal(Voiture *pilotes, int nombre_pilotes);
void attribuerPoints(Voiture *pilotes, int nombre_pilotes);

#endif // VOITURE_H
