/*
 * test_analyseur_semantique.c
 *
 *  Created on: 22 nov. 2013
 *      Author: jean
 */

#include "../src/types.h"
#include <stdbool.h>
#include <CUnit/CUnit.h>
#include <stdlib.h>
#include "test_analyseur_semantique.h"
#include "../src/analyseur_semantique.h"

void test_controler_jointures_succes() {
	t_jointure* liste = malloc(2 * sizeof(t_jointure));
	t_jointure elt1 = {
			.cible = malloc(sizeof(char) * (strlen("user_lines")+1)),
			.condition = malloc(sizeof(char) * (strlen("users.id=user_lines.user_id") + 1)),
	};
	t_jointure elt2 = {
			.cible = malloc(sizeof(char) * (strlen("lines")+1)),
			.condition = malloc(sizeof(char) * (strlen("lines.id=user_lines.line_id")+1)),
	};
	strcpy(elt1.cible, "user_lines");
	strcpy(elt1.condition, "users.id=user_lines.user_id");
	strcpy(elt2.cible, "lines");
	strcpy(elt2.condition, "lines.id=user_lines.line_id");
	liste[0] = elt1;
	liste[1] = elt2;
	t_jointures jointures = {
			.nb_jointures = 2,
			.liste = liste
	};
	t_requete requete = {
			.cible = "users",
			.jointures = jointures,
	};
	CU_ASSERT_EQUAL(true, controler_jointures(&requete));
	CU_ASSERT_STRING_EQUAL("user_lines.line_id=lines.id", requete.jointures.liste[1].condition);
}

void test_controler_jointures_pas_de_prefixe() {
	t_jointure* liste = malloc(sizeof(t_jointure));
	t_jointure elt1 = {
			.cible = malloc(sizeof(char) * (strlen("user_lines")+1)),
			.condition = malloc(sizeof(char) * (strlen("id=user_id") + 1)),
	};
	strcpy(elt1.cible, "user_lines");
	strcpy(elt1.condition, "id=user_id");
	liste[0] = elt1;
	t_jointures jointures = {
			.nb_jointures = 1,
			.liste = liste
	};
	t_requete requete = {
			.cible = "users",
			.jointures = jointures,
	};
	CU_ASSERT_EQUAL(false, controler_jointures(&requete));
}

void test_controler_jointures_cible_non_declaree() {
	t_jointure* liste = malloc(sizeof(t_jointure));
	t_jointure elt1 = {
			.cible = malloc(sizeof(char) * (strlen("user_lines")+1)),
			.condition = malloc(sizeof(char) * (strlen("users.id=user_mylines.user_id") + 1)),
	};
	strcpy(elt1.cible, "user_lines");
	strcpy(elt1.condition, "users.id=user_mylines.user_id");
	liste[0] = elt1;
	t_jointures jointures = {
			.nb_jointures = 1,
			.liste = liste
	};
	t_requete requete = {
			.cible = "users",
			.jointures = jointures,
	};
	CU_ASSERT_EQUAL(false, controler_jointures(&requete));

	t_jointure elt2 = {
			.cible = malloc(sizeof(char) * (strlen("user_lines")+1)),
			.condition = malloc(sizeof(char) * (strlen("myusers.id=user_lines.user_id") + 1)),
	};
	strcpy(elt2.cible, "user_lines");
	strcpy(elt2.condition, "myusers.id=user_lines.user_id");
	liste[0] = elt2;
	CU_ASSERT_EQUAL(false, controler_jointures(&requete));
}

void test_controler_conditions_succes() {
	t_condition fg = {
			.valeur = "id=20",
			.fils_gauche = NULL,
			.fils_droit = NULL
	};
	t_condition fd = {
				.valeur = "name=Robert",
				.fils_gauche = NULL,
				.fils_droit = NULL
		};
	t_condition condition = {
			.valeur = "and",
			.fils_gauche = &fg,
			.fils_droit = &fd
	};
	t_jointures jointures = {
			.nb_jointures = 0
	};
	t_requete requete = {
			.cible = "users",
			.condition = condition,
			.jointures = jointures
	};

	CU_ASSERT_EQUAL(true, controler_conditions(&requete));

	t_jointure* liste = malloc(2 * sizeof(t_jointure));
	t_jointure elt1 = {
			.cible = malloc(sizeof(char) * (strlen("user_lines")+1)),
			.condition = malloc(sizeof(char) * (strlen("users.id=user_lines.user_id") + 1)),
	};
	t_jointure elt2 = {
			.cible = malloc(sizeof(char) * (strlen("lines")+1)),
			.condition = malloc(sizeof(char) * (strlen("lines.id=user_lines.line_id")+1)),
	};
	strcpy(elt1.cible, "user_lines");
	strcpy(elt1.condition, "users.id=user_lines.user_id");
	strcpy(elt2.cible, "lines");
	strcpy(elt2.condition, "lines.id=user_lines.line_id");
	liste[0] = elt1;
	liste[1] = elt2;
	jointures.nb_jointures = 2;
	jointures.liste = liste;
	fd.valeur = "lines.id=20";
	fg.valeur = "users.name=Robert";

	CU_ASSERT_EQUAL(true, controler_conditions(&requete));
}

