/*
 * analyseur_lexical.c
 *
 *  Created on: 25 oct. 2013
 *      Author: jean
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "types.h"
#include "analyseur_lexical.h"

static const char CARACTERES_SPECIAUX[] = {',', '=', '(', ')'};

t_requete_lexemes diviser_requete_en_lexemes(char* requete) {
    t_requete_lexemes resultat;
    //on suppose que les mots font en moyenne plus de 4 caractères
    resultat.tableau = malloc((strlen(requete)/4)*sizeof(char*));
    resultat.taille = 0;
    char* lexeme = strtok(requete, " ");
    while(lexeme !=  NULL) {
    	extraire_caracteres_speciaux(lexeme, &resultat);
        lexeme = strtok(NULL, " ");
    }
    return resultat;
}

void extraire_caracteres_speciaux(char* lexeme, t_requete_lexemes* resultat) {
	char* sous_lexeme = malloc((strlen(lexeme) + 1) * sizeof(char));
	sous_lexeme[0] = '\0';
	for(int j=0; j<strlen(lexeme); j++) {
		if(est_caractere_special(lexeme[j])) {
			if(strlen(sous_lexeme) > 0) {
				resultat->tableau[resultat->taille] = sous_lexeme;
				sous_lexeme = malloc((strlen(lexeme) - strlen(sous_lexeme) + 1) * sizeof(char));
				sous_lexeme[0] = '\0';
				resultat->taille++;
			}
			resultat->tableau[resultat->taille] = malloc(2*sizeof(char));
			sprintf(resultat->tableau[resultat->taille], "%c", lexeme[j]);
			resultat->taille++;
		} else {
			sprintf(sous_lexeme, "%s%c", sous_lexeme, lexeme[j]);
		}
	}
	if(strlen(sous_lexeme) > 0) {
		resultat->tableau[resultat->taille] = sous_lexeme;
		resultat->taille++;
	};
}

bool est_caractere_special(char caractere) {
	int taille = sizeof(CARACTERES_SPECIAUX) / sizeof(char);
	for(int i = 0; i < taille; i++) {
		if(CARACTERES_SPECIAUX[i] == caractere)
			return true;
	}
	return false;
}
