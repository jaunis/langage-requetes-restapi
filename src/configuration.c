/*
 * configuration.c
 *
 *  Created on: 24 nov. 2013
 *      Author: jean
 */

#include "configuration.h"
#include "executeur_requete.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void charger_configuration(char* nom_fichier) {
	FILE* fichier = fopen(nom_fichier, "r");
	if(!fichier)
		return;
	char ligne[1000];
	while(fscanf(fichier, "%s\n", ligne) == 1) {
		if(verifier_contient_egal(ligne)) {
			char* cle = strtok(ligne, "=");
			char* valeur = strtok(NULL, "=");
			traiter_cle_valeur(cle, valeur);
		}
	}
	fclose(fichier);
}

bool verifier_contient_egal(char* chaine) {
	return strstr(chaine, "=") != NULL;
}

void traiter_cle_valeur(char* cle, char* valeur) {
	if(strcmp(cle, "base_url") == 0) {
		REST_API_URL = malloc(sizeof(char) * (strlen(valeur) + 5));
		sprintf(REST_API_URL, "%s/1.1", valeur);
	} else if(strcmp(cle, "utilisateur") == 0) {
		UTILISATEUR = malloc((strlen(valeur) + 1) * sizeof(char));
		strcpy(UTILISATEUR, valeur);
	} else if(strcmp(cle, "mdp") == 0) {
		MOT_DE_PASSE = malloc((strlen(valeur) + 1) * sizeof(char));
		strcpy(MOT_DE_PASSE, valeur);
	} else {
		printf("Paramètre inconnu : %s\n", cle);
	}
}
