#include <stdlib.h>
#include <stdbool.h>

typedef struct t_requete_lexemes {
    char** tableau;
    int taille;
} t_requete_lexemes;

t_requete_lexemes diviser_requete_en_lexemes(char*);
bool requete_est_valide(t_requete_lexemes requete);
