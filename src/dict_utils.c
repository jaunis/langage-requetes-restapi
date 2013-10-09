/*
 * dict_utils.c
 *
 *  Created on: 8 oct. 2013
 *      Author: jean
 */

#include "types.h"
#include <string.h>
#include <stdlib.h>

char* dict_valeur(dict* dict, char* champ) {
	entree* entree;
	for(int i=0; i<dict->nb_entrees; i++) {
		entree = dict->entrees[i];
		if(strcmp(champ, entree->cle) == 0)
			return entree->valeur;
	}
	return NULL;
}

void dict_ajouter_cle_valeur(dict* dict, char* cle, char* valeur) {

}
