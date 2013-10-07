#include <stdbool.h>
#include "types.h"

#ifndef ANALYSEUR_REQUETE_H
#define ANALYSEUR_REQUETE_H

t_requete_lexemes diviser_requete_en_lexemes(char*);
bool construire_requete_et_renvoyer_statut(t_requete_lexemes, t_requete*);

#endif
