#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "listaLigada.h"
#define TAMANHO 1000

char* mystrsep(char** stringp, const char* delim) {
    char* start = *stringp;
    char* p = (start != NULL) ? strpbrk(start, delim) : NULL;

    if (p == NULL) {
        *stringp = NULL;
    } else {
        *p = '\0';
        *stringp = p + 1;
    }

    return start;
}

char* formata_string(char *input) {
    int i, j = 0;
    char *output = (char*) malloc (sizeof(char)*(strlen(input)+1));

    for (i = 0; input[i] != '\0'; i++) {
        //verifica se o caractere eh um "-" de tal forma que, se for, o remove e adciona um espaço no lugar dele no output
        if (input[i] == '-') {
            output[j++] = ' ';
        }
        
        //verifica se o caractere nao eh pontuacao e entao o adiciona no output
        if (!ispunct(input[i])) {
            //adiciona no output, transformando todas as letras em minusculo
            output[j++] = tolower(input[i]);
        }
    }

    //adiciona o caractere final a string
    output[j] = '\0';
    return output;
}

void busca(lista_ligada* lista, char* palavra, char* tipo_indice) {
    clock_t ini, fim;
    ini = clock();
    if(strcmp(tipo_indice, "lista") == 0) buscalista(lista, palavra);

    // codigo


    fim = clock();
    printf("Tempo de busca: %d ms \n", (1000*(fim - ini) / CLOCKS_PER_SEC));
}