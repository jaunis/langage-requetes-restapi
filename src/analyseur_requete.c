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
    etat_analyse_projection etat = projection_etat_initial;
    t_projection projection = {
    		.taille = 0,
    		.champs = malloc((lexemes.taille - 1) * sizeof(char*))
    };
    while(etat != projection_etat_final) {
    	switch(etat) {
    	case projection_etat_initial:
    		if(strcmp(",", tableau[*position]) == 0) {
    			printf("Virgule inattendue en position %d\n", *position);
    			return false;
    		}
    		projection.champs[projection.taille] = malloc((strlen(tableau[*position]) + 1) * sizeof(char));
    		strcpy(projection.champs[projection.taille], tableau[*position]);
    		projection.taille++;
    		etat = projection_champ;
    		(*position)++;
    		break;
    	case projection_champ:
    		if(strcmp(",", tableau[*position]) == 0) {
    			etat = projection_etat_initial;
    			(*position)++;
    		} else {
    			etat = projection_etat_final;
    		}
    		break;
    	}
    }
    requete->projection = projection;
    return true;
}

bool construire_condition_et_renvoyer_statut(char** clause_where, int taille_clause_where, t_condition* condition) {
	int nouvelle_taille = 0;
	char** clause_where_concatenee = concatener_tests(clause_where, taille_clause_where, &nouvelle_taille);
	t_liste_str* clause_prefixee = prefixer_expression(clause_where_concatenee, nouvelle_taille);
	*condition = *transformer_expression_prefixee_en_arbre(&clause_prefixee);
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

t_condition* transformer_expression_prefixee_en_arbre(t_liste_str** expression_prefixee) {
	t_condition* resultat = initialiser_condition((*expression_prefixee)->valeur);
	*expression_prefixee = (*expression_prefixee)->suivant;
	if(est_operateur(resultat->valeur)) {
		resultat->fils_gauche = transformer_expression_prefixee_en_arbre(expression_prefixee);
		resultat->fils_droit = transformer_expression_prefixee_en_arbre(expression_prefixee);
	}
	return resultat;
}

t_condition* initialiser_condition(char* valeur) {
	t_condition* resultat = malloc(sizeof(t_condition));
	resultat->valeur = valeur;
	resultat->fils_droit = NULL;
	resultat->fils_gauche = NULL;
	return resultat;
}

char** concatener_tests(char** clause_where, int taille_clause_where, int* nouvelle_taille) {
	char** resultat = malloc(taille_clause_where * sizeof(char*));
	int j = 0;
	for(int i = 0; i < taille_clause_where; i++) {
		if(strcmp(clause_where[i], "=") == 0) {
			if(i-1 < 0 || i + 1 >= taille_clause_where) {
				printf("Erreur : %s", clause_where[i]);
				exit(1);
			}
			int taille_test = strlen(clause_where[i - 1]) + strlen(clause_where[i]) + strlen(clause_where[i + 1]);
			resultat[j-1] = malloc(sizeof(char) * (taille_test + 1));
			sprintf(resultat[j-1], "%s%s%s", clause_where[i - 1], clause_where[i], clause_where[i + 1]);
			i++;
		} else {
			resultat[j] = clause_where[i];
			j++;
		}
	}
	*nouvelle_taille = j;
	return resultat;
}
