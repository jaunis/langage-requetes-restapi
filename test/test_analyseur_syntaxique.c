#include "../src/analyseur_syntaxique.h"
#include "../src/utils/liste_str_utils.h"
#include "../src/utils/pile_int_utils.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdlib.h>

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
    lexemes.tableau = malloc(sizeof(char*)*16);
    lexemes.tableau[0] = "select";
    lexemes.tableau[1] = "champ1";
    lexemes.tableau[2] = ",";
    lexemes.tableau[3] = "champ2";
    lexemes.tableau[4] = ",";
    lexemes.tableau[5] = "champ3";
    lexemes.tableau[6] = "from";
    lexemes.tableau[7] = "devices";
    lexemes.tableau[8] = "where";
    lexemes.tableau[9] = "id";
    lexemes.tableau[10] = "=";
    lexemes.tableau[11] = "1";
    lexemes.tableau[12] = "and";
    lexemes.tableau[13] = "model";
	lexemes.tableau[14] = "=";
	lexemes.tableau[15] = "6731i";
    lexemes.taille = 16;

    CU_ASSERT_EQUAL(true, construire_requete_et_renvoyer_statut(lexemes, &requete));

    CU_ASSERT_STRING_EQUAL("devices", requete.cible);
    CU_ASSERT_EQUAL(3, requete.projection.taille);
    CU_ASSERT_STRING_EQUAL("champ1", requete.projection.champs[0]);
    CU_ASSERT_STRING_EQUAL("champ2", requete.projection.champs[1]);
    CU_ASSERT_STRING_EQUAL("champ3", requete.projection.champs[2]);
    CU_ASSERT_STRING_EQUAL("and", requete.condition.valeur);
    CU_ASSERT_STRING_EQUAL("id=1", requete.condition.fils_gauche->valeur);
    CU_ASSERT_STRING_EQUAL("model=6731i", requete.condition.fils_droit->valeur);
}

void test_construire_requete_join_et_renvoyer_statut_ok() {
    t_requete_lexemes lexemes;
    t_requete requete;
    lexemes.tableau = malloc(sizeof(char*)*16);
    lexemes.tableau[0] = "select";
    lexemes.tableau[1] = "*";
    lexemes.tableau[2] = "from";
    lexemes.tableau[3] = "users";
    lexemes.tableau[4] = "join";
    lexemes.tableau[5] = "user_line";
    lexemes.tableau[6] = "on";
    lexemes.tableau[7] = "users.id";
    lexemes.tableau[8] = "=";
    lexemes.tableau[9] = "user_line.user_id";
    lexemes.tableau[10] = "join";
    lexemes.tableau[11] = "lines";
    lexemes.tableau[12] = "on";
    lexemes.tableau[13] = "user_line.line_id";
	lexemes.tableau[14] = "=";
	lexemes.tableau[15] = "lines.id";
    lexemes.taille = 16;

    CU_ASSERT_EQUAL(true, construire_requete_et_renvoyer_statut(lexemes, &requete));

    CU_ASSERT_EQUAL(2, requete.jointures.nb_jointures);
    CU_ASSERT_STRING_EQUAL("user_line", requete.jointures.liste[0].cible);
    CU_ASSERT_STRING_EQUAL("lines", requete.jointures.liste[1].cible);

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

	CU_ASSERT_EQUAL(true, construire_condition_et_renvoyer_statut(clause_where, 7, condition));

	CU_ASSERT_STRING_EQUAL("and", condition->valeur);
	t_condition* f_gauche = condition->fils_gauche;
	CU_ASSERT_STRING_EQUAL("id=1", f_gauche->valeur);
	t_condition* f_droit = condition->fils_droit;
	CU_ASSERT_STRING_EQUAL("model=6731i", f_droit->valeur);
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

	t_condition* resultat = transformer_expression_prefixee_en_arbre(&liste);

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

	//and and id=1 model=6737i or id=2 model=6731i
	liste = initialiser_liste_str();
	liste_str_inserer(&liste, "and", 0);
	liste_str_inserer(&liste, "and", 1);
	liste_str_inserer(&liste, "id=1", 2);
	liste_str_inserer(&liste, "model=6737i", 3);
	liste_str_inserer(&liste, "or", 4);
	liste_str_inserer(&liste, "id=2", 5);
	liste_str_inserer(&liste, "model=6731i", 6);

	resultat = transformer_expression_prefixee_en_arbre(&liste);

	CU_ASSERT_STRING_EQUAL("and", resultat->valeur);
	CU_ASSERT_STRING_EQUAL("and", resultat->fils_gauche->valeur);
	CU_ASSERT_STRING_EQUAL("id=1", resultat->fils_gauche->fils_gauche->valeur);
	CU_ASSERT_STRING_EQUAL("model=6737i", resultat->fils_gauche->fils_droit->valeur);
	CU_ASSERT_STRING_EQUAL("or", resultat->fils_droit->valeur);
	CU_ASSERT_STRING_EQUAL("id=2", resultat->fils_droit->fils_gauche->valeur);
	CU_ASSERT_STRING_EQUAL("model=6731i", resultat->fils_droit->fils_droit->valeur);
}

void test_concatener_tests() {
	char** clause_where = malloc(7 * sizeof(char*));
	clause_where[0] = "id";
	clause_where[1] = "=";
	clause_where[2] = "2";
	clause_where[3] = "and";
	clause_where[4] = "model";
	clause_where[5] = "=";
	clause_where[6] = "6721i";
	int nouvelle_taille = 0;

	char** resultat = concatener_tests(clause_where, 7, &nouvelle_taille);

	CU_ASSERT_STRING_EQUAL("id=2", resultat[0]);
	CU_ASSERT_STRING_EQUAL("and", resultat[1]);
	CU_ASSERT_STRING_EQUAL("model=6721i", resultat[2]);
	CU_ASSERT_EQUAL(3, nouvelle_taille);
}
