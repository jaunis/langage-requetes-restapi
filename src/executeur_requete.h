#include "analyseur_requete.h"
#include "types.h"
#include <curl/curl.h>

#ifndef EXECUTEUR_REQUETE_H
#define EXECUTEUR_REQUETE_H

void executer_requete(t_requete, t_resultat*);
size_t callback(void* buffer, size_t size, size_t nmemb, void *userp);
bool remplir_resultat(char*, t_resultat*);

#endif
