#include "test_analyseur_lexical.h"
#include "test_analyseur_syntaxique.h"
#include "test_analyseur_json.h"
#include "test_dict_utils.h"
#include "test_afficheur.h"
#include "test_post_traitement.h"
#include "test_analyseur_semantique.h"
#include "test_configuration.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#define CUNIT



int main() {
//	test_construire_condition_et_renvoyer_statut_ok();
    CU_initialize_registry();

    CU_pSuite suite_analyseur_lexical = CU_add_suite("Tests analyseur_lexical.c", NULL, NULL);
    CU_add_test(suite_analyseur_lexical, "test_diviser_requete_en_lexemes", test_diviser_requete_en_lexemes);

    CU_pSuite suite_analyseur_syntaxique = CU_add_suite("Tests analyseur_syntaxique.c", NULL, NULL);
    CU_add_test(suite_analyseur_syntaxique, "test_construire_requete_etoile_et_renvoyer_statut_ok", test_construire_requete_etoile_et_renvoyer_statut_ok);
    CU_add_test(suite_analyseur_syntaxique, "test_construire_requete_selection_et_renvoyer_statut_ok", test_construire_requete_selection_et_renvoyer_statut_ok);
    CU_add_test(suite_analyseur_syntaxique, "test_construire_requete_join_et_renvoyer_statut_ok", test_construire_requete_join_et_renvoyer_statut_ok);
    CU_add_test(suite_analyseur_syntaxique, "test_construire_requete_et_renvoyer_statut_ko", test_construire_requete_et_renvoyer_statut_ko);
    CU_add_test(suite_analyseur_syntaxique, "test_transformer_expression_prefixee_en_arbre", test_transformer_expression_prefixee_en_arbre);
    CU_add_test(suite_analyseur_syntaxique, "test_construire_condition_et_renvoyer_statut_ok", test_construire_condition_et_renvoyer_statut_ok);
    CU_add_test(suite_analyseur_syntaxique, "test_prefixer_expression", test_prefixer_expression);
    CU_add_test(suite_analyseur_syntaxique, "test_concatener_tests", test_concatener_tests);

    CU_pSuite suite_analyseur_semantique = CU_add_suite("Tests analyseur_semantique.c", NULL, NULL);
	CU_add_test(suite_analyseur_semantique, "test_controler_jointures_succes", test_controler_jointures_succes);
	CU_add_test(suite_analyseur_semantique, "test_controler_jointures_pas_de_prefixe", test_controler_jointures_pas_de_prefixe);
	CU_add_test(suite_analyseur_semantique, "test_controler_jointures_cible_non_declaree", test_controler_jointures_cible_non_declaree);
	CU_add_test(suite_analyseur_semantique, "test_controler_conditions_succes", test_controler_conditions_succes);
	CU_add_test(suite_analyseur_semantique, "test_controler_conditions_pas_de_prefixe", test_controler_conditions_pas_de_prefixe);
	CU_add_test(suite_analyseur_semantique, "test_controler_conditions_cible_non_declaree", test_controler_conditions_cible_non_declaree);
	CU_add_test(suite_analyseur_semantique, "test_controler_condition_prefixage_en_trop", test_controler_condition_prefixage_en_trop);
	CU_add_test(suite_analyseur_semantique, "test_controler_projections_succes", test_controler_projections_succes);
	CU_add_test(suite_analyseur_semantique, "test_controler_projections_pas_de_prefixe", test_controler_projections_pas_de_prefixe);
	CU_add_test(suite_analyseur_semantique, "test_controler_projections_cible_non_declaree", test_controler_projections_cible_non_declaree);
	CU_add_test(suite_analyseur_semantique, "test_controler_projection_prefixage_en_trop", test_controler_projection_prefixage_en_trop);

	CU_pSuite suite_resultat_utils = CU_add_suite("Tests resultat_utils.c", NULL, NULL);
	CU_add_test(suite_resultat_utils, "test_dict_valeur", test_dict_valeur);
	CU_add_test(suite_resultat_utils, "test_dict_valeur_null", test_dict_valeur_null);
	CU_add_test(suite_resultat_utils, "test_dict_inserer_cle_valeur", test_dict_inserer_cle_valeur);
	CU_add_test(suite_resultat_utils, "test_initialiser_dict", test_initialiser_dict);
	CU_add_test(suite_resultat_utils, "test_dict_inserer_cle_existante", test_dict_inserer_cle_existante);

	CU_pSuite suite_afficheur = CU_add_suite("Tests afficheur.c", NULL, NULL);
	CU_add_test(suite_afficheur, "test_afficher_resultat_complet", test_afficher_resultat_complet);
	CU_add_test(suite_afficheur, "test_afficher_resultat_partiel", test_afficher_resultat_partiel);

    CU_pSuite suite_analyseur_json = CU_add_suite("Tests analyseur_json.c", NULL, NULL);
	CU_add_test(suite_analyseur_json, "test_analyser_json_valide", test_analyser_json_valide);
	CU_add_test(suite_analyseur_json, "test_analyser_json_invalide", test_analyser_json_invalide);

	CU_pSuite suite_post_traitement = CU_add_suite("Tests post_traitement.c", NULL, NULL);
	CU_add_test(suite_post_traitement, "test_appliquer_clause_where", test_appliquer_clause_where);
	CU_add_test(suite_post_traitement, "test_element_verifie_condition", test_element_verifie_condition);
	CU_add_test(suite_post_traitement, "test_appliquer_jointures", test_appliquer_jointures);
	CU_add_test(suite_post_traitement, "test_appliquer_jointures_champ_inexistant", test_appliquer_jointures_champ_inexistant);

	CU_pSuite suite_configuration = CU_add_suite("Tests configuration.c", NULL, NULL);
	CU_add_test(suite_configuration, "test_charger_configuration", test_charger_configuration);
	CU_add_test(suite_configuration, "test_charger_configuration_invalide", test_charger_configuration_invalide);
	CU_add_test(suite_configuration, "test_pas_de_fichier", test_pas_de_fichier);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    return CU_get_error();
}
