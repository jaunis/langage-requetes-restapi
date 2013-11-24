/*
 * configuration.c
 *
 *  Created on: 24 nov. 2013
 *      Author: jean
 */

#include "configuration.h"
#include "executeur_requete.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void charger_configuration(char* nom_fichier) {
	printf("Chargement de la config.\n");
	FILE* fichier = fopen(nom_fichier, "r");
	if(!fichier)
		return;
	char ligne[100];
	int nb_lus = fread(ligne, sizeof(char), 100, fichier);
	if(nb_lus > 0 && verifier_contient_egal(ligne)) {
		ligne[nb_lus] = '\0';
		char* param = strtok(ligne, "=");
		char* valeur = strtok(NULL, "=");
		rstrip(valeur);
		REST_API_URL = malloc(sizeof(char) * (strlen(valeur) + 5));
		sprintf(REST_API_URL, "%s/1.1", valeur);
	}
	fclose(fichier);
	printf("rest api url : %s\n", REST_API_URL);
}

bool verifier_contient_egal(char* chaine) {
	return strstr(chaine, "=") != NULL;
}

void rstrip(char* chaine) {
	for (int i=0, j=0; chaine[j]=chaine[i]; j+=!isspace(chaine[i++]));
}
