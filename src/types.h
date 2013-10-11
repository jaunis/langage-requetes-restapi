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

typedef struct t_requete_lexemes {
    char** tableau;
    int taille;
} t_requete_lexemes;

typedef struct t_requete {
    char* cible;
} t_requete;

typedef struct t_en_tete {
	char** colonnes;
	int taille;
} t_en_tete;

#endif /* TYPES_H_ */
