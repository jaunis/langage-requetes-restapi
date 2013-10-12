/*
 * afficheur.h
 *
 *  Created on: 10 oct. 2013
 *      Author: jean
 */

#include "types.h"
#include <stdbool.h>

#ifndef AFFICHEUR_H_
#define AFFICHEUR_H_

void afficher_resultat(t_resultat* resultat, t_projection* projection);
t_en_tete creer_en_tete(t_resultat* resultat, t_projection* projection);
t_en_tete concatener_en_tetes(t_en_tete gauche, t_en_tete droit);
t_en_tete extraire_en_tete(t_resultat* resultat);
void afficher_en_tete(t_en_tete en_tete);
void afficher_lignes(t_resultat* resultat, t_en_tete en_tete);
void desallouer_en_tete(t_en_tete en_tete);
void incrementer_taille_en_tete(t_en_tete* en_tete);
void ajouter_colonne(t_en_tete* en_tete, char* valeur);
bool en_tete_contient(t_en_tete en_tete, char* valeur);
int determiner_taille_ligne(dict* dict, t_en_tete en_tete);
void remplir_ligne_avec_dict(char* ligne, dict* dict, t_en_tete en_tete);

#endif /* AFFICHEUR_H_ */
