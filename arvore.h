#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define TAMANHO 1000
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
    int* lista_nova; // Note: This field was declared but not used, you may remove it if unnecessary
} no_arvore;

typedef struct {
    no_arvore* raiz;
    char* linhas[TAMANHO];
} arvore;

// Function to create a new tree
arvore* cria_arvore() {
    arvore* arv = (arvore*)malloc(sizeof(arvore));
    arv->raiz = NULL;
    return arv;
}

// Function to save a line in the tree
void salva_linha_arvore(arvore* arv, int numero_linha, char* linha) {
    // Check if the line number is within bounds
    if (numero_linha >= 0 && numero_linha < TAMANHO) {
        // Allocate memory for the line and copy it
        arv->linhas[numero_linha] = strdup(linha); // Fixed index, and removed +1
    } else {
        // Handle the case where the line number is out of bounds
        printf("ERRO: Número máximo de linhas atingido\n");
    }
}

bool insere_ord_rec(no_arvore* raiz, no_arvore* novo) {
    // Cria nó novo (palavra não existe no catálogo)
    if (strcmp(raiz->palavra, novo->palavra) != 0) {
        if (strcmp(raiz->palavra, novo->palavra) > 0) {
            if (raiz->esquerda) 
                return insere_ord_rec(raiz->esquerda, novo);
            else {
                raiz->esquerda = novo;
            }
        } else {
            if (raiz->direita) 
                return insere_ord_rec(raiz->direita, novo);
            else 
                raiz->direita = novo;
        }

        return TRUE;
    } else {
        // Palavra já existe, incrementa a quantidade
        raiz->quantidade++;
        lista_linha_arvore* linha_atual = raiz->linhas_aparece;

        while (linha_atual->proximo != NULL) {
            linha_atual = linha_atual->proximo;
        }

        lista_linha_arvore* linha_nova = (lista_linha_arvore*)malloc(sizeof(lista_linha_arvore));
        linha_nova->quantidade = linha_atual->quantidade + 1; // Fix here
        linha_nova->proximo = NULL;
        linha_atual->proximo = linha_nova;
    }

    return FALSE;
}

bool insere_ord(arvore* arv, char* palavra, int linha) {
    no_arvore* novo = (no_arvore*)malloc(sizeof(no_arvore));

    novo->palavra = strdup(palavra);
    novo->quantidade = 1;

    lista_linha_arvore* aux = (lista_linha_arvore*)malloc(sizeof(lista_linha_arvore));
    aux->quantidade = linha + 1;
    aux->proximo = NULL;
    novo->linhas_aparece = aux;

    novo->esquerda = novo->direita = NULL;

    if (arv->raiz) 
        return insere_ord_rec(arv->raiz, novo);
    else
        arv->raiz = novo;

    return TRUE;
}


void cria_lista_nova_arvore_rec(no_arvore* raiz) {
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

            // Ensure that the lista_nova array is initialized
            if (no->lista_nova == NULL) {
                return NULL;
            }

            for (int i = 0; i < TAMANHO; i++) {
                // Print the line numbers where the word appears
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

// Function to perform inorder traversal
void printArvore_rec(no_arvore* raiz) {
    if (raiz) {
        printArvore_rec(raiz->esquerda);
        printf("Palavra: '%s' \\ ", raiz->palavra);
        printf("Quantidade: %i \\ ", raiz->quantidade);
        
        printf("Linhas Velhas: ");
        lista_linha_arvore *linha_atual = raiz->linhas_aparece;
        while (linha_atual != NULL){
            printf("%d ", linha_atual->quantidade);
            linha_atual = linha_atual->proximo;

        }

        printf("\\ Linhas Novas: ");
        for(int i = 0; i < TAMANHO; i++) {
            printf("%i", raiz->lista_nova[i]);
        }
        printf("\n \n");
        printArvore_rec(raiz->direita);
    }
}

void printArvore(arvore* arv) {
    printf("Elementos da Árvore: \n");
    printArvore_rec(arv->raiz);
}