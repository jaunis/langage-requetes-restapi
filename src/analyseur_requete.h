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
t_condition* transformer_expression_prefixee_en_arbre(t_liste_str* expression_prefixee);
t_condition* initialiser_condition(char* valeur);

typedef enum etat_analyse_projection {
	etat_initial,
	champ,
	etat_final
} etat_analyse_projection;

#endif
