#include "../src/analyseur_requete.h"
#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"
#include <stdbool.h>

void test_diviser_requete_en_lexemes() {
    char requete[] = "select *     from   devices";
    t_requete_lexemes requete_divisee = diviser_requete_en_lexemes(requete);
    CU_ASSERT_STRING_EQUAL("select", requete_divisee.tableau[0]);
    CU_ASSERT_STRING_EQUAL("*", requete_divisee.tableau[1]);
    CU_ASSERT_STRING_EQUAL("from", requete_divisee.tableau[2]);
    CU_ASSERT_STRING_EQUAL("devices", requete_divisee.tableau[3]);
    CU_ASSERT_EQUAL(4, requete_divisee.taille);
}

void test_requete_est_valide_ok() {
    t_requete_lexemes requete;
    requete.tableau = malloc(sizeof(char*)*4);
    requete.tableau[0] = "select";
    requete.tableau[1] = "*";
    requete.tableau[2] = "from";
    requete.tableau[3] = "devices";
    requete.taille = 4;
    CU_ASSERT_EQUAL(true, requete_est_valide(requete));
}

void test_requete_est_valide_ko() {
    t_requete_lexemes requete;
    requete.tableau = malloc(sizeof(char*)*5);
    requete.tableau[0] = "select";
    requete.tableau[1] = "*";
    requete.tableau[2] = "from";
    requete.tableau[3] = "devices";
    requete.tableau[4] = "stuff";
    requete.taille = 5;
    CU_ASSERT_EQUAL(false, requete_est_valide(requete));
    
    
    requete.tableau[0] = "select";
    requete.tableau[1] = "*";
    requete.tableau[2] = "rfom";
    requete.tableau[3] = "devices";
    requete.taille = 4;
    CU_ASSERT_EQUAL(false, requete_est_valide(requete));

    requete.tableau[0] = "select";
    requete.tableau[1] = "*";
    requete.tableau[2] = "from";
    requete.tableau[3] = "";
    requete.taille = 4;
    CU_ASSERT_EQUAL(false, requete_est_valide(requete));
}

int main() {
    CU_initialize_registry();
    CU_pSuite pSuite = pSuite = CU_add_suite("Suite_1", NULL, NULL);
    CU_add_test(pSuite, "test_diviser_requete_en_lexemes", test_diviser_requete_en_lexemes);
    CU_add_test(pSuite, "test_requete_est_valide_ok", test_requete_est_valide_ok);
    CU_add_test(pSuite, "test_requete_est_valide_ko", test_requete_est_valide_ko);
    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_basic_run_tests();
    return CU_get_error();
}
