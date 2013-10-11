/*
 * analyseur_json.c
 *
 *  Created on: 8 oct. 2013
 *      Author: jean
 */

#include "types.h"
#include "resultat_utils.h"
#include "analyseur_json.h"
#include <json/json.h>
#include <stdbool.h>

bool analyser_json(char* json, t_resultat* resultat) {
	json_object* jobj = json_tokener_parse(json);
	json_object* contenu;
	if(!json_object_object_get_ex(jobj, "items", &contenu))
		return false;
	if(json_object_get_type(contenu) != json_type_array)
		return false;
	int taille = json_object_array_length(contenu);
	resultat->taille = taille;
	resultat->liste = malloc(taille * sizeof(dict*));
	json_object* element;
	for(int i=0; i<taille; i++) {
		element = json_object_array_get_idx(contenu, i);
		dict* dict = initialiser_dict(10);
		json_object_object_foreach(element, key, val) {
			if(json_object_get_type(val) != json_type_array)
				dict_inserer_cle_valeur(dict, key, json_object_get_string(val));
		}
		resultat->liste[i] = dict;
	}
	return true;
}
