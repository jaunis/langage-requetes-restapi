#include "analyseur_requete.h"
#include <string.h>

t_requete_lexemes diviser_requete_en_lexemes(char* requete) {
    t_requete_lexemes resultat;
    resultat.tableau = malloc((strlen(requete)/4)*sizeof(char*));
    char* lexeme = strtok(requete, " ");
    int i = 0;
    while(lexeme !=  NULL) {
        resultat.tableau[i] = lexeme;
        i++;
        lexeme = strtok(NULL, " ");
    }
    resultat.taille = i;
    return resultat;
}

bool requete_est_valide(t_requete_lexemes requete) {
    if(requete.taille != 4)
        return false;
    bool resultat = true;
    char** tableau = requete.tableau;
    resultat &= (strcmp(tableau[0], "select") == 0);
    resultat &= (strcmp(tableau[1], "*") == 0);
    resultat &= (strcmp(tableau[2], "from") == 0);
    resultat &= (strlen(tableau[3]) > 0);
    return resultat;
}
