/*
 * dict_utils.h
 *
 *  Created on: 8 oct. 2013
 *      Author: jean
 */

#ifndef DICT_UTILS_H_
#define DICT_UTILS_H_

dict* initialiser_dict(int);
char* dict_valeur(dict*, char*);
void dict_ajouter_cle_valeur(dict*, char*, char*);

#endif /* DICT_UTILS_H_ */
