#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "interpreteur.h"
#include "analyseur_requete.h"
#include "types.h"

int main(int argc, char** argv) {
    if(argc != 2) {
        utilisation();
        return 1;
    }
    char* requete_str = argv[1];
    t_requete_lexemes requete_divisee = diviser_requete_en_lexemes(requete_str);
    t_requete requete;
    if(!construire_requete_et_renvoyer_statut(requete_divisee, &requete)) {
        return 1;
    }
    printf("Cible : %s\n", requete.cible);
    executer_requete(requete);
    return 0;

}

void utilisation() {
    printf("Utilisation : interpreteur \"requête\"\n");
}
