#ifndef VOITURE_H
#define VOITURE_H

#define MAX_NOM 20  // Taille maximale des noms

// Structure représentant une voiture
typedef struct {
    int numero;                  // Numéro de la voiture
    char nom[MAX_NOM];           // Nom du pilote
    char prenom[MAX_NOM];        // Prénom du pilote
    float secteurs[3];           // Temps des 3 secteurs
    float meilleur_temps;        // Meilleur temps global de la voiture
    char status;                 // Statut : 'R' = Roule, 'P' = Aux stands, 'O' = Out
    int points;                  // Points obtenus par le pilote
} Voiture;

void initialiserPilotes(Voiture *pilotes, int nombre_pilotes);
void afficherClassementFinal(Voiture *pilotes, int nombre_pilotes);
void attribuerPoints(Voiture *pilotes, int nombre_pilotes);

#endif // VOITURE_H
