/*
 * analyseur_lexical.h
 *
 *  Created on: 25 oct. 2013
 *      Author: jean
 */
#include <stdbool.h>
#include "types.h"

#ifndef ANALYSEUR_LEXICAL_H_
#define ANALYSEUR_LEXICAL_H_

t_requete_lexemes diviser_requete_en_lexemes(char* requete);
void extraire_caracteres_speciaux(char* lexeme, t_requete_lexemes* resultat);
bool est_caractere_special(char caractere);

#endif /* ANALYSEUR_LEXICAL_H_ */
