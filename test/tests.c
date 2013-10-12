#include "test_analyseur_requete.h"
#include "test_analyseur_json.h"
#include "test_resultat_utils.h"
#include "test_afficheur.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#define CUNIT



int main() {
//	test_analyser_json_valide();
    CU_initialize_registry();

    CU_pSuite suite_analyseur_requete = CU_add_suite("Tests analyseur_requetes.c", NULL, NULL);
    CU_add_test(suite_analyseur_requete, "test_diviser_requete_en_lexemes", test_diviser_requete_en_lexemes);
    CU_add_test(suite_analyseur_requete, "test_construire_requete_etoile_et_renvoyer_statut_ok", test_construire_requete_etoile_et_renvoyer_statut_ok);
    CU_add_test(suite_analyseur_requete, "test_construire_requete_selection_et_renvoyer_statut_ok", test_construire_requete_selection_et_renvoyer_statut_ok);
    CU_add_test(suite_analyseur_requete, "test_construire_requete_et_renvoyer_statut_ko", test_construire_requete_et_renvoyer_statut_ko);

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

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    return CU_get_error();
}
