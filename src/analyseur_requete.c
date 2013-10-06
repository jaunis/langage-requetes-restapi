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

bool construire_requete_et_renvoyer_statut(t_requete_lexemes lexemes, t_requete* requete) {
    if(lexemes.taille != 4)
        return false;
    bool resultat = true;
    char** tableau = lexemes.tableau;
    resultat &= (strcmp(tableau[0], "select") == 0);
    resultat &= (strcmp(tableau[1], "*") == 0);
    resultat &= (strcmp(tableau[2], "from") == 0);
    resultat &= (strlen(tableau[3]) > 0);
    if(resultat)
        requete->cible = tableau[3];
    return resultat;
}
