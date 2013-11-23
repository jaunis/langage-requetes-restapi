#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "interpreteur.h"
#include "analyseur_lexical.h"
#include "analyseur_syntaxique.h"
#include "analyseur_semantique.h"
#include "executeur_requete.h"
#include "types.h"
#include "afficheur.h"
#include "analyseur_json.h"
#include "post_traitement.h"

int main(int argc, char** argv) {
    if(argc != 2) {
        utilisation();
        return 1;
    }
    char* requete_str = argv[1];
    t_requete_lexemes requete_divisee = diviser_requete_en_lexemes(requete_str);
    t_requete requete;
    if(!construire_requete_et_renvoyer_statut(requete_divisee, &requete) || !controler_jointures(&requete)) {
    	printf("Requête invalide, arrêt.\n");
        return 1;
    }
    t_resultats* resultats = executer_requete(requete);
    t_resultat* resultat_jointure = appliquer_jointures(resultats, requete);
	appliquer_clause_where(resultat_jointure, &(requete.condition));
	afficher_resultat(resultat_jointure, &requete.projection);
    return 0;
}

void utilisation() {
    printf("Utilisation : interpreteur \"requête\"\n");
}
