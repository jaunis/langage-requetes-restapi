#include "executeur_requete.h"
#include "analyseur_json.h"
#include <json/json.h>
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

const char* REST_API_URL = "http://localhost:50050/1.1";
CURL* curl;

void executer_requete(t_requete requete, t_resultat* resultat) {
    CURLcode code_execution;
    curl = curl_easy_init();
    if(curl) {
    	int taille = (strlen(REST_API_URL) + strlen(requete.cible) + 2) * sizeof(char);
        char* url_complete = malloc(taille);
        sprintf(url_complete, "%s/%s", REST_API_URL, requete.cible);
        curl_easy_setopt(curl, CURLOPT_URL, url_complete);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, resultat);
        code_execution = curl_easy_perform(curl);
        free(url_complete);
        curl_easy_cleanup(curl);
        if(code_execution != CURLE_OK) {
            printf("Impossible d'exécuter la requête : %s\n", curl_easy_strerror(code_execution));
            exit(1);
        }
    } else {
        printf("Impossible d'initialiser CURL. Vérifiez que la libcurl est installé");
        exit(1);
    }
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
    t_resultat* resultat = (t_resultat*) userp;
    if(analyser_json(str_buffer, resultat))
    	return statut_ok;
    else
    	return statut_ko;
}

bool remplir_resultat(char* json, t_resultat* resultat) {
	json_object* jobj = json_tokener_parse(json);
	if(json_object_get_type(jobj) != json_type_object)
		return false;
	json_object* contenu =  json_object_object_get(jobj, "items");
	if(json_object_get_type(contenu) != json_type_array)
		return false;
	int taille = json_object_array_length(contenu);
	printf("Il y a %d éléments dans le tableau\n", taille);
	json_object* element;
	for(int i=0; i<taille; i++) {
		element = json_object_array_get_idx(contenu, i);
		printf("Elément %d :\n", i);
		json_object_object_foreach(element, key, val) {
			printf("Clé : %s, valeur : %s\n", key, json_object_get_string(val));
		}
	}
	return true;
}
