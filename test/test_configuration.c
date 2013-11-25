/*
 * test_configuration.c
 *
 *  Created on: 24 nov. 2013
 *      Author: jean
 */

#include "test_configuration.h"
#include "../src/executeur_requete.h"
#include "../src/configuration.h"
#include <CUnit/CUnit.h>
#include <stdio.h>

void test_charger_configuration() {
	REST_API_URL = "http://localhost:50050/1.1";
	UTILISATEUR = "root";
	MOT_DE_PASSE = "superpass";
	FILE* fichier = fopen(".interpreteurrc.test", "w");
	fprintf(fichier, "base_url=https://10.49.1.1:50051\n");
	fprintf(fichier, "utilisateur=admin\n");
	fprintf(fichier, "mdp=passadmin\n");
	fclose(fichier);

	charger_configuration(".interpreteurrc.test");
	CU_ASSERT_STRING_EQUAL("https://10.49.1.1:50051/1.1", REST_API_URL);
	CU_ASSERT_STRING_EQUAL("admin", UTILISATEUR);
	CU_ASSERT_STRING_EQUAL("passadmin", MOT_DE_PASSE);

	remove(".interpreteurrc.test");
}

void test_charger_configuration_invalide() {
	REST_API_URL = "http://localhost:50050/1.1";
	UTILISATEUR = "root";
	MOT_DE_PASSE = "superpass";
	FILE* fichier = fopen(".interpreteurrc.test", "w");
	fprintf(fichier, "\n");
	fclose(fichier);

	charger_configuration(".interpreteurrc.test");
	CU_ASSERT_STRING_EQUAL("http://localhost:50050/1.1", REST_API_URL);
	CU_ASSERT_STRING_EQUAL("root", UTILISATEUR);
	CU_ASSERT_STRING_EQUAL("superpass", MOT_DE_PASSE);

	remove(".interpreteurrc.test");
}

void test_pas_de_fichier() {
	REST_API_URL = "http://localhost:50050/1.1";
	UTILISATEUR = "root";
	MOT_DE_PASSE = "superpass";
	charger_configuration(".interpreteurrc.test");
	CU_ASSERT_STRING_EQUAL("http://localhost:50050/1.1", REST_API_URL);
	CU_ASSERT_STRING_EQUAL("root", UTILISATEUR);
	CU_ASSERT_STRING_EQUAL("superpass", MOT_DE_PASSE);
}
