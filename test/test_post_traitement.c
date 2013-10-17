/*
 * test_post_traitement.c
 *
 *  Created on: 17 oct. 2013
 *      Author: jean
 */

#include <CUnit/CUnit.h>

void test_appliquer_clause_where() {
	char** clause_where = malloc(7 * sizeof(char*));
	clause_where[0] = "id";
	clause_where[1] = "=";
	clause_where[2] = "1";
	clause_where[3] = "and";
	clause_where[4] = "model";
	clause_where[5] = "=";
	clause_where[6] = "6731i";
	t_condition* condition;
	construire_condition_et_renvoyer_statut(clause_where, 7, condition);
	t_resultat resultat = {
			.taille = 3,
			.liste = malloc(3 * sizeof(dict*))
	};
	dict* dict = initialiser_dict(2);
	dict_inserer_cle_valeur(dict, "id", "1");
	dict_inserer_cle_valeur(dict, "model", "6737i");
	resultat.liste[0] = dict;

	dict = initialiser_dict(2);
	dict_inserer_cle_valeur(dict, "id", "2");
	dict_inserer_cle_valeur(dict, "model", "6731i");
	resultat.liste[1] = dict;

	dict = initialiser_dict(2);
	dict_inserer_cle_valeur(dict, "id", "1");
	dict_inserer_cle_valeur(dict, "model", "6731i");
	resultat.liste[2] = dict;

	appliquer_clause_where(&resultat, condition);

	CU_ASSERT_EQUAL(1, resultat.taille);
	CU_ASSERT_STRING_EQUAL("1", dict_valeur(resultat.liste[0], "id"));
	CU_ASSERT_STRING_EQUAL("6731i", dict_valeur(resultat.liste[0], "model"));
}
