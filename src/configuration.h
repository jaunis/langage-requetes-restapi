/*
 * configuration.h
 *
 *  Created on: 24 nov. 2013
 *      Author: jean
 */

#include <stdbool.h>

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

void charger_configuration(char* fichier);
bool verifier_contient_egal(char* chaine);
void rstrip(char* chaine);
void traiter_cle_valeur(char* cle, char* valeur);

#endif /* CONFIGURATION_H_ */
