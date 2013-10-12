#include <stdbool.h>
#include "types.h"

#ifndef ANALYSEUR_REQUETE_H
#define ANALYSEUR_REQUETE_H

t_requete_lexemes diviser_requete_en_lexemes(char*);
bool construire_requete_et_renvoyer_statut(t_requete_lexemes, t_requete*);
bool analyser_projection(t_requete_lexemes lexemes, int* position_debut_projection, t_requete* requete);

typedef enum etat_analyse_projection {
	etat_initial,
	champ,
	virgule,
	etat_final
} etat_analyse_projection;

#endif
