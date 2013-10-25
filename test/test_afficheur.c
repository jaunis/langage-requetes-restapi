/*
 * test_afficheur.c
 *
 *  Created on: 10 oct. 2013
 *      Author: jean
 */

#include "test_afficheur.h"
#include "mocks.h"
#include "../src/types.h"
#include "../src/utils/dict_utils.h"
#include "../src/afficheur.h"
#include <CUnit/CUnit.h>
#include <stdlib.h>

void test_afficher_resultat_complet() {
	char** champs = malloc(sizeof(char*));
	champs[0] = "*";
	t_projection projection = {
			.taille = 1,
			.champs = champs
	};
	t_resultat* resultat = malloc(sizeof(t_resultat));
	dict** liste = malloc(sizeof(dict*) * 2);
	dict* elt1 = initialiser_dict(2);
	dict_inserer_cle_valeur(elt1, "cle1", "valeur1");
	dict_inserer_cle_valeur(elt1, "cle2", "valeur2");
	dict* elt2 = initialiser_dict(2);
	dict_inserer_cle_valeur(elt2, "cle1", "valeur01");
	dict_inserer_cle_valeur(elt2, "cle3", "valeur03");
	liste[0] = elt1;
	liste[1] = elt2;
	resultat->liste = liste;
	resultat->taille = 2;
	SORTIE_STDOUT[0] = '\0';

	afficher_resultat(resultat, &projection);

	char* sortie_attendue = "cle1,cle2,cle3\nvaleur1,valeur2,\nvaleur01,,valeur03\n";
	CU_ASSERT_STRING_EQUAL(sortie_attendue, SORTIE_STDOUT);

	free(resultat);
	free(liste);
	free(elt1);
	free(elt2);
}

void test_afficher_resultat_partiel() {
	char** champs = malloc(sizeof(char*) * 2);
	champs[0] = "cle1";
	champs[1] = "cle3";
	t_projection projection = {
			.taille = 2,
			.champs = champs
	};
	t_resultat* resultat = malloc(sizeof(t_resultat));
	dict** liste = malloc(sizeof(dict*) * 2);
	dict* elt1 = initialiser_dict(2);
	dict_inserer_cle_valeur(elt1, "cle1", "valeur1");
	dict_inserer_cle_valeur(elt1, "cle2", "valeur2");
	dict* elt2 = initialiser_dict(2);
	dict_inserer_cle_valeur(elt2, "cle1", "valeur01");
	dict_inserer_cle_valeur(elt2, "cle3", "valeur03");
	liste[0] = elt1;
	liste[1] = elt2;
	resultat->liste = liste;
	resultat->taille = 2;
	SORTIE_STDOUT[0] = '\0';

	afficher_resultat(resultat, &projection);

	char* sortie_attendue = "cle1,cle3\nvaleur1,\nvaleur01,valeur03\n";
	CU_ASSERT_STRING_EQUAL(sortie_attendue, SORTIE_STDOUT);

	free(resultat);
	free(liste);
	free(elt1);
	free(elt2);
}
