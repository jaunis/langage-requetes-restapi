#include "../src/types.h"
#include "../src/analyseur_json.h"
#include "../src/utils/dict_utils.h"
#include "test_analyseur_json.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>

void test_analyser_json_valide() {
    char json[] = "{\"items\": [{\"champ1\": \"valeur1\", \"champ2\": 2}, {\"champ1\": \"valeur001\", \"champ3\": 3, \"champ4\": null}]}";
    t_resultat resultat = {
			.taille = 0,
			.liste = NULL
	};
    char* param = malloc((strlen(json) + 1) * sizeof(char));
    strcpy(param, json);

    CU_ASSERT_TRUE(analyser_json(param, &resultat, "pref."));

    CU_ASSERT_EQUAL(2, resultat.taille);
    dict* elt1 = resultat.liste[0];
    CU_ASSERT_STRING_EQUAL("valeur1", dict_valeur(elt1, "pref.champ1"));
    CU_ASSERT_STRING_EQUAL("2", dict_valeur(elt1, "pref.champ2"));
    dict* elt2 = resultat.liste[1];
    CU_ASSERT_STRING_EQUAL("valeur001", dict_valeur(elt2, "pref.champ1"));
    CU_ASSERT_STRING_EQUAL("3", dict_valeur(elt2, "pref.champ3"));
    free(param);
    for(int i=0; i<resultat.taille; i++) {
    	free_dict(resultat.liste[i]);
    }
    free(resultat.liste);
}

void test_analyser_json_invalide() {
    char json[] = "[{\"champ1\": \"valeur1\", \"champ2\": 2}, {\"champ1\": \"valeur001\", \"champ3\": 3}]";
    char* param = malloc((strlen(json) + 1) * sizeof(char));
    strcpy(param, json);
    t_resultat resultat = {
    		.taille = 0,
    		.liste = NULL
    };
    CU_ASSERT_FALSE(analyser_json(param, &resultat, ""));
    free(param);

    char json2[] = "{\"truc\": [{\"champ1\": \"valeur1\", \"champ2\": 2}, {\"champ1\": \"valeur001\", \"champ3\": 3}]}";
    char* param2 = malloc((strlen(json2) + 1) * sizeof(char));
    strcpy(param2, json2);
	CU_ASSERT_FALSE(analyser_json(param2, &resultat, ""));
	free(param2);

	char json3[] = "{\"items\": {\"champ1\": \"valeur1\", \"champ2\": 2}}";
	char* param3 = malloc((strlen(json3) + 1) * sizeof(char));
	strcpy(param3, json3);
	CU_ASSERT_FALSE(analyser_json(param3, &resultat, ""));
	free(param3);
}
