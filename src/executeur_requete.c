#include "executeur_requete.h"
#include "analyseur_json.h"
#include <json/json.h>
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

const char* REST_API_URL = "http://localhost:50050/1.1";
CURL* curl;

char* executer_requete(t_requete requete) {
    CURLcode code_execution;
    curl = curl_easy_init();
    if(curl) {
    	int taille = (strlen(REST_API_URL) + strlen(requete.cible) + 2) * sizeof(char);
        char* url_complete = malloc(taille);
        sprintf(url_complete, "%s/%s", REST_API_URL, requete.cible);
        curl_easy_setopt(curl, CURLOPT_URL, url_complete);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        char* resultat = malloc(sizeof(char));
        resultat[0] = '\0';
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resultat);
        code_execution = curl_easy_perform(curl);
        free(url_complete);
        curl_easy_cleanup(curl);
        if(code_execution != CURLE_OK) {
            printf("Impossible d'exécuter la requête : %s\n", curl_easy_strerror(code_execution));
            exit(1);
        }
        return resultat;
    } else {
        printf("Impossible d'initialiser CURL. Vérifiez que la libcurl est installée\n");
        exit(1);
    }
}

size_t callback(void* buffer, size_t size, size_t nmemb, char** userp) {
    size_t statut_ok = size * nmemb;
    size_t statut_ko = -1;
    long http_code = 0;
    char* str_buffer = (char*) buffer;
    curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
    if(http_code != 200) {
        printf("Erreur dans la requête HTTP : code %ld\n%s", http_code, str_buffer);
        return statut_ko;
    }
    *userp = realloc(*userp, (strlen(str_buffer) + strlen(*userp) + 1) * sizeof(char));
    strcat(*userp, str_buffer);
    return statut_ok;
}
