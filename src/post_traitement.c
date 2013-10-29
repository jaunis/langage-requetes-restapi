/*
 * post_traitement.c
 *
 *  Created on: 18 oct. 2013
 *      Author: jean
 */

#include "post_traitement.h"
#include <stdlib.h>
#include <string.h>
#include "utils/dict_utils.h"

void appliquer_clause_where(t_resultat* resultat, t_condition* condition) {
	if(condition->valeur == NULL)
		return;
	dict** ancienne_liste = resultat->liste;
	dict** nouvelle_liste = malloc(resultat->taille * sizeof(dict*));
	int nouvelle_taille = 0;
	for(int i = 0; i < resultat->taille; i++) {
		dict* element = resultat->liste[i];
		if(element_verifie_condition(element, condition)) {
			nouvelle_liste[nouvelle_taille] = element;
			nouvelle_taille++;
		} else {
			free_dict(element);
		}
	}
	free(ancienne_liste);
	resultat->liste = nouvelle_liste;
	resultat->taille = nouvelle_taille;
}

bool element_verifie_condition(dict* element, t_condition* condition) {
	if(strcmp("or", condition->valeur) == 0) {
		return element_verifie_condition(element, condition->fils_gauche) ||
				element_verifie_condition(element, condition->fils_droit);
	} else if(strcmp("and", condition->valeur) == 0) {
		return element_verifie_condition(element, condition->fils_gauche) &&
						element_verifie_condition(element, condition->fils_droit);
	} else {
		return element_passe_test(element, condition->valeur);
	}
}

bool element_passe_test(dict* element, char* test) {
	char* test_recopie = malloc((strlen(test) + 1) * sizeof(char));
	strcpy(test_recopie, test);
	char* champ = strtok(test_recopie, "=");
	if(!dict_contient_champ(element, champ))
		return false;
	char* valeur_attendue = strtok(NULL, "=");
	char* valeur = dict_valeur(element, champ);
	return strcmp(valeur_attendue, valeur) == 0;
}

t_resultat* appliquer_jointures(t_resultats* resultats, t_requete requete) {
	t_resultat* partie_gauche = &(resultats->resultats[0]);
	for(int i = 0; i < requete.jointures.nb_jointures; i++) {
		t_resultat* partie_droite = &(resultats->resultats[i + 1]);
		partie_gauche = fusionner_resultats(partie_gauche, partie_droite, requete.jointures.liste[i]);
	}
	return partie_gauche;
}

t_resultat* fusionner_resultats(t_resultat* partie_gauche, t_resultat* partie_droite, t_jointure jointure) {
	t_resultat* resultat_jointure = malloc(sizeof(t_resultat));
	resultat_jointure->taille = partie_gauche->taille * partie_droite->taille;
	resultat_jointure->liste = malloc(resultat_jointure->taille * sizeof(dict*));
	int taille_reelle = 0;
	for(int i = 0; i < partie_gauche->taille; i++) {
		dict* ligne_gauche = partie_gauche->liste[i];
		for(int j = 0; j < partie_droite->taille; j++) {
			dict* ligne_droite = partie_droite->liste[j];
			if(condition_jointure_verifiee(ligne_gauche, ligne_droite, jointure.condition)) {
				fusionner_dicts(ligne_gauche, ligne_droite);
				resultat_jointure->liste[taille_reelle] = ligne_gauche;
				taille_reelle++;
			}
		}
	}
	resultat_jointure->taille = taille_reelle;
	resultat_jointure->liste = realloc(resultat_jointure->liste, taille_reelle * sizeof(dict*));
	return resultat_jointure;
}

bool condition_jointure_verifiee(dict* partie_gauche, dict* partie_droite, char* condition) {
	char* temp_condition = malloc(sizeof(char) * (strlen(condition) + 1));
	strcpy(temp_condition, condition);
	char* champ_gauche = strtok(temp_condition, "=");
	char* champ_droit = strtok(NULL, "=");

	char* valeur_gauche = dict_valeur(partie_gauche, champ_gauche);
	char* valeur_droite = dict_valeur(partie_droite, champ_droit);
	if(valeur_gauche == NULL || valeur_droite == NULL)
		return false;
	return strcmp(valeur_droite, valeur_gauche) == 0;
}
