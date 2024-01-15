#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define TAMANHO 10000
#define FALSE 0
#define TRUE 1
typedef int bool;

typedef struct _linha_arvore {
    int quantidade;
    struct _linha_arvore* proximo;
} lista_linha_arvore;

typedef struct _no_arvore {
    char* palavra;
    int quantidade;
    lista_linha_arvore* linhas_aparece;
    struct _no_arvore* esquerda;
    struct _no_arvore* direita;
    int* lista_nova;
} no_arvore;

typedef struct {
    no_arvore* raiz;
    char* linhas[TAMANHO];
} arvore;

// inicializa uma nova árvore, atribuindo o valor correto para raiz
arvore* cria_arvore() {
    arvore* arv = (arvore*)malloc(sizeof(arvore));
    arv->raiz = NULL;
    return arv;
}

void salva_linha_arvore(arvore* arv, int numero_linha, char* linha) {
    // checa o numero da linha é válido
    if (numero_linha >= 0 && numero_linha < TAMANHO) {
        // salva a linha
        arv->linhas[numero_linha] = strdup(linha);
    } else {
        printf("ERRO: Número máximo de linhas atingido. \n");
    }
}

bool insere_ord_rec(no_arvore* raiz, no_arvore* novo, int linha) {
    // procura se a palavra já existe, se não existir, inclua o novo nó na árvore
    if (strcmp(raiz->palavra, novo->palavra) != 0) {
        if (strcmp(raiz->palavra, novo->palavra) > 0) {
            if (raiz->esquerda) 
                return insere_ord_rec(raiz->esquerda, novo, linha);
            else {
                raiz->esquerda = novo;
            }
        } else {
            if (raiz->direita) 
                return insere_ord_rec(raiz->direita, novo, linha);
            else 
                raiz->direita = novo;
        }

        return TRUE;
    } else {
        // Palavra já existe, incrementa a quantidade
        raiz->quantidade++;
        lista_linha_arvore* linha_atual = raiz->linhas_aparece;

        // adiciona o número da linha na lista ligada de número de linhas
        while (linha_atual->proximo != NULL) {
            linha_atual = linha_atual->proximo;
        }

        lista_linha_arvore* linha_nova = (lista_linha_arvore*)malloc(sizeof(lista_linha_arvore));
        linha_nova->quantidade = linha+1;
        linha_nova->proximo = NULL;
        linha_atual->proximo = linha_nova;
    }

    return FALSE;
}

bool insere_ord(arvore* arv, char* palavra, int linha) {
    //cria um novo nó, atribuindo os devidos valores
    no_arvore* novo = (no_arvore*)malloc(sizeof(no_arvore));

    novo->palavra = strdup(palavra);
    novo->quantidade = 1;

    lista_linha_arvore* aux = (lista_linha_arvore*)malloc(sizeof(lista_linha_arvore));
    aux->quantidade = linha + 1;
    aux->proximo = NULL;
    novo->linhas_aparece = aux;

    novo->esquerda = novo->direita = NULL;

    // verifica se o nó será adicionado na raiz da lista ou não
    if (arv->raiz) 
        return insere_ord_rec(arv->raiz, novo, linha);
    else
        arv->raiz = novo;

    return TRUE;
}

//funcao utilizada para criar uma forma melhorada de trabalhar com as linhas em que a palavra aparece
void cria_lista_nova_arvore_rec(no_arvore* raiz) {
    // passa por todos os elementos recursivamente, criando a lista nova
    if (raiz) {
        cria_lista_nova_arvore_rec(raiz->esquerda);

        raiz->lista_nova = (int*)calloc(TAMANHO, sizeof(int));

        lista_linha_arvore* linha_atual = raiz->linhas_aparece;

        // Atribui os devidos valores nas novas listas
        while (linha_atual != NULL) {
            raiz->lista_nova[linha_atual->quantidade]++;
            linha_atual = linha_atual->proximo;
        }

        cria_lista_nova_arvore_rec(raiz->direita);
    }
}

no_arvore* buscaarvore_rec(arvore* arv, no_arvore* no, char* palavra) {
    if (no) {
        if (strcmp(no->palavra, palavra) == 0) {
            printf("Existem %i ocorrência(s) da palavra '%s' na(s) seguinte(s) linha(s):\n", no->quantidade, palavra);

            // garante a lista_nova foi inicializada
            if (no->lista_nova == NULL) {
                return NULL;
            }

            for (int i = 0; i < TAMANHO; i++) {
                // imprime as linhas em que palavra aprece
                if (no->lista_nova[i] > 0) {
                    printf("Linha %i: %s\n", i, arv->linhas[i]);
                }
            }
            return no;
        }

        if (strcmp(no->palavra, palavra) < 0) {
            return buscaarvore_rec(arv, no->direita, palavra);
        } else {
            return buscaarvore_rec(arv, no->esquerda, palavra);
        }
    }

    printf("Palavra '%s' nao encontrada. \n", palavra);
    return NULL;
}

no_arvore* buscaarvore(arvore* arv, char* palavra) {
    return buscaarvore_rec(arv, arv->raiz, palavra);
}

void cria_lista_nova_arvore (arvore* arv) {
    cria_lista_nova_arvore_rec(arv->raiz);
}
