/*
 * types.h
 *
 *  Created on: 7 oct. 2013
 *      Author: jean
 */

#ifndef TYPES_H_
#define TYPES_H_

typedef struct entree {
	char* cle;
	char* valeur;
} entree;

typedef struct dict {
	entree** entrees;
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


#endif /* TYPES_H_ */
