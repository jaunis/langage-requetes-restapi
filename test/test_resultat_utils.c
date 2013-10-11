/*
 * test_resultat_utils.c
 *
 *  Created on: 8 oct. 2013
 *      Author: jean
 */

#include "../src/types.h"
#include "../src/resultat_utils.h"
#include "test_resultat_utils.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>

void test_dict_valeur() {
	t_entree entree1 = {
			.cle = "cle1",
			.valeur = "valeur1"
	};

	t_entree entree2 = {
			.cle = "cle2",
			.valeur = "valeur2"
	};
	t_entree entree3 = {
			.cle = "cle3",
			.valeur = "valeur3"
	};

	t_entree* liste[] = { &entree1, &entree2, &entree3 };
	dict dictionnaire = {
			.entrees = liste,
			.nb_entrees = 3
	};

	CU_ASSERT_STRING_EQUAL("valeur1", dict_valeur(&dictionnaire, "cle1"));
	CU_ASSERT_STRING_EQUAL("valeur2", dict_valeur(&dictionnaire, "cle2"));
	CU_ASSERT_STRING_EQUAL("valeur3", dict_valeur(&dictionnaire, "cle3"));
}

void test_dict_valeur_null() {
	t_entree entree1 = {
			.cle = "cle1",
			.valeur = "valeur1"
	};

	t_entree entree2 = {
			.cle = "cle2",
			.valeur = "valeur2"
	};

	t_entree* liste[] = { &entree1, &entree2 };
	dict dictionnaire = {
			.entrees = liste,
			.nb_entrees = 2
	};

	CU_ASSERT_PTR_NULL(dict_valeur(&dictionnaire, "cle_inexistante"));
}

void test_dict_inserer_cle_valeur() {
	dict* dict = initialiser_dict(1000);
	char* cle = malloc(sizeof(char)*7);
	char* valeur = malloc(sizeof(char)*10);
	for(int i=0; i<10000; i++) {
		sprintf(cle, "cle%d", i);
		sprintf(valeur, "valeur%d", i);
		dict_inserer_cle_valeur(dict, cle, valeur);
	}

	for(int i=0; i<10000; i++) {
		sprintf(cle, "cle%d", i);
		sprintf(valeur, "valeur%d", i);
		CU_ASSERT_STRING_EQUAL(valeur, dict_valeur(dict, cle));
	}
	CU_ASSERT_EQUAL(10000, dict->nb_entrees);
}

void test_dict_inserer_cle_existante() {
	dict* dict = initialiser_dict(3);
	dict_inserer_cle_valeur(dict, "cle1", "valeur1");
	dict_inserer_cle_valeur(dict, "cle2", "valeur2");
	dict_inserer_cle_valeur(dict, "cle3", "valeur3");
	dict_inserer_cle_valeur(dict, "cle2", "nouvelle_valeur2");

	CU_ASSERT_EQUAL(3, dict->nb_entrees);
	CU_ASSERT_STRING_EQUAL("valeur1", dict_valeur(dict, "cle1"));
	CU_ASSERT_STRING_EQUAL("nouvelle_valeur2", dict_valeur(dict, "cle2"));
	CU_ASSERT_STRING_EQUAL("valeur3", dict_valeur(dict, "cle3"));
}

void test_initialiser_dict() {
	dict* dict = initialiser_dict(10);
	CU_ASSERT_EQUAL(10, dict->_taille_allouee);
	CU_ASSERT_PTR_NOT_NULL(dict->entrees);
	CU_ASSERT_EQUAL(0, dict->nb_entrees);
}
