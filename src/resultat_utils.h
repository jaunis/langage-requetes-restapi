/*
 * resultat_utils.h
 *
 *  Created on: 8 oct. 2013
 *      Author: jean
 */
#include <stdbool.h>

#ifndef resultat_utils_H_
#define resultat_utils_H_

dict* initialiser_dict(int);
char* dict_valeur(dict*, char*);
void dict_inserer_cle_valeur(dict*, const char*, const char*);
bool remplacer_entree_existante(dict* dict, const char* cle, const char* valeur);
void inserer_nouvelle_entree(dict* dict, const char* cle, const char* valeur);
void free_dict(dict* dict);

#endif /* resultat_utils_H_ */
