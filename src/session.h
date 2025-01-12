#ifndef SESSION_H
#define SESSION_H

#include "voiture.h"

// Prototypes des fonctions
void sauvegarder_resultats(Voiture *voitures, int nombre_voitures, const char *nom_session);
void simuler_qualification(Voiture *voitures, int nombre_voitures);
int comparer_voitures(const void *a, const void *b);
void simuler_course(Voiture *voitures, int nombre_voitures, int nombre_tours);
void initialiserPilotes(Voiture *pilotes, int nombre_pilotes);

void lancerEssaisP1(Voiture *pilotes, int nombre_pilotes);
void lancerEssaisP2(Voiture *pilotes, int nombre_pilotes);
void lancerEssaisP3(Voiture *pilotes, int nombre_pilotes);

void lancerQualifications(Voiture *pilotes, int nombre_pilotes);
void lancerCourse(Voiture *pilotes, int nombre_pilotes);



#endif // SESSION_H
