#ifndef SCANNER_H
#define SCANNER_H



/**
 * Rappresenta una risposta HTTP
 * @param httpCode: Il codice HTTP della richiesta.
 * @param body: Puntatore al body della richiesta.
 * @param error: Puntatore al messaggio di errore o NULL.
 */
typedef struct {
    long httpCode;
    char *body;
    char *error;
} HTTPResponse;


/**
 * Funzione di callback per scrivere i dati di una risposta HTTP.
 * Chiamata dalla libcurl ogni volta che vengono ricevuti dei dati.
 * Riceve i dati in `contents` e li appende alla memoria puntata da `response`.
 * `size` e `nmemb` indicano la dimensione di ogni dato ricevuto
 * 
 * 
 * @param contents: Puntatore ai dati ricevuti.
 * @param size: Dimensione di ogni elemento dati.
 * @param nmemb: Numero di elementi dati ricevuti.
 * @param response: Puntatore al buffer di risposta.
 * 
 * @return size_t: La dimensione totale dei dati ricevuti.
 */
size_t writeCallback(void *contents, size_t size, size_t nmemb, char **response);



/**
 * Recupera il corpo di un URL effettuando una richiesta HTTP in GET.
 * Usa libcurl per fare la richiesta.
 * 
 * 
 * @param url: L'URL da cui recuperare il corpo.
 * 
 * @return HTTPResponse: Una struttura di tipo HTTPResponse.
 */
HTTPResponse getURLBody(const char *url);




#endif