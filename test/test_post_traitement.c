/*
 * test_post_traitement.c
 *
 *  Created on: 17 oct. 2013
 *      Author: jean
 */

#include "test_post_traitement.h"
#include <CUnit/CUnit.h>
#include <stdlib.h>
#include "../src/types.h"
#include "../src/analyseur_syntaxique.h"
#include "../src/utils/dict_utils.h"
#include "../src/post_traitement.h"

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

void test_element_verifie_condition() {
	dict* element_vrai = initialiser_dict(2);
	dict_inserer_cle_valeur(element_vrai, "id", "1");
	dict_inserer_cle_valeur(element_vrai, "model", "6731i");

	dict* element_faux = initialiser_dict(2);
	dict_inserer_cle_valeur(element_faux, "id", "2");
	dict_inserer_cle_valeur(element_faux, "model", "6737i");

	dict* element_champ_manquant = initialiser_dict(2);
	dict_inserer_cle_valeur(element_champ_manquant, "model", "6755i");

	t_condition* condition = initialiser_condition("or");
	condition->fils_gauche = initialiser_condition("id=1");
	condition->fils_droit = initialiser_condition("model=6755i");

	CU_ASSERT_EQUAL(true, element_verifie_condition(element_vrai, condition));
	CU_ASSERT_EQUAL(false, element_verifie_condition(element_faux, condition));
	CU_ASSERT_EQUAL(true, element_verifie_condition(element_champ_manquant, condition));
}

void test_appliquer_jointures() {
	char* condition = "devices.id=ref_devices.device_id";
	t_jointure jointure = {
			.cible = "ref_devices",
			.condition = malloc((strlen(condition) + 1) * sizeof(char))
	};
	strcpy(jointure.condition, condition);
	t_jointures jointures = {
			.nb_jointures = 1,
			.jointures = malloc(sizeof(t_jointure))
	};

	t_requete requete = {
			.cible = "devices",
			.jointures = jointures
	};
	jointures.jointures[0] = jointure;

	t_resultat devices = {
			.taille = 3,
			.liste = malloc(3 * sizeof(dict*))
	};
	dict* dev = initialiser_dict(2);
	dict_inserer_cle_valeur(dev, "devices.id", "1");
	dict_inserer_cle_valeur(dev, "devices.model", "6737i");
	devices.liste[0] = dev;

	dev = initialiser_dict(2);
	dict_inserer_cle_valeur(dev, "devices.id", "2");
	dict_inserer_cle_valeur(dev, "devices.model", "6731i");
	devices.liste[1] = dev;

	dev = initialiser_dict(2);
	dict_inserer_cle_valeur(dev, "devices.id", "3");
	dict_inserer_cle_valeur(dev, "devices.model", "6731i");
	devices.liste[2] = dev;

	t_resultat ref_devices = {
			.liste = malloc(2 * sizeof(dict*)),
			.taille = 2
	};
	dict* ref = initialiser_dict(2);
	dict_inserer_cle_valeur(ref, "ref_devices.id", "71");
	dict_inserer_cle_valeur(ref, "ref_devices.device_id", "1");
	ref_devices.liste[0] = ref;

	ref = initialiser_dict(2);
	dict_inserer_cle_valeur(ref, "ref_devices.id", "72");
	dict_inserer_cle_valeur(ref, "ref_devices.device_id", "2");
	ref_devices.liste[1] = ref;

	t_resultats resultats = {
			.taille = 2,
			.resultats = malloc(2 * sizeof(t_resultat))
	};
	resultats.resultats[0] = devices;
	resultats.resultats[1] = ref_devices;

	t_resultat* resultat_jointure = appliquer_jointures(&resultats, requete);

	CU_ASSERT_EQUAL(2, resultat_jointure->taille);
	dict* premier = resultat_jointure->liste[0];
	CU_ASSERT_STRING_EQUAL("1", dict_valeur(premier, "devices.id"));
	CU_ASSERT_STRING_EQUAL("71", dict_valeur(premier, "ref_devices.id"));
	dict* deuxieme = resultat_jointure->liste[1];
	CU_ASSERT_STRING_EQUAL("2", dict_valeur(deuxieme, "devices.id"));
	CU_ASSERT_STRING_EQUAL("72", dict_valeur(deuxieme, "ref_devices.id"));
}
