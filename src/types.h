/*
 * types.h
 *
 *  Created on: 7 oct. 2013
 *      Author: jean
 */

#ifndef TYPES_H_
#define TYPES_H_

typedef struct t_entree {
	char* cle;
	char* valeur;
} t_entree;

typedef struct dict {
	t_entree** entrees;
	int nb_entrees;
	int _taille_allouee;
} dict;

typedef struct t_resultat {
	dict** liste;
	int taille;
} t_resultat;

typedef struct t_resultats {
	int taille;
	t_resultat* resultats;
} t_resultats;

typedef struct t_requete_lexemes {
    char** tableau;
    int taille;
} t_requete_lexemes;

typedef struct t_projection {
	int taille;
	char** champs;
} t_projection;

typedef enum t_element_condition {
	operateur,
	operande
} t_element_condition;

typedef struct t_condition {
	t_element_condition type;
	char* valeur;
	struct t_condition* fils_gauche;
	struct t_condition* fils_droit;
} t_condition;

typedef struct t_jointure {
	char* cible;
	char* condition;
} t_jointure;

typedef struct t_jointures {
	int nb_jointures;
	t_jointure* jointures;
} t_jointures;

typedef struct t_requete {
    char* cible;
    t_jointures jointures;
    t_projection projection;
    t_condition condition;
} t_requete;


typedef struct t_en_tete {
	char** colonnes;
	int taille;
} t_en_tete;

typedef struct t_liste_str {
	char* valeur;
	struct t_liste_str* suivant;
} t_liste_str;

typedef struct t_pile_int {
	int valeur;
	struct t_pile_int* suivant;
} t_pile_int;

#endif /* TYPES_H_ */
