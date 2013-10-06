#include "executeur_requete.h"
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

const char* REST_API_URL = "http://localhost:50050/1.1";
CURL* curl;

t_resultat executer_requete(t_requete* requete) {
    t_resultat resultat;
    CURLcode code_execution;
    curl = curl_easy_init();
    if(curl) {
        char* url_complete = malloc((strlen(REST_API_URL) + strlen(requete->cible) + 1) * sizeof(char));
        sprintf(url_complete, "%s/%s", REST_API_URL, requete->cible);
        curl_easy_setopt(curl, CURLOPT_URL, url_complete);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        code_execution = curl_easy_perform(curl);
        free(url_complete);
        curl_easy_cleanup(curl);
        if(code_execution != CURLE_OK) {
            printf("Impossible d'exécuter la requête : %s\n", curl_easy_strerror(code_execution));
            exit(1);
        }
        long http_code = 0;
//        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
    } else {
        printf("Impossible d'initialiser CURL. Vérifiez que la libcurl est installé");
        exit(1);
    }
    return resultat;
}

size_t callback(void* buffer, size_t size, size_t nmemb, void* userp) {
    size_t statut_ok = size * nmemb;
    size_t statut_ko = -1;
    long http_code = 0;
    char* str_buffer = (char*) buffer;
    curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
    if(http_code != 200) {
        printf("Erreur dans la requête HTTP : code %ld\n%s", http_code, str_buffer);
        return statut_ko;
    }
    printf("Appel du callback : %s\n", str_buffer);
    return statut_ok;
}
