/*
 * analyseur_semantique.c
 *
 *  Created on: 22 nov. 2013
 *      Author: jean
 */

#include "analyseur_semantique.h"
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include <stdio.h>

bool controler_jointures(t_requete* requete) {
	bool resultat = true;
	bool inverser = false;
	char** cibles_existantes = malloc(sizeof(char*) * (1 + requete->jointures.nb_jointures));
	cibles_existantes[0] = requete->cible;
	for(int i=0; i < requete->jointures.nb_jointures; i++) {
		t_jointure* jointure = &(requete->jointures.liste[i]);
		char* cible_courante = jointure->cible;
		char* condition_reecrite = malloc(sizeof(char) * (strlen(jointure->condition) + 1));
		char* gauche = strtok(jointure->condition, "=");
		resultat &= verifier_presence_point(gauche);
		char* droite = strtok(NULL, "=");
		resultat &= verifier_presence_point(droite);
		if(resultat) {
			char* cible_gauche = strtok(gauche, ".");
			char* champ_gauche = strtok(NULL, ".");
			char* cible_droite = strtok(droite, ".");
			char* champ_droite = strtok(NULL, ".");
			if(strcmp(cible_courante, cible_droite) != 0)
				inverser = true;
			if(inverser && strcmp(cible_courante, cible_gauche) != 0)
				resultat &= false;
			if(inverser) {
				resultat &= tableau_contient_str(cibles_existantes, cible_droite, i+1);
				sprintf(condition_reecrite, "%s.%s=%s.%s", cible_droite, champ_droite, cible_gauche, champ_gauche);
			} else {
				resultat &= tableau_contient_str(cibles_existantes, cible_gauche, i+1);
				sprintf(condition_reecrite, "%s.%s=%s.%s", cible_gauche, champ_gauche, cible_droite, champ_droite);
			}
		}
		free(jointure->condition);
		jointure->condition = condition_reecrite;
		cibles_existantes[i+1] = cible_courante;
	}
	free(cibles_existantes);
	return resultat;
}

bool verifier_presence_point(char* chaine) {
	bool resultat = NULL != strstr(chaine, ".");
	if(!resultat)
		printf("Erreur : les conditions de jointure doivent être préfixées avec le nom de la cible : %s\n", chaine);
	return resultat;
}

bool tableau_contient_str(char** tableau, char* chaine, int taille_tableau) {
	bool resultat = false;
	for(int i=0; i<taille_tableau; i++) {
		resultat |= strcmp(tableau[i], chaine) == 0;
	}
	if(!resultat)
		printf("Erreur : une condition de jointure porte sur une cible inconnue : %s\n", chaine);
	return resultat;
}
