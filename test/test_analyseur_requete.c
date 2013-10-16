#include "../src/analyseur_requete.h"
#include "../src/liste_str_utils.h"
#include "../src/pile_int_utils.h"
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

void test_construire_condition_et_renvoyer_statut_ok () {
	char** clause_where = malloc(7 * sizeof(char*));
	clause_where[0] = "id";
	clause_where[1] = "=";
	clause_where[2] = "1";
	clause_where[3] = "and";
	clause_where[4] = "model";
	clause_where[5] = "=";
	clause_where[6] = "6731i";
	t_condition* condition = malloc(sizeof(t_condition));

	CU_ASSERT_EQUAL(true, construire_condition_et_renvoyer_statut(clause_where, 3, condition));

	CU_ASSERT_STRING_EQUAL("and", condition->valeur);
	CU_ASSERT_EQUAL(operateur, condition->type);
	t_condition* f_gauche = condition->fils_gauche;
	CU_ASSERT_STRING_EQUAL("id=1", f_gauche->valeur);
	CU_ASSERT_EQUAL(operande, f_gauche->type);
	t_condition* f_droit = condition->fils_droit;
	CU_ASSERT_STRING_EQUAL("model=6731i", f_droit->valeur);
	CU_ASSERT_EQUAL(operande, f_droit->type);
}

void test_prefixer_expression() {
	char** clause_where = malloc(9 * sizeof(char*));
	clause_where[0] = "(";
	clause_where[1] = "(";
	clause_where[2] = "id=1";;
	clause_where[3] = "and";
	clause_where[4] = "model=6731i";
	clause_where[5] = ")";
	clause_where[6] = "or";
	clause_where[7] = "model=6737i";
	clause_where[8] = ")";

	t_liste_str* resultat = prefixer_expression(clause_where, 9);

	CU_ASSERT_STRING_EQUAL("or", resultat->valeur);
	CU_ASSERT_STRING_EQUAL("and", resultat->suivant->valeur);
	CU_ASSERT_STRING_EQUAL("id=1", resultat->suivant->suivant->valeur);
	CU_ASSERT_STRING_EQUAL("model=6731i", resultat->suivant->suivant->suivant->valeur);
	CU_ASSERT_STRING_EQUAL("model=6737i", resultat->suivant->suivant->suivant->suivant->valeur);
	CU_ASSERT_PTR_NULL(resultat->suivant->suivant->suivant->suivant->suivant);

	clause_where[0] = "(";
	clause_where[1] = "id=1";
	clause_where[2] = "and";;
	clause_where[3] = "(";
	clause_where[4] = "model=6731i";
	clause_where[5] = "or";
	clause_where[6] = "model=6737i";
	clause_where[7] = ")";
	clause_where[8] = ")";

	resultat = prefixer_expression(clause_where, 9);

	CU_ASSERT_STRING_EQUAL("and", resultat->valeur);
	CU_ASSERT_STRING_EQUAL("id=1", resultat->suivant->valeur);
	CU_ASSERT_STRING_EQUAL("or", resultat->suivant->suivant->valeur);
	CU_ASSERT_STRING_EQUAL("model=6731i", resultat->suivant->suivant->suivant->valeur);
	CU_ASSERT_STRING_EQUAL("model=6737i", resultat->suivant->suivant->suivant->suivant->valeur);
	CU_ASSERT_PTR_NULL(resultat->suivant->suivant->suivant->suivant->suivant);

	clause_where = realloc(clause_where, 13*sizeof(char*));

	clause_where[0] = "(";
	clause_where[1] = "(";
	clause_where[2] = "id=1";
	clause_where[3] = "and";;
	clause_where[4] = "model=6731i";
	clause_where[5] = ")";
	clause_where[6] = "or";
	clause_where[7] = "(";
	clause_where[8] = "id=2";
	clause_where[9] = "and";
	clause_where[10] = "model=6737i";
	clause_where[11] = ")";
	clause_where[12] = ")";

	resultat = prefixer_expression(clause_where, 13);

	CU_ASSERT_STRING_EQUAL("or", resultat->valeur);
	CU_ASSERT_STRING_EQUAL("and", resultat->suivant->valeur);
	CU_ASSERT_STRING_EQUAL("id=1", resultat->suivant->suivant->valeur);
	CU_ASSERT_STRING_EQUAL("model=6731i", resultat->suivant->suivant->suivant->valeur);
	CU_ASSERT_STRING_EQUAL("and", resultat->suivant->suivant->suivant->suivant->valeur);
	CU_ASSERT_STRING_EQUAL("id=2", resultat->suivant->suivant->suivant->suivant->suivant->valeur);
	CU_ASSERT_STRING_EQUAL("model=6737i", resultat->suivant->suivant->suivant->suivant->suivant->suivant->valeur);
	CU_ASSERT_PTR_NULL(resultat->suivant->suivant->suivant->suivant->suivant->suivant->suivant);
}

void test_transformer_expression_prefixee_en_arbre() {
	//and id=1 or id=2 model=6731i
	t_liste_str* liste = initialiser_liste_str();
	liste_str_inserer(&liste, "and", 0);
	liste_str_inserer(&liste, "id=1", 1);
	liste_str_inserer(&liste, "or", 2);
	liste_str_inserer(&liste, "id=2", 3);
	liste_str_inserer(&liste, "model=6731i", 4);

	t_condition* resultat = transformer_expression_prefixee_en_arbre(liste);

	CU_ASSERT_STRING_EQUAL("and", resultat->valeur);
	CU_ASSERT_STRING_EQUAL("id=1", resultat->fils_gauche->valeur);
	CU_ASSERT_PTR_NULL(resultat->fils_gauche->fils_gauche);
	CU_ASSERT_PTR_NULL(resultat->fils_gauche->fils_droit);
	CU_ASSERT_STRING_EQUAL("or", resultat->fils_droit->valeur);
	CU_ASSERT_STRING_EQUAL("id=2", resultat->fils_droit->fils_gauche->valeur);
	CU_ASSERT_PTR_NULL(resultat->fils_droit->fils_gauche->fils_gauche);
	CU_ASSERT_PTR_NULL(resultat->fils_droit->fils_gauche->fils_droit);
	CU_ASSERT_STRING_EQUAL("model=6731i", resultat->fils_droit->fils_droit->valeur);
	CU_ASSERT_PTR_NULL(resultat->fils_droit->fils_droit->fils_gauche);
	CU_ASSERT_PTR_NULL(resultat->fils_droit->fils_droit->fils_droit);
}
