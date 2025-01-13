#ifndef COURSE_H
#define COURSE_H

#include "voiture.h"  // Pour utiliser la structure Voiture

// Fonction pour simuler la course principale
void simuler_course(Voiture *voitures, int nombre_voitures, int nombre_tours);

// Fonction pour lancer la course principale
void lancerCourse(Voiture *pilotes, int nombre_pilotes);

#endif // COURSE_H
