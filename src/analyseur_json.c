/*
 * analyseur_json.c
 *
 *  Created on: 8 oct. 2013
 *      Author: jean
 */

#include "types.h"
#include "utils/dict_utils.h"
#include "analyseur_json.h"
#include <json/json.h>
#include <json/json_tokener.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool analyser_json(char* json, t_resultat* resultat, char* prefixe) {
	json_object* jobj = json_tokener_parse(json);
	if(jobj == NULL) {
		printf("Erreur dans l'analyse du JSON.\n");
		printf("JSON reçu : %s\n", json);
		return false;
	}
	json_object* contenu;
	if(!json_object_object_get_ex(jobj, "items", &contenu)) {
		free(jobj);
		return false;
	}
	if(json_object_get_type(contenu) != json_type_array) {
		free(jobj);
		free(contenu);
		return false;
	}
	int taille = json_object_array_length(contenu);
	resultat->taille = taille;
	resultat->liste = malloc(taille * sizeof(dict*));
	json_object* element;
	for(int i=0; i<taille; i++) {
		element = json_object_array_get_idx(contenu, i);
		dict* dict = initialiser_dict(10);
		remplir_dict_avec_element(dict, element, prefixe);
		resultat->liste[i] = dict;
	}
	return true;
}

void remplir_dict_avec_element(dict* dict, json_object* element, char* prefixe) {
	json_object_object_foreach(element, key, val) {
		char* cle_prefixee = malloc((strlen(prefixe) + strlen(key) + 2) * sizeof(char));
		sprintf(cle_prefixee, "%s%s", prefixe, key);
		json_type type = json_object_get_type(val);
		if(type == json_type_double || type == json_type_int || type == json_type_string || type == json_type_boolean)
			dict_inserer_cle_valeur(dict, cle_prefixee, json_object_get_string(val));
		else if(type == json_type_null)
			dict_inserer_cle_valeur(dict, cle_prefixee, "");
	}
}
