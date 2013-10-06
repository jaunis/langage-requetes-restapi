#include "analyseur_requete.h"

#ifndef EXECUTEUR_REQUETE_H
#define EXECUTEUR_REQUETE_H

typedef struct t_resultat {
} t_resultat;

t_resultat executer_requete(t_requete*);
size_t callback(void* buffer, size_t size, size_t nmemb, void *userp);

#endif
