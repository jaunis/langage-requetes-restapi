#include "../src/analyseur_requete.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdlib.h>

void test_diviser_requete_en_lexemes() {
    char requete[] = "select *     from   devices where id=1";
    t_requete_lexemes requete_divisee = diviser_requete_en_lexemes(requete);
    CU_ASSERT_EQUAL(8, requete_divisee.taille);
    CU_ASSERT_STRING_EQUAL("select", requete_divisee.tableau[0]);
    CU_ASSERT_STRING_EQUAL("*", requete_divisee.tableau[1]);
    CU_ASSERT_STRING_EQUAL("from", requete_divisee.tableau[2]);
    CU_ASSERT_STRING_EQUAL("devices", requete_divisee.tableau[3]);
    CU_ASSERT_STRING_EQUAL("where", requete_divisee.tableau[4]);
    CU_ASSERT_STRING_EQUAL("id", requete_divisee.tableau[5]);
    CU_ASSERT_STRING_EQUAL("=", requete_divisee.tableau[6]);
    CU_ASSERT_STRING_EQUAL("1", requete_divisee.tableau[7]);


    char requete2[] = "select champ1,champ2   ,champ3     from   devices";
	t_requete_lexemes requete_divisee2 = diviser_requete_en_lexemes(requete2);
	CU_ASSERT_EQUAL(8, requete_divisee2.taille);
	CU_ASSERT_STRING_EQUAL("select", requete_divisee2.tableau[0]);
	CU_ASSERT_STRING_EQUAL("champ1", requete_divisee2.tableau[1]);
	CU_ASSERT_STRING_EQUAL(",", requete_divisee2.tableau[2]);
	CU_ASSERT_STRING_EQUAL("champ2", requete_divisee2.tableau[3]);
	CU_ASSERT_STRING_EQUAL(",", requete_divisee2.tableau[4]);
	CU_ASSERT_STRING_EQUAL("champ3", requete_divisee2.tableau[5]);
	CU_ASSERT_STRING_EQUAL("from", requete_divisee2.tableau[6]);
	CU_ASSERT_STRING_EQUAL("devices", requete_divisee2.tableau[7]);
}

void test_construire_requete_etoile_et_renvoyer_statut_ok() {
    t_requete_lexemes lexemes;
    t_requete requete;
    lexemes.tableau = malloc(sizeof(char*)*4);
    lexemes.tableau[0] = "select";
    lexemes.tableau[1] = "*";
    lexemes.tableau[2] = "from";
    lexemes.tableau[3] = "devices";
    lexemes.taille = 4;
    CU_ASSERT_EQUAL(true, construire_requete_et_renvoyer_statut(lexemes, &requete));
    CU_ASSERT_STRING_EQUAL("devices", requete.cible);
    CU_ASSERT_EQUAL(1, requete.projection.taille);
    CU_ASSERT_STRING_EQUAL("*", requete.projection.champs[0]);
}

void test_construire_requete_selection_et_renvoyer_statut_ok() {
    t_requete_lexemes lexemes;
    t_requete requete;
    lexemes.tableau = malloc(sizeof(char*)*8);
    lexemes.tableau[0] = "select";
    lexemes.tableau[1] = "champ1";
    lexemes.tableau[2] = ",";
    lexemes.tableau[3] = "champ2";
    lexemes.tableau[4] = ",";
    lexemes.tableau[5] = "champ3";
    lexemes.tableau[6] = "from";
    lexemes.tableau[7] = "devices";
    lexemes.taille = 8;
    CU_ASSERT_EQUAL(true, construire_requete_et_renvoyer_statut(lexemes, &requete));
    CU_ASSERT_STRING_EQUAL("devices", requete.cible);
    CU_ASSERT_EQUAL(3, requete.projection.taille);
    CU_ASSERT_STRING_EQUAL("champ1", requete.projection.champs[0]);
    CU_ASSERT_STRING_EQUAL("champ2", requete.projection.champs[1]);
    CU_ASSERT_STRING_EQUAL("champ3", requete.projection.champs[2]);
}

void test_construire_requete_et_renvoyer_statut_ko() {
    t_requete_lexemes lexemes;
    t_requete requete;
    lexemes.tableau = malloc(sizeof(char*)*5);
    lexemes.tableau[0] = "select";
    lexemes.tableau[1] = "*";
    lexemes.tableau[2] = "from";
    lexemes.tableau[3] = "devices";
    lexemes.tableau[4] = "stuff";
    lexemes.taille = 5;
    CU_ASSERT_EQUAL(false, construire_requete_et_renvoyer_statut(lexemes, &requete));
    
    
    lexemes.tableau[0] = "select";
    lexemes.tableau[1] = "*";
    lexemes.tableau[2] = "rfom";
    lexemes.tableau[3] = "devices";
    lexemes.taille = 4;
    CU_ASSERT_EQUAL(false, construire_requete_et_renvoyer_statut(lexemes, &requete));

    lexemes.tableau[0] = "select";
    lexemes.tableau[1] = "*";
    lexemes.tableau[2] = "from";
    lexemes.tableau[3] = "";
    lexemes.taille = 4;
    CU_ASSERT_EQUAL(false, construire_requete_et_renvoyer_statut(lexemes, &requete));

	free(lexemes.tableau);
    lexemes.tableau = malloc(sizeof(char*)*7);
	lexemes.tableau[0] = "select";
	lexemes.tableau[1] = "champ1";
	lexemes.tableau[2] = ",";
	lexemes.tableau[3] = ",";
	lexemes.tableau[4] = "champ3";
	lexemes.tableau[5] = "from";
	lexemes.tableau[6] = "devices";
	lexemes.taille = 7;
	CU_ASSERT_EQUAL(false, construire_requete_et_renvoyer_statut(lexemes, &requete));
}

