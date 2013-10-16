/*
 * liste_str_utils.c
 *
 *  Created on: 16 oct. 2013
 *      Author: jean
 */

#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "liste_str_utils.h"

void liste_str_inserer(t_liste_str** liste, char* element, int position) {
	if((*liste)->valeur == NULL) {
		if(position > 0) {
			printf("Erreur : %s\n", element);
			exit(1);
		}
		(*liste)->valeur = element;
	} else {
		int i = 0;
		t_liste_str* suivant = *liste;
		t_liste_str* precedent = NULL;
		while(i < position) {
			if(suivant == NULL) {
				printf("Erreur : %s\n", element);
				exit(1);
			}
			precedent = suivant;
			suivant = suivant->suivant;
			i++;
		}
		t_liste_str* nouveau = malloc(sizeof(t_liste_str));
		nouveau->valeur = element;
		nouveau->suivant = suivant;
		if(precedent == NULL)
			*liste = nouveau;
		else
			precedent->suivant = nouveau;
	}
}

t_liste_str* initialiser_liste_str() {
	t_liste_str* resultat = malloc(sizeof(t_liste_str));
	resultat->valeur = NULL;
	resultat->suivant = NULL;
	return resultat;
}
