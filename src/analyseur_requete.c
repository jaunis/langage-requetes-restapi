#include "analyseur_requete.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

t_requete_lexemes diviser_requete_en_lexemes(char* requete) {
    t_requete_lexemes resultat;
    resultat.tableau = malloc((strlen(requete)/4)*sizeof(char*));
    char* lexeme = strtok(requete, " ");
    int i = 0;
    while(lexeme !=  NULL) {
        resultat.tableau[i] = lexeme;
        i++;
        lexeme = strtok(NULL, " ");
    }
    resultat.taille = i;
    return resultat;
}

bool construire_requete_et_renvoyer_statut(t_requete_lexemes lexemes, t_requete* requete) {
    if(lexemes.taille != 4) {
    	printf("Requête incomplète.\n");
    	return false;
    }
    char** tableau = lexemes.tableau;
    if(strcmp(tableau[0], "select") != 0) {
    	printf("Requête invalide. Attendu : select, reçu : %s\n", tableau[0]);
    	return false;
    }
    if(strcmp(tableau[1], "*") != 0) {
    	printf("Requête invalide : %s\n", tableau[1]);
    	return false;
    }
    if(strcmp(tableau[2], "from") != 0) {
		printf("Requête invalide. Attendu : from, reçu: %s\n", tableau[2]);
		return false;
	}
    if(strlen(tableau[3]) == 0) {
    	printf("Requête invalide : clause from vide.\n");
    	return false;
    }
	requete->cible = tableau[3];
    return true;
}
