/*
 * analyseur_semantique.c
 *
 *  Created on: 22 nov. 2013
 *      Author: jean
 */

#include "analyseur_semantique.h"
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include <stdio.h>

bool valider_requete(t_requete* requete) {
    return controler_jointures(requete) && controler_conditions(requete) && controler_projection(requete);
}

bool controler_jointures(t_requete* requete) {
    bool resultat = true;
    bool inverser = false;
    char** cibles_existantes = malloc(sizeof(char*) * (1 + requete->jointures.nb_jointures));
    cibles_existantes[0] = requete->cible;
    for (int i = 0; i < requete->jointures.nb_jointures; i++) {
        t_jointure* jointure = &(requete->jointures.liste[i]);
        resultat &= controler_jointure(jointure, cibles_existantes, i + 1);
        cibles_existantes[i + 1] = jointure->cible;
    }
    free(cibles_existantes);
    return resultat;
}

bool controler_jointure(t_jointure* jointure, char** cibles_existantes, int taille_tableau) {
    bool inverser = false;
    char* condition_reecrite = malloc(sizeof(char) * (strlen(jointure->condition) + 1));
    char* gauche = strtok(jointure->condition, "=");
    bool resultat = true;
    resultat &= verifier_presence_point(gauche);
    char* droite = strtok(NULL, "=");
    resultat &= verifier_presence_point(droite);
    if (resultat) {
        char* cible_gauche = strtok(gauche, ".");
        char* champ_gauche = strtok(NULL, ".");
        char* cible_droite = strtok(droite, ".");
        char* champ_droite = strtok(NULL, ".");
        if (strcmp(jointure->cible, cible_droite) != 0)
            inverser = true;
        if (inverser && strcmp(jointure->cible, cible_gauche) != 0)
            resultat &= false;
        if (inverser) {
            resultat &= tableau_contient_str(cibles_existantes, cible_droite, taille_tableau);
            sprintf(condition_reecrite, "%s.%s=%s.%s", cible_droite, champ_droite, cible_gauche, champ_gauche);
        } else {
            resultat &= tableau_contient_str(cibles_existantes, cible_gauche, taille_tableau);
            sprintf(condition_reecrite, "%s.%s=%s.%s", cible_gauche, champ_gauche, cible_droite, champ_droite);
        }
    }
    free(jointure->condition);
    jointure->condition = condition_reecrite;
    return resultat;
}

bool verifier_presence_point(char* chaine) {
    bool resultat = NULL != strstr(chaine, ".");
    if (!resultat)
        printf(
                "Erreur : les conditions, projections et conditions de jointure doivent être préfixées avec le nom de la cible : %s\n",
                chaine);
    return resultat;
}

bool tableau_contient_str(char** tableau, char* chaine, int taille_tableau) {
    bool resultat = false;
    for (int i = 0; i < taille_tableau; i++) {
        resultat |= strcmp(tableau[i], chaine) == 0;
    }
    if (!resultat)
        printf("Erreur : une conditions, projections ou condition de jointure porte sur une cible inconnue : %s\n",
                chaine);
    return resultat;
}

bool controler_conditions(t_requete* requete) {
    if (requete->jointures.nb_jointures > 0) {
        return conditions_sont_prefixees(requete);
    } else {
        return conditions_sont_non_prefixees(requete->condition);
    }
}

bool conditions_sont_prefixees(t_requete* requete) {
    int taille_tableau = requete->jointures.nb_jointures + 1;
    char** cibles = malloc(sizeof(char*) * taille_tableau);
    liste_cibles(requete, cibles);
    return verifier_prefixage_arbre(requete->condition, cibles, taille_tableau);
}

bool conditions_sont_non_prefixees(t_condition condition) {
    if (condition.valeur == NULL)
        return true;
    if (condition.fils_droit == NULL || condition.fils_gauche == NULL) {
        return verifier_absence_point(condition.valeur);
    }
    return conditions_sont_non_prefixees(*(condition.fils_droit)) && conditions_sont_non_prefixees(*(condition.fils_gauche));
}

bool verifier_prefixage_arbre(t_condition condition, char** cibles, int nb_cibles) {
    if (condition.valeur == NULL)
        return true;
    if (condition.fils_droit == NULL || condition.fils_gauche == NULL) {
        char* valeur = malloc((strlen(condition.valeur) + 1) * sizeof(char));
        strcpy(valeur, condition.valeur);
        return verifier_presence_point(valeur) && tableau_contient_str(cibles, strtok(valeur, "."), nb_cibles);
    }
    return verifier_prefixage_arbre(*(condition.fils_droit), cibles, nb_cibles)
            && verifier_prefixage_arbre(*(condition.fils_gauche), cibles, nb_cibles);
}

bool controler_projection(t_requete* requete) {
    if (requete->jointures.nb_jointures > 0) {
        int taille_tableau = requete->jointures.nb_jointures + 1;
        char** cibles = malloc(sizeof(char*) * taille_tableau);
        liste_cibles(requete, cibles);
        return verifier_prefixage_projection(requete->projection, cibles, taille_tableau);
    } else {
        return verifier_non_prefixage_projection(requete->projection);
    }
}

void liste_cibles(t_requete* requete, char** cibles) {
    cibles[0] = requete->cible;
    for (int i = 1; i < requete->jointures.nb_jointures + 1; i++) {
        cibles[i] = requete->jointures.liste[i - 1].cible;
    }
}

bool verifier_prefixage_projection(t_projection projection, char** cibles, int nb_cibles) {
    bool resultat = true;
    for (int i = 0; i < projection.taille; i++) {
        char* chaine = malloc((strlen(projection.champs[i]) + 1) * sizeof(char));
        strcpy(chaine, projection.champs[i]);
        if (strcmp(chaine, "*") != 0) {
            resultat &= verifier_presence_point(chaine) && tableau_contient_str(cibles, strtok(chaine, "."), nb_cibles);
        }
    }
    return resultat;
}

bool verifier_non_prefixage_projection(t_projection projection) {
    bool resultat = true;
    for(int i=0; i<projection.taille; i++) {
        resultat &= verifier_absence_point(projection.champs[i]);
    }
    return resultat;
}

bool verifier_absence_point(char* chaine) {
    return NULL == strstr(chaine, ".");
}
