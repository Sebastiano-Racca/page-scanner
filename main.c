#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/scanner.h"



int main(int argc, char **argv){
    char *url;

    if (argc > 1) {
        url = malloc(strlen(argv[1]) + 1); // Alloca memoria per l'url
        strcpy(url, argv[1]);
    } else {
        printf("Inserisci l'url: ");
        url = malloc(256); // Alloca memoria fissa 256 byte per l'url
        scanf("%255s", url); // Aggiunge un limite all'url per non andare altre ai 256 byte
    }


    HTTPResponse result = getURLBody(url); // Fa la richiesa all'url in GET

    if(result.error != NULL){
        printf("C'è stato un errore: %s\n", result.error);
        exit(1);
    }

    printf("HTTP Status code: %ld\n", result.httpCode);
    printf("Body:\n%s\n", result.body);


    // Disalloca la memoria
    free(result.body);
    free(result.error);
    free(url);

    return 0;
}