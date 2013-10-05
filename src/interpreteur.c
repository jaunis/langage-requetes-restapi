#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "interpreteur.h"
#include "analyseur_requete.h"

int main(int argc, char** argv) {
    if(argc != 2) {
        utilisation();
        return 1;
    }
    char* requete = argv[1];
    t_requete_lexemes requete_divisee = diviser_requete_en_lexemes(requete);
    if(!requete_est_valide((requete_divisee)) {
        return 1;
    }
    return 0;

}

void utilisation() {
    printf("Utilisation : interpreteur \"requête\"\n");
}
