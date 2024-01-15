#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define TAMANHO 10000

typedef struct _linha_{
    int quantidade;
    struct _linha_ * proximo;
}lista_linha;

typedef struct _no_ {
    char* palavra;
    int quantidade;
    lista_linha* linhas_aparece;
    struct _no_* proximo;
    int* lista_nova;
} no;

typedef struct {
    no* primeiro;
    char* linhas[TAMANHO];
} lista_ligada;


//cria lista e atribui o devido valor a lista->proximo
lista_ligada* cria_lista() {
    lista_ligada* lista = (lista_ligada*)malloc(sizeof(lista_ligada));
    lista->primeiro = NULL;
    return lista;
}

void salva_linha_lista(lista_ligada* lista, int numero_linha, char* linha) {
    // checa o numero da linha é válido
    if (numero_linha >= 0 && numero_linha < TAMANHO) {
        // salva a linha
        lista->linhas[numero_linha+1] = strdup(linha);
    } else {
        printf("ERRO: Número máximo de linhas atingido. \n");
    }
}

//adiciona um no, verificando se a palavra ja existe no catalogo
int adiciona_no(lista_ligada* lista, char* palavra, int linha) {
    //se a palavra tem tamanho, em bytes, igual a 0, retorna 0, que significa erro
    if (strlen(palavra) == 0) return 0;

    no* aux = lista->primeiro;

        while (aux != NULL) {
            //testa se a palavra ja existe no catalogo
            if (strcmp(aux->palavra, palavra) == 0) {
                // se existir, atualiza-se a quantidade de aparições dessa palavra
                aux->quantidade++;

                lista_linha* linha_atual = aux->linhas_aparece;
                //chega ao ultimo elemento da lista de aparicoes dessa palavra
                while (linha_atual->proximo) {
                linha_atual = linha_atual->proximo;
                }

                // adiciona a linha em que essa palavra foi encontrada na ultima posicao da lista de aparicoes
                lista_linha* linha_nova = (lista_linha*)malloc(sizeof(lista_linha));
                linha_nova->quantidade = linha+1;
                linha_nova->proximo = NULL;
                linha_atual->proximo = linha_nova;

                //retorna 1, que significa que a funcao deu certo, porem nao adicionou um no novo
                return 1;
            }

        //evita que o programa acesse uma memoria que nao é reservada para ele
        if (aux->proximo == NULL) {
            break;
        }

        aux = aux->proximo;
    }

    //codigo executado caso a palavra nao exista 
    //cria um novo no, atribuindo os devidos valores
    no* novo = (no*)malloc(sizeof(no));
    novo->palavra = strdup(palavra);
    novo->quantidade = 1;

    lista_linha* linha_nova = (lista_linha*) malloc(sizeof(lista_linha));
    linha_nova->quantidade = linha+1;
    linha_nova->proximo = NULL;
    novo->linhas_aparece = linha_nova;
    novo->proximo = NULL;


    //verifica se o no deve ser inserido na primeira posicao da lista ou nao
    if (aux == NULL) {
        lista->primeiro = novo;
    } else {
        aux->proximo = novo;
    }

    //retorna 2, que significa que a funcao deu certo e um no foi adicionado
    return 2;
}

//funcao utilizada para criar uma forma melhorada de trabalhar com as linhas em que a palavra aparece
void cria_lista_nova(lista_ligada* lista) {
    no *atual = lista->primeiro;

    while (atual != NULL){
        //passa por todos os elementos da lista, criando uma lista nova com TAMANHO espaços de memoria zerados
        lista_linha *linha_atual = atual->linhas_aparece;
        atual->lista_nova = (int *)calloc(TAMANHO, sizeof(int)); 

        //atribui os devidos valores nas novas listas
        while (linha_atual != NULL){
            atual->lista_nova[linha_atual->quantidade]++;
            linha_atual = linha_atual->proximo;
            
        }
        atual = atual->proximo;
    }
}

int buscalista(lista_ligada* lista, char* palavra) {
    no* busca = lista->primeiro;
    
    // encontra a palavra no catálogo
    while (busca) {
        if (strcmp(busca->palavra, palavra) == 0) {
            printf("Existem %i ocorrências da palavra '%s' na(s) seguinte(s) linha(s): \n", busca->quantidade, busca->palavra);

            // garante que lista_nova foi inicializado
            if (busca->lista_nova == NULL) {
                return -1;
            }

            for (int i = 0; i < TAMANHO; i++) {
                // imprime as linhas em que palavra aparece
                if (busca->lista_nova[i] > 0) {
                    printf("Linha %i: %s\n", i, lista->linhas[i+1]);
                }
            }
            return 0;
        }

        busca = busca->proximo;
    }
    printf("Palavra '%s' nao encontrada. \n", palavra);
    return -1;
}
