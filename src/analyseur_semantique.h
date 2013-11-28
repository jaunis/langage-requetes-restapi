/*
 * analyseur_semantique.h
 *
 *  Created on: 22 nov. 2013
 *      Author: jean
 */

#ifndef ANALYSEUR_SEMANTIQUE_H_
#define ANALYSEUR_SEMANTIQUE_H_

#include <stdbool.h>
#include "types.h"

bool controler_jointures(t_requete*);
bool verifier_presence_point(char*);
bool tableau_contient_str(char** tableau, char* chaine, int taille_tableau);
bool controler_conditions(t_requete* requete);
bool conditions_sont_prefixees(t_requete* requete);
bool verifier_prefixage_arbre(t_condition condition, char** cibles, int nb_cibles);
bool valider_requete(t_requete* requete);
bool controler_projection(t_requete* requete);
void liste_cibles(t_requete* requete, char** cibles);
bool verifier_prefixage_projection(t_projection projection, char** cibles, int nb_cibles);
bool controler_jointure(t_jointure* jointure, char** cibles_existantes, int taille_tableau);
bool verifier_non_prefixage_projection(t_projection projection);
bool verifier_absence_point(char* chaine);
bool conditions_sont_non_prefixees(t_condition condition);

#endif /* ANALYSEUR_SEMANTIQUE_H_ */
