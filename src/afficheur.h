/*
 * afficheur.h
 *
 *  Created on: 10 oct. 2013
 *      Author: jean
 */

#include "types.h"

#ifndef AFFICHEUR_H_
#define AFFICHEUR_H_

void afficher_resultat(t_resultat*);
char** extraire_en_tete(t_resultat* resultat, int* taille_en_tete);
void afficher_en_tete(char** en_tete, int taille_en_tete);
void afficher_lignes(t_resultat* resultat, char** en_tete, int taille_en_tete);
void desallouer_en_tete(char** en_tete, int taille_en_tete);

#endif /* AFFICHEUR_H_ */
