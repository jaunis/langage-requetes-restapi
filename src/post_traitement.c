/*
 * post_traitement.c
 *
 *  Created on: 18 oct. 2013
 *      Author: jean
 */

#include "post_traitement.h"
#include <stdlib.h>
#include <string.h>
#include "resultat_utils.h"

void appliquer_clause_where(t_resultat* resultat, t_condition* condition) {
	if(condition->valeur == NULL)
		return;
	dict** ancienne_liste = resultat->liste;
	dict** nouvelle_liste = malloc(resultat->taille * sizeof(dict*));
	int nouvelle_taille = 0;
	for(int i = 0; i < resultat->taille; i++) {
		dict* element = resultat->liste[i];
		if(element_verifie_condition(element, condition)) {
			nouvelle_liste[nouvelle_taille] = element;
			nouvelle_taille++;
		} else {
			free_dict(element);
		}
	}
	free(ancienne_liste);
	resultat->liste = nouvelle_liste;
	resultat->taille = nouvelle_taille;
}

bool element_verifie_condition(dict* element, t_condition* condition) {
	if(strcmp("or", condition->valeur) == 0) {
		return element_verifie_condition(element, condition->fils_gauche) ||
				element_verifie_condition(element, condition->fils_droit);
	} else if(strcmp("and", condition->valeur) == 0) {
		return element_verifie_condition(element, condition->fils_gauche) &&
						element_verifie_condition(element, condition->fils_droit);
	} else {
		return element_passe_test(element, condition->valeur);
	}
}

bool element_passe_test(dict* element, char* test) {
	char* test_recopie = malloc((strlen(test) + 1) * sizeof(char));
	strcpy(test_recopie, test);
	char* champ = strtok(test_recopie, "=");
	if(!dict_contient_champ(element, champ))
		return false;
	char* valeur_attendue = strtok(NULL, "=");
	char* valeur = dict_valeur(element, champ);
	return strcmp(valeur_attendue, valeur) == 0;
}
