/*
 * analyseur_json.h
 *
 *  Created on: 8 oct. 2013
 *      Author: jean
 */

#include <stdbool.h>
#include <json/json.h>

#ifndef ANALYSEUR_JSON_H_
#define ANALYSEUR_JSON_H_

bool analyser_json(char* json, t_resultat* resultat, char* prefixe);
void remplir_dict_avec_element(dict* dict, json_object* element, char* prefixe);

#endif /* ANALYSEUR_JSON_H_ */
