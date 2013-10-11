#include "../src/types.h"
#include "../src/analyseur_json.h"
#include "../src/resultat_utils.h"
#include "test_analyseur_json.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>

void test_analyser_json_valide() {
    char json[] = "{\"items\": [{\"champ1\": \"valeur1\", \"champ2\": 2}, {\"champ1\": \"valeur001\", \"champ3\": 3}]}";
    t_resultat* resultat = malloc(sizeof(t_resultat));

    CU_ASSERT_TRUE(analyser_json(json, resultat));

    CU_ASSERT_EQUAL(2, resultat->taille);
    dict* elt1 = resultat->liste[0];
    CU_ASSERT_STRING_EQUAL("valeur1", dict_valeur(elt1, "champ1"));
    CU_ASSERT_STRING_EQUAL("2", dict_valeur(elt1, "champ2"));
    dict* elt2 = resultat->liste[1];
    CU_ASSERT_STRING_EQUAL("valeur001", dict_valeur(elt2, "champ1"));
    CU_ASSERT_STRING_EQUAL("3", dict_valeur(elt2, "champ3"));
}

void test_analyser_json_invalide() {
    char json[] = "[{\"champ1\": \"valeur1\", \"champ2\": 2}, {\"champ1\": \"valeur001\", \"champ3\": 3}]";
    t_resultat* resultat = malloc(sizeof(t_resultat));
    CU_ASSERT_FALSE(analyser_json(json, resultat));

    char json2[] = "{\"truc\": [{\"champ1\": \"valeur1\", \"champ2\": 2}, {\"champ1\": \"valeur001\", \"champ3\": 3}]}";
	CU_ASSERT_FALSE(analyser_json(json2, resultat));

	char json3[] = "{\"items\": {\"champ1\": \"valeur1\", \"champ2\": 2}}";
	CU_ASSERT_FALSE(analyser_json(json3, resultat));
}
