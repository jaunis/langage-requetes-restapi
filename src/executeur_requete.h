#include "types.h"
#include <curl/curl.h>
#include <stdbool.h>

#ifndef EXECUTEUR_REQUETE_H
#define EXECUTEUR_REQUETE_H

extern char* REST_API_URL;

char* executer_requete_http(char* cible);
size_t callback(void* buffer, size_t size, size_t nmemb, char** userp);
bool remplir_resultat(char*, t_resultat*);
t_resultats*  executer_requete(t_requete);

#endif
