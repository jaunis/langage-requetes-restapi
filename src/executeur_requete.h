#include "analyseur_requete.h"
#include "types.h"
#include <curl/curl.h>

#ifndef EXECUTEUR_REQUETE_H
#define EXECUTEUR_REQUETE_H

char* executer_requete(t_requete);
size_t callback(void* buffer, size_t size, size_t nmemb, char** userp);
bool remplir_resultat(char*, t_resultat*);

#endif
