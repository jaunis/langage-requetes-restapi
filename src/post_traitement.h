/*
 * post_traitement.h
 *
 *  Created on: 18 oct. 2013
 *      Author: jean
 */
#include <stdbool.h>
#include "types.h"

#ifndef POST_TRAITEMENT_H_
#define POST_TRAITEMENT_H_

void appliquer_clause_where(t_resultat*, t_condition*);
bool element_verifie_condition(dict* element, t_condition* condition);
bool element_passe_test(dict* element, char* test);

#endif /* POST_TRAITEMENT_H_ */
