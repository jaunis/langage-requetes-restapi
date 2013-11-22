/*
 * test_analyseur-lexical.c
 *
 *  Created on: 22 nov. 2013
 *      Author: jean
 */

#include "../src/analyseur_lexical.h"
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
