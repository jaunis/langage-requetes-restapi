/*
 * dict_utils.c
 *
 *  Created on: 8 oct. 2013
 *      Author: jean
 */

#include "types.h"
#include "dict_utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char* dict_valeur(dict* dict, char* champ) {
	entree* entree;
	for(int i=0; i<dict->nb_entrees; i++) {
		entree = dict->entrees[i];
		if(strcmp(champ, entree->cle) == 0)
			return entree->valeur;
	}
	return NULL;
}

void dict_inserer_cle_valeur(dict* dict, const char* cle, const char* valeur) {
	if(!remplacer_entree_existante(dict, cle, valeur)) {
		inserer_nouvelle_entree(dict, cle, valeur);
	}
}

bool remplacer_entree_existante(dict* dict, const char* cle, const char* valeur) {
	for (int i = 0; i < dict->nb_entrees; i++) {
		entree* entree = dict->entrees[i];
		if (strcmp(cle, entree->cle) == 0) {
			entree->valeur = realloc(entree->valeur,
					sizeof(char) * strlen(valeur));
			strcpy(entree->valeur, valeur);
			return true;
		}
	}
	return false;
}

void inserer_nouvelle_entree(dict* dict, const char* cle, const char* valeur) {
	entree* nouvelle_entree = malloc(sizeof(entree));
	nouvelle_entree->cle = malloc(sizeof(char) * strlen(cle));
	strcpy(nouvelle_entree->cle, cle);
	nouvelle_entree->valeur = malloc(sizeof(char) * strlen(valeur));
	strcpy(nouvelle_entree->valeur, valeur);
	if (dict->nb_entrees == dict->_taille_allouee) {
		int nouvelle_taille_allouee = dict->_taille_allouee * 2;
		dict->entrees = realloc(dict->entrees,
				sizeof(entree*) * nouvelle_taille_allouee);
		dict->_taille_allouee = nouvelle_taille_allouee;
	}
	dict->entrees[dict->nb_entrees] = nouvelle_entree;
	(dict->nb_entrees)++;
}


dict* initialiser_dict(int taille_initiale) {
	dict* dict = malloc(sizeof(dict));
	dict->entrees = malloc(sizeof(entree*) * taille_initiale);
	dict->nb_entrees = 0;
	dict->_taille_allouee = taille_initiale;
	return dict;
}
