#include "../src/analyseur_requete.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdlib.h>

void test_diviser_requete_en_lexemes() {
    char requete[] = "select *     from   devices";
    t_requete_lexemes requete_divisee = diviser_requete_en_lexemes(requete);
    CU_ASSERT_STRING_EQUAL("select", requete_divisee.tableau[0]);
    CU_ASSERT_STRING_EQUAL("*", requete_divisee.tableau[1]);
    CU_ASSERT_STRING_EQUAL("from", requete_divisee.tableau[2]);
    CU_ASSERT_STRING_EQUAL("devices", requete_divisee.tableau[3]);
    CU_ASSERT_EQUAL(4, requete_divisee.taille);
}

void test_construire_requete_et_renvoyer_statut_ok() {
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
}

