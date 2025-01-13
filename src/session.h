#ifndef SESSION_H
#define SESSION_H

#include "voiture.h"

// Fonction pour comparer les voitures selon leur meilleur temps
int comparer_voitures(const void *a, const void *b);

// Fonction pour sauvegarder les résultats dans un fichier
void sauvegarder_resultats(Voiture *voitures, int nombre_voitures, const char *nom_session);

// Fonction pour afficher les meilleurs temps par secteur et le meilleur tour
void afficherMeilleursTemps(Voiture *voitures, int nombre_voitures);

#endif // SESSION_H
