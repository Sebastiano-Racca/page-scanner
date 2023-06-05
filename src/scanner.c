#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "scanner.h"

size_t writeCallback(void *contents, size_t size, size_t nmemb, char **response) {
    size_t realSize = size * nmemb;
    
    // Rialloca la memoria per il buffer di `risposta` per ricevere i nuovi dati
    // Il +1 serve per '\0'
    *response = realloc(*response, realSize + 1);
    if (*response == NULL) {
        fprintf(stderr, "Impossibile allocare memoria per il buffer di risposta.\n");
        return 0;
    }
    
    // Copia i dati ricevuti da `contents` a `response`
    memcpy(*response, contents, realSize);
    (*response)[realSize] = '\0'; // Rende il buffer un'effettiva stringa
    
    return realSize;
}

HTTPResponse getURLBody(const char *url) {
    // Inizializzo la struttura a null
    HTTPResponse response = { NULL };
    
    // Inizializza la libcurl globalmente
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    // Inizializza curl easy handle -> https://everything.curl.dev/libcurl/easyhandle
    CURL *curl = curl_easy_init();
    
    if (curl) {
        // Imposta l'url
        curl_easy_setopt(curl, CURLOPT_URL, url);
        
        // Imposta la funzione di callback con cui andrà a scrivere i dati
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        
        // Imposto dove andare a scrivere i dati
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(response.body));
        
        // Faccio la richiesta
        CURLcode res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) { // C'è stato un errore
            response.error = strdup(curl_easy_strerror(res));
        }
        
        // Prendo il codice HTTP della risposta
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &(response.httpCode));
        
        // Pulisco curl easy handle
        curl_easy_cleanup(curl);
    }
    
    // Pulisco libcurl globalmente
    curl_global_cleanup();
    
    return response;
}

