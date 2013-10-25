/*
 * afficheur.c
 *
 *  Created on: 10 oct. 2013
 *      Author: jean
 */

#include "afficheur.h"
#include "utils/dict_utils.h"
#include <string.h>
#include <stdlib.h>
#ifndef CUNIT
#include <stdio.h>
#else
#include "../test/mocks.h"
#endif

void afficher_resultat(t_resultat* resultat, t_projection* projection) {
	t_en_tete en_tete = creer_en_tete(resultat, projection);
	afficher_en_tete(en_tete);
	afficher_lignes(resultat, en_tete);
	desallouer_en_tete(en_tete);
}

t_en_tete creer_en_tete(t_resultat* resultat, t_projection* projection) {
	t_en_tete en_tete = {
			.colonnes = NULL,
			.taille = 0
	};
	for(int i=0; i<projection->taille; i++) {
		if(strcmp("*", projection->champs[i]) == 0) {
			t_en_tete en_tete_etoile = extraire_en_tete(resultat);
			t_en_tete nouvel_en_tete = concatener_en_tetes(en_tete, en_tete_etoile);
			free(en_tete.colonnes);
			free(en_tete_etoile.colonnes);
			en_tete = nouvel_en_tete;
		} else {
			incrementer_taille_en_tete(&en_tete);
			ajouter_colonne(&en_tete, projection->champs[i]);
		}
	}
	return en_tete;
}

t_en_tete concatener_en_tetes(t_en_tete gauche, t_en_tete droit) {
	t_en_tete resultat = {
			.colonnes = malloc((gauche.taille + droit.taille) * sizeof(char*)),
			.taille = gauche.taille + droit.taille
	};
	if(gauche.taille > 0)
		memcpy(resultat.colonnes, gauche.colonnes, gauche.taille * sizeof(char*));
	if(droit.taille > 0)
		memcpy(&(resultat.colonnes[gauche.taille]), droit.colonnes, droit.taille * sizeof(char*));
	return resultat;
}

t_en_tete extraire_en_tete(t_resultat* resultat) {
	t_en_tete en_tete = {
			.colonnes = NULL,
			.taille = 0
	};
	for(int i=0; i<resultat->taille; i++) {
		dict* entree = resultat->liste[i];
		for(int j=0; j<entree->nb_entrees; j++) {
			char* cle = entree->entrees[j]->cle;
			if(!en_tete_contient(en_tete, cle)) {
				incrementer_taille_en_tete(&en_tete);
				ajouter_colonne(&en_tete, cle);
			}
		}
	}
	return en_tete;
}

void afficher_en_tete(t_en_tete en_tete) {
	int taille_totale = 0;
	for(int i=0; i<en_tete.taille; i++) {
		taille_totale += strlen(en_tete.colonnes[i]) + 1;
	}
	taille_totale++;
	char* ligne = malloc(taille_totale * sizeof(char));
	ligne[0] = '\0';
	for(int i=0; i<en_tete.taille; i++) {
		strcat(ligne, en_tete.colonnes[i]);
		if(i != en_tete.taille - 1)
			strcat(ligne, ",");
	}
	strcat(ligne, "\n");
	printf(ligne);
	free(ligne);
}

void afficher_lignes(t_resultat* resultat, t_en_tete en_tete) {
	for(int i=0; i<resultat->taille; i++) {
		dict* dict = resultat->liste[i];
		int taille_ligne = determiner_taille_ligne(dict, en_tete);
		char* ligne = malloc(taille_ligne * sizeof(char));
		remplir_ligne_avec_dict(ligne, dict, en_tete);
		printf(ligne);
		free(ligne);
	}
}

int determiner_taille_ligne(dict* dict, t_en_tete en_tete) {
	int taille_ligne = 0;
	for(int j=0; j<en_tete.taille; j++) {
		char* valeur = dict_valeur(dict, en_tete.colonnes[j]);
		if(valeur != NULL)
			taille_ligne += strlen(valeur);
		taille_ligne++;
	}
	return taille_ligne + 1;
}

void remplir_ligne_avec_dict(char* ligne, dict* dict, t_en_tete en_tete) {
	ligne[0] = '\0';
	for(int j=0; j<en_tete.taille; j++) {
		char* valeur = dict_valeur(dict, en_tete.colonnes[j]);
		if(valeur != NULL)
			strcat(ligne, valeur);
		if(j != en_tete.taille - 1)
			strcat(ligne, ",");
	}
	strcat(ligne, "\n");
}

void incrementer_taille_en_tete(t_en_tete* en_tete) {
	en_tete->taille++;
	en_tete->colonnes = realloc(en_tete->colonnes, (en_tete->taille) * sizeof(char*));
}

void ajouter_colonne(t_en_tete* en_tete, char* valeur) {
	int position = en_tete->taille - 1;
	en_tete->colonnes[position] = malloc((strlen(valeur) + 1) * sizeof(char));
	strcpy(en_tete->colonnes[position], valeur);
}

bool en_tete_contient(t_en_tete en_tete, char* valeur) {
	for(int i=0; i< en_tete.taille; i++) {
		if(strcmp(en_tete.colonnes[i], valeur) == 0)
			return true;
	}
	return false;
}

void desallouer_en_tete(t_en_tete en_tete) {
	for(int i=0; i<en_tete.taille; i++) {
		free(en_tete.colonnes[i]);
	}
	free(en_tete.colonnes);
}
