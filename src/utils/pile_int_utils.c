/*
 * pile_int_utils.c
 *
 *  Created on: 16 oct. 2013
 *      Author: jean
 */

#include <stdlib.h>
#include "../types.h"
#include "pile_int_utils.h"

int pop(t_pile_int** pile) {
	int resultat = (*pile)->valeur;
	if((*pile)->suivant == NULL)
		(*pile)->valeur = -1;
	else
		*pile = (*pile)->suivant;
	return resultat;
}

void push(int valeur, t_pile_int** pile) {
	if((*pile)->valeur == -1) {
		(*pile)->valeur = valeur;
	} else {
		t_pile_int* sommet = malloc(sizeof(t_pile_int));
		sommet->valeur = valeur;
		sommet->suivant = *pile;
		*pile = sommet;
	}

}

t_pile_int* initialiser_pile_int() {
	t_pile_int* resultat = malloc(sizeof(t_pile_int));
	resultat->valeur = -1;
	resultat->suivant = NULL;
	return resultat;
}
