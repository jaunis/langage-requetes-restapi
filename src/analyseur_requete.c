#include "analyseur_requete.h"
#include "pile_int_utils.h"
#include "liste_str_utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
		if(lexeme[j] == ',' || lexeme[j] == '=') {
			if(strlen(sous_lexeme) > 0) {
				resultat->tableau[resultat->taille] = sous_lexeme;
				sous_lexeme = malloc((strlen(lexeme) - strlen(sous_lexeme) + 1) * sizeof(char));
				sous_lexeme[0] = '\0';
				resultat->taille++;
			}
			resultat->tableau[resultat->taille] = malloc(sizeof(char));
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

bool construire_condition_et_renvoyer_statut(char** clause_where, int taille_clause_where, t_condition* condition) {
	condition->type = operande;
	condition->valeur = malloc(sizeof(char));
	condition->valeur[0] = '\0';
	for(int i=0; i< taille_clause_where; i++) {
		int nouvelle_taille = strlen(condition->valeur) + strlen(clause_where[i]);
		condition->valeur = realloc(condition->valeur, (nouvelle_taille + 1) * sizeof(char));
		strcat(condition->valeur, clause_where[i]);
	}
	return true;
}

t_liste_str* prefixer_expression(char** clause_where, int taille_clause_where) {
	t_liste_str* resultat = initialiser_liste_str();
	t_pile_int* positions_ou_inserer = initialiser_pile_int();
	int parentheses_a_fermer = 0;
	int ou_inserer = 0;
	int taille_liste = 0;
	for(int i = 0; i < taille_clause_where; i++) {
		char* lexeme = clause_where[i];
		if(est_operateur(lexeme)) {
			int position_ou_inserer = pop(&positions_ou_inserer);
			liste_str_inserer(&resultat, lexeme, position_ou_inserer);
			taille_liste++;
			ou_inserer = taille_liste;
		} else if (strcmp("(", lexeme) == 0){
			push(ou_inserer, &positions_ou_inserer);
			parentheses_a_fermer++;
		} else if(strcmp(")", lexeme) == 0) {
			parentheses_a_fermer--;
		} else {
			liste_str_inserer(&resultat, lexeme, taille_liste);
			taille_liste++;
		}
	}
	//TODO: liberer_pile(&positions_ou_inserer);
	return resultat;
}

bool est_operateur(char* lexeme) {
	return (strcmp("and", lexeme) == 0 || strcmp("or", lexeme) == 0);
}

t_condition* transformer_expression_prefixee_en_arbre(t_liste_str* expression_prefixee) {
	return NULL;
}
