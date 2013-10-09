/*
 * dict_utils.h
 *
 *  Created on: 8 oct. 2013
 *      Author: jean
 */
#include <stdbool.h>

#ifndef DICT_UTILS_H_
#define DICT_UTILS_H_

dict* initialiser_dict(int);
char* dict_valeur(dict*, char*);
void dict_inserer_cle_valeur(dict*, const char*, const char*);
bool remplacer_entree_existante(dict* dict, const char* cle, const char* valeur);
void inserer_nouvelle_entree(dict* dict, const char* cle, const char* valeur);

#endif /* DICT_UTILS_H_ */
