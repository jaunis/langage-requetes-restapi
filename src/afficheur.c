/*
 * afficheur.c
 *
 *  Created on: 10 oct. 2013
 *      Author: jean
 */

#include "afficheur.h"
#include "resultat_utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void afficher_resultat(t_resultat* resultat) {
	int taille_en_tete;
	char** en_tete = extraire_en_tete(resultat, &taille_en_tete);
	afficher_en_tete(en_tete, taille_en_tete);
	afficher_lignes(resultat, en_tete, taille_en_tete);
	desallouer_en_tete(en_tete, taille_en_tete);
}

char** extraire_en_tete(t_resultat* resultat, int* taille_en_tete) {
	dict* entree = resultat->liste[0];
	char** en_tete = malloc(entree->nb_entrees * sizeof(char*));
	for(int i=0; i<entree->nb_entrees; i++) {
		char* cle = entree->entrees[i]->cle;
		en_tete[i] = malloc(strlen(cle) * sizeof(char));
		strcpy(en_tete[i], cle);
	}
	*taille_en_tete = entree->nb_entrees;
	return en_tete;
}

void afficher_en_tete(char** en_tete, int taille_en_tete) {
	int taille_totale = 0;
	for(int i=0; i<taille_en_tete; i++) {
		taille_totale += strlen(en_tete[i]) + 1;
	}
	char* ligne = malloc(taille_totale * sizeof(char));
	ligne[0] = '\0';
	for(int i=0; i<taille_en_tete; i++) {
		strcat(ligne, en_tete[i]);
		if(i != taille_en_tete - 1)
			strcat(ligne, ",");
	}
	printf("%s\n", ligne);
	free(ligne);
}

void afficher_lignes(t_resultat* resultat, char** en_tete, int taille_en_tete) {
	for(int i=0; i<resultat->taille; i++) {
		dict* dict = resultat->liste[i];
		int taille_ligne = 0;
		for(int j=0; j<taille_en_tete; j++) {
			char* valeur = dict_valeur(dict, en_tete[j]);
			if(valeur != NULL)
				taille_ligne += strlen(valeur);
			taille_ligne++;
		}
		char* ligne = malloc(taille_ligne * sizeof(char));
		ligne[0] = '\0';
		for(int j=0; j<taille_en_tete; j++) {
			char* valeur = dict_valeur(dict, en_tete[j]);
			if(valeur != NULL)
				strcat(ligne, valeur);
			if(j != taille_en_tete - 1)
				strcat(ligne, ",");
		}
		printf("%s\n", ligne);
		free(ligne);
	}
}

void desallouer_en_tete(char** en_tete, int taille_en_tete) {
	for(int i=0; i<taille_en_tete; i++) {
		free(en_tete[i]);
	}
	free(en_tete);
}
