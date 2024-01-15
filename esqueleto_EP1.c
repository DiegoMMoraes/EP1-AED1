// EP1 – Algoritmos e Estruturas de Dados I
// Diego Machado de Moraes - 14652567
// Mariana Borges Araujo da Silva - 14596342


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "functions.h"

#define TAMANHO 10000

int main(int argc, char ** argv){

	FILE * in;
	char * linha;
	char * copia_ponteiro_linha;
	char * quebra_de_linha;
	char * palavra;	
	char* nome_arquivo;
	char* tipo_indice;
	char* linha_formatada;
	char* palavra_formatada;
	int contador_linha;
	clock_t tempI, tempF;

	//verifica se o numero de argumentos dado na execução é correto
	if(argc < 3) {
		printf("ERRO: Poucos Argumentos.");
		return 0;
	}
	if(argc > 3) {
		printf("ERRO: Muitos Argumentos.");
		return 0;
	}
	if(argc == 3) {
		//inicia o temporizador e salva nome, tipo e arquvio
		tempI = clock();
		nome_arquivo = strdup(argv[1]);
	    tipo_indice = strdup(argv[2]);
		in = fopen(argv[1], "r");

		printf(">>>>> Carregando arquivo...\n");

		//inicializa a lista ligada, se o tipo do indice for lista
		lista_ligada* lista;
		if(strcmp(tipo_indice, "lista") == 0) {
			lista = cria_lista();
		}

		// inicializa a arvore, se o tipo indice for arvore
		arvore* arv;
		if(strcmp(tipo_indice, "arvore") == 0) {
			arv = cria_arvore();
		}

		contador_linha = 0;
 		linha = (char *) malloc((TAMANHO + 1) * sizeof(char));

		while(in && fgets(linha, TAMANHO, in)){
			
			if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;

			//print no numero da linha e no texto da linha
			printf("linha %03d: '%s'\n", contador_linha + 1, linha);


			// salva a linha original e uma versão em que a linha esta formatada
			copia_ponteiro_linha = linha;
			linha_formatada = formata_string(copia_ponteiro_linha);

			// salva a linha de acordo com o tipo do indice
			if(strcmp(tipo_indice, "lista") == 0) {
				salva_linha_lista(lista, contador_linha+1, copia_ponteiro_linha);
			}

			else if(strcmp(tipo_indice, "arvore") == 0) {
				salva_linha_arvore(arv, contador_linha+1, copia_ponteiro_linha);
			}

			while( (palavra_formatada = mystrsep(&linha_formatada, " ")) ){

				//adiciona "nos" na lista, se o tipo for lista
				if(strcmp(tipo_indice, "lista") == 0) {
					adiciona_no(lista, palavra_formatada, contador_linha);
				}

				// adiciona o nos na arvore, se o tipo for arvore
				else if (strcmp(tipo_indice, "arvore") == 0) {
					insere_ord(arv, palavra_formatada, contador_linha);
				}

				//imprime a palavra
				palavra = mystrsep(&copia_ponteiro_linha, " ");
				if (!(palavra == NULL)) {
					printf("\t\t'%s'\n", palavra);
				}
				
			}

			contador_linha++;
		}

		//cria uma nova lista, a qual possibilita a busca
		if(strcmp(tipo_indice, "lista") == 0) {
			cria_lista_nova(lista);
		}

		if(strcmp(tipo_indice, "arvore") == 0) {
			cria_lista_nova_arvore(arv);
		}


		printf(">>>>> Arquivo carregado!\n");
		//finaliza o temporizador
		tempF = clock();

		//print em informações úteis
		printf("Tipo de indice: '%s' \n", tipo_indice);
		printf("Arquivo de texto: '%s' \n", nome_arquivo);
		printf("Numero de linhas no arquivo: %i \n", contador_linha);
		printf("Tempo para carregar o arquivo e construir o indice: %04d ms \n", (1000*(tempF - tempI) / CLOCKS_PER_SEC));


		//código para realizacao da busca
		char acao[10];
		char palavra[50];
		while(1){
			printf("> ");
			scanf("%s", &acao);

			// verifica se a acao é valida
			if((strcmp(acao, "fim") != 0) && (strcmp(acao, "busca") != 0)) {
				printf("Opção Invalida. \n");
			}

			else {
				// verifica se a acao==fim
				if(strcmp(acao,"fim") == 0){
				break;
				}

				scanf("%s", &palavra);

				// transforma todas as letras da palavra em minusculas
				for(int i=0; palavra[i]; i++){
				palavra[i] = tolower(palavra[i]);
				}

				// faz a busca
				if(strcmp(acao, "busca") == 0){
				busca(lista, arv, palavra, tipo_indice);
				}
			}
		}
	return 1;
	
	}
}