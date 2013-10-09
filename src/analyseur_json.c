/*
 * analyseur_json.c
 *
 *  Created on: 8 oct. 2013
 *      Author: jean
 */

#include "types.h"
#include "dict_utils.h"
#include <json/json.h>

void analyser_json(char* json, t_resultat* resultat) {
	json_object* jobj = json_tokener_parse(json);
	json_object* contenu =  json_object_object_get(jobj, "items");
	int taille = json_object_array_length(contenu);
	resultat->taille = taille;
	resultat->liste = malloc(taille * sizeof(dict*));
	json_object* element;
	for(int i=0; i<taille; i++) {
		element = json_object_array_get_idx(contenu, i);
		dict* dict = initialiser_dict(10);
		json_object_object_foreach(element, key, val) {
			dict_inserer_cle_valeur(dict, key, json_object_get_string(val));
		}
		resultat->liste[i] = dict;
	}
}
