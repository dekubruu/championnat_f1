#ifndef SESSION_H
#define SESSION_H

#include "voiture.h"

// Prototypes des fonctions
void sauvegarder_resultats(Voiture *voitures, int nombre_voitures, const char *nom_session);
void simuler_qualification(Voiture *voitures, int nombre_voitures);
int comparer_voitures(const void *a, const void *b);  // Ajout du prototype
void simuler_course(Voiture *voitures, int nombre_voitures, int nombre_tours);


#endif // SESSION_H
