#include <stdbool.h>
#include "types.h"

#ifndef ANALYSEUR_REQUETE_H
#define ANALYSEUR_REQUETE_H

t_requete_lexemes diviser_requete_en_lexemes(char*);
bool construire_requete_et_renvoyer_statut(t_requete_lexemes, t_requete*);
bool analyser_projection(t_requete_lexemes lexemes, int* position_debut_projection, t_requete* requete);
void extraire_caracteres_speciaux(char* lexeme, t_requete_lexemes* resultat);
bool construire_condition_et_renvoyer_statut(char**, int, t_condition*);
t_liste_str* prefixer_expression(char** clause_where, int taille_clause_where);
bool est_operateur(char* lexeme);
t_condition* transformer_expression_prefixee_en_arbre(t_liste_str** expression_prefixee);
t_condition* initialiser_condition(char* valeur);
char** concatener_tests(char**, int, int*);
bool est_caractere_special(char caractere);
bool analyser_jointures(t_requete_lexemes lexemes, int* no_lexeme, t_requete* requete);
bool est_debut_jointure(t_requete_lexemes lexemes, int no_lexeme);

typedef enum etat_analyse_projection {
	projection_etat_initial,
	projection_champ,
	projection_etat_final
} etat_analyse_projection;

typedef enum etat_analyse_jointure {
	jointure_etat_initial,
	jointure_cible,
	jointure_on,
	jointure_condition,
	jointure_etat_final
} etat_analyse_jointure;

#endif
