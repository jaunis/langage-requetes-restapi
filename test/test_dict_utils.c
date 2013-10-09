/*
 * test_dict_utils.c
 *
 *  Created on: 8 oct. 2013
 *      Author: jean
 */

#include "../src/types.h"
#include "test_dict_utils.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_dict_valeur() {
	entree entree1 = {
			.cle = "cle1",
			.valeur = "valeur1"
	};

	entree entree2 = {
			.cle = "cle2",
			.valeur = "valeur2"
	};
	entree entree3 = {
			.cle = "cle3",
			.valeur = "valeur3"
	};

	entree* liste[] = { &entree1, &entree2, &entree3 };
	dict dictionnaire = {
			.entrees = liste,
			.nb_entrees = 3
	};

	CU_ASSERT_STRING_EQUAL("valeur1", dict_valeur(&dictionnaire, "cle1"));
	CU_ASSERT_STRING_EQUAL("valeur2", dict_valeur(&dictionnaire, "cle2"));
	CU_ASSERT_STRING_EQUAL("valeur3", dict_valeur(&dictionnaire, "cle3"));
}

void test_dict_valeur_null() {
	entree entree1 = {
			.cle = "cle1",
			.valeur = "valeur1"
	};

	entree entree2 = {
			.cle = "cle2",
			.valeur = "valeur2"
	};

	entree* liste[] = { &entree1, &entree2 };
	dict dictionnaire = {
			.entrees = liste,
			.nb_entrees = 2
	};

	CU_ASSERT_PTR_NULL(dict_valeur(&dictionnaire, "cle_inexistante"));
}

void test_dict_ajouter_cle_valeur() {
	CU_FAIL("Non implémenté");
}

void test_initialiser_dict() {
	CU_FAIL("Non implémenté");
}
