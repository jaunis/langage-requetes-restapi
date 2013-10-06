#include <stdlib.h>
#include <stdbool.h>

#ifndef ANALYSEUR_REQUETE_H
#define ANALYSEUR_REQUETE_H

typedef struct t_requete_lexemes {
    char** tableau;
    int taille;
} t_requete_lexemes;

typedef struct t_requete {
    char* cible;
} t_requete;

t_requete_lexemes diviser_requete_en_lexemes(char*);
bool construire_requete_et_renvoyer_statut(t_requete_lexemes, t_requete*);

#endif
