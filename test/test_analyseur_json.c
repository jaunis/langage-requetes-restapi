#include "../src/types.h"
#include "../src/analyseur_json.h"
#include "../src/dict_utils.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_analyser_json_valide() {
    char json[] = "{\"items\": [{\"champ1\": \"valeur1\", \"champ2\": 2}, {\"champ1\": \"valeur001\", \"champ3\": 3}]}";
    t_resultat* resultat;
    analyser_json(json, resultat);
    CU_ASSERT_EQUAL(2, resultat->taille);
    dict* elt1 = resultat->liste[0];
    CU_ASSERT_STRING_EQUAL("\"valeur1\"", dict_valeur(elt1, "\"champ1\""));
    CU_ASSERT_STRING_EQUAL("2", dict_valeur(elt1, "\"champ2\""));
    dict* elt2 = resultat->liste[1];
    CU_ASSERT_STRING_EQUAL("\"valeur001\"", dict_valeur(elt1, "\"champ1\""));
    CU_ASSERT_STRING_EQUAL("3", dict_valeur(elt1, "\"champ3\""));
}