void test_controler_conditions_pas_de_prefixe() {
	t_condition fg = {
			.fils_gauche = NULL,
			.fils_droit = NULL
	};
	fg.valeur = malloc(sizeof(char) * (strlen("id=20") + 1));
	strcpy(fg.valeur, "id=20");
	t_condition fd = {
			.fils_gauche = NULL,
			.fils_droit = NULL
	};
	fd.valeur = malloc(sizeof(char) * (strlen("name=Robert") + 1));
	strcpy(fd.valeur, "name=Robert");
	t_condition condition = {
			.valeur = "and",
			.fils_gauche = &fg,
			.fils_droit = &fd
	};
	t_jointure* liste = malloc(2 * sizeof(t_jointure));
	t_jointure elt1 = {
			.cible = malloc(sizeof(char) * (strlen("user_lines")+1)),
			.condition = malloc(sizeof(char) * (strlen("users.id=user_lines.user_id") + 1)),
	};
	t_jointure elt2 = {
			.cible = malloc(sizeof(char) * (strlen("lines")+1)),
			.condition = malloc(sizeof(char) * (strlen("lines.id=user_lines.line_id")+1)),
	};
	strcpy(elt1.cible, "user_lines");
	strcpy(elt1.condition, "users.id=user_lines.user_id");
	strcpy(elt2.cible, "lines");
	strcpy(elt2.condition, "lines.id=user_lines.line_id");
	liste[0] = elt1;
	liste[1] = elt2;
	t_jointures jointures = {
				.nb_jointures = 2,
				.liste = liste
		};
	t_requete requete = {
			.cible = "users",
			.condition = condition,
			.jointures = jointures
	};


	CU_ASSERT_EQUAL(false, controler_conditions(&requete))
}

void test_controler_conditions_cible_non_declaree() {
	t_condition fg = {
				.fils_gauche = NULL,
				.fils_droit = NULL
	};
	fg.valeur = malloc(sizeof(char) * (strlen("truc.id=20") + 1));
	strcpy(fg.valeur, "truc.id=20");
	t_condition fd = {
			.fils_gauche = NULL,
			.fils_droit = NULL
	};
	fd.valeur = malloc(sizeof(char) * (strlen("users.name=Robert") + 1));
	strcpy(fd.valeur, "users.name=Robert");
	t_condition condition = {
			.valeur = "and",
			.fils_gauche = &fg,
			.fils_droit = &fd
	};
	t_jointure* liste = malloc(2 * sizeof(t_jointure));
	t_jointure elt1 = {
			.cible = malloc(sizeof(char) * (strlen("user_lines")+1)),
			.condition = malloc(sizeof(char) * (strlen("users.id=user_lines.user_id") + 1)),
	};
	t_jointure elt2 = {
			.cible = malloc(sizeof(char) * (strlen("lines")+1)),
			.condition = malloc(sizeof(char) * (strlen("lines.id=user_lines.line_id")+1)),
	};
	strcpy(elt1.cible, "user_lines");
	strcpy(elt1.condition, "users.id=user_lines.user_id");
	strcpy(elt2.cible, "lines");
	strcpy(elt2.condition, "lines.id=user_lines.line_id");
	liste[0] = elt1;
	liste[1] = elt2;
	t_jointures jointures = {
				.nb_jointures = 2,
				.liste = liste
		};
	t_requete requete = {
			.cible = "users",
			.condition = condition,
			.jointures = jointures
	};


	CU_ASSERT_EQUAL(false, controler_conditions(&requete))
}
