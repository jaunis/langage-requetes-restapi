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

#endif /* ANALYSEUR_SEMANTIQUE_H_ */
