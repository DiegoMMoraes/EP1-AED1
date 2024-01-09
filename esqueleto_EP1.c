#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "functions.h"

#define TAMANHO 1000

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
	if(argc == 3) {
		//inicia o temporizador e salva nome, tipo e arquvio
		tempI = clock();
		nome_arquivo = strdup(argv[1]);
	    tipo_indice = strdup(argv[2]);
		in = fopen(argv[1], "r");

		printf(">>>>> Carregando arquivo...\n");

		//cria a lista ligada, se o tipo do indice for lista
		lista_ligada* lista;
		if(strcmp(tipo_indice, "lista") == 0) {
			lista = cria_lista();
		}

		contador_linha = 0;
 		linha = (char *) malloc((TAMANHO + 1) * sizeof(char));

		while(in && fgets(linha, TAMANHO, in)){
			
			if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;

			printf("linha %03d: '%s'\n", contador_linha + 1, linha);

			// fazemos uma copia do endereço que corresponde ao array de chars 
			// usado para armazenar cada linha lida do arquivo pois a função 'mystrsep' 
			// modifica o endereço do ponteiro a cada chamada feita a esta função (e 
			// não queremos que 'linha' deixe de apontar para o inicio do array).

			copia_ponteiro_linha = linha;
			linha_formatada = formata_string(copia_ponteiro_linha);
			salva_linha(lista, contador_linha+1, linha);

			while( (palavra_formatada = mystrsep(&linha_formatada, " ")) ){

				//adiciona "nos" na lista, se o tipo for lista
				if(strcmp(tipo_indice, "lista") == 0) {
					adiciona_no(lista, palavra_formatada, contador_linha, copia_ponteiro_linha);
				}

				palavra = mystrsep(&copia_ponteiro_linha, " ");
				if (!(palavra == NULL)) {
					printf("\t\t'%s'\n", palavra);
				}
				
			}

			contador_linha++;
		}

		cria_lista_nova(lista);
		printf(">>>>> Arquivo carregado!\n");

		//finaliza o temporizador
		tempF = clock();

		//print em informações pedidas por coutinho
		printf("Tipo de indice: '%s' \n", tipo_indice);
		printf("Arquivo de texto: '%s' \n", nome_arquivo);
		printf("Numero de linhas no arquivo: %i \n", contador_linha);
		printf("Tempo para carregar o arquivo e construir o indice: %d ms \n", (1000*(tempF - tempI) / CLOCKS_PER_SEC));

		//da um print na lista, será removido na entrega final 
		// tempI = clock();
		//printLista(lista);
		// tempF = clock();
		// printf("%d", ((tempF - tempI) / CLOCKS_PER_SEC));
		
		char acao[10];
		char palavra[50];
		while(1){
		printf("> ");
		scanf("%s", &acao);

		if((strcmp(acao, "fim") != 0) && (strcmp(acao, "busca") != 0)) {
			printf("Opção Invalida. \n");
		}

		else {
			if(strcmp(acao,"fim") == 0){
			break;
			}

			scanf("%s", &palavra);

			for(int i=0; palavra[i]; i++){
			palavra[i] = tolower(palavra[i]);
			}

			if(strcmp(acao, "busca") == 0){
			busca(lista, palavra, tipo_indice);
			}
			}
			if(strcmp(acao,"fim") == 0){
				break;
		}

	}

	return 1;
	
	}
}