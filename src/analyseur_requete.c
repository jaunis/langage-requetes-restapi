#include "analyseur_requete.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

t_requete_lexemes diviser_requete_en_lexemes(char* requete) {
    t_requete_lexemes resultat;
    //on suppose que les mots font en moyenne plus de 4 caractères
    resultat.tableau = malloc((strlen(requete)/4)*sizeof(char*));
    char* lexeme = strtok(requete, " ");
    int i = 0;
    while(lexeme !=  NULL) {
    	char* sous_lexeme = malloc(sizeof(lexeme));
    	sous_lexeme[0] = '\0';
    	for(int j=0; j<strlen(lexeme); j++) {
    		if(lexeme[j] == ',' || lexeme[j] == '=') {
    			if(strlen(sous_lexeme) > 0) {
    				resultat.tableau[i] = sous_lexeme;
    				sous_lexeme = malloc(sizeof(lexeme));
    				sous_lexeme[0] = '\0';
    				i++;
    			}
    			resultat.tableau[i] = malloc(sizeof(char));
    			sprintf(resultat.tableau[i], "%c", lexeme[j]);
    			i++;
    		} else {
    			sprintf(sous_lexeme, "%s%c", sous_lexeme, lexeme[j]);
    		}
    	}
    	if(strlen(sous_lexeme) > 0) {
    		resultat.tableau[i] = sous_lexeme;
    		i++;
    	}
        lexeme = strtok(NULL, " ");
    }
    resultat.taille = i;
    return resultat;
}

bool construire_requete_et_renvoyer_statut(t_requete_lexemes lexemes, t_requete* requete) {
    int no_lexeme = 0;
    char** tableau = lexemes.tableau;
    if(strcmp(tableau[no_lexeme], "select") != 0) {
    	printf("Requête invalide. Attendu : select, reçu : %s\n", tableau[0]);
    	return false;
    }
    no_lexeme++;
    if(!analyser_projection(lexemes, &no_lexeme, requete))
    	return false;
    if(strcmp(tableau[no_lexeme], "from") != 0) {
		printf("Requête invalide. Attendu : from, reçu: %s\n", tableau[2]);
		return false;
	}
    no_lexeme++;
    if(strlen(tableau[no_lexeme]) == 0) {
    	printf("Requête invalide : clause from vide.\n");
    	return false;
    }
	requete->cible = tableau[no_lexeme];
	if((no_lexeme + 1) < lexemes.taille) {
		printf("Eléments non traités dans la requête : %s\n", tableau[no_lexeme+1]);
		return false;
	}
    return true;
}

bool analyser_projection(t_requete_lexemes lexemes, int* position, t_requete* requete) {
	char** tableau = lexemes.tableau;
    etat_analyse_projection etat = etat_initial;
    t_projection projection = {
    		.taille = 0,
    		.champs = malloc((lexemes.taille - 1) * sizeof(char*))
    };
    while(etat != etat_final) {
    	switch(etat) {
    	case etat_initial:
    		if(strcmp(",", tableau[*position]) == 0) {
    			printf("Virgule inattendue en position %d\n", *position);
    			return false;
    		}
    		projection.champs[projection.taille] = malloc((strlen(tableau[*position]) + 1) * sizeof(char));
    		strcpy(projection.champs[projection.taille], tableau[*position]);
    		projection.taille++;
    		etat = champ;
    		(*position)++;
    		break;
    	case champ:
    		if(strcmp(",", tableau[*position]) == 0) {
    			etat = etat_initial;
    			(*position)++;
    		} else {
    			etat = etat_final;
    		}
    		break;
    	}
    }
    requete->projection = projection;
    return true;
}
