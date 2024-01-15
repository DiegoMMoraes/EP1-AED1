Exercício Programa de Análise e Estrutura de Dados I – Indexador e Buscador de Palavras

O exercício programa realizado tem como objetivo buscar palavras em um texto, apresentando quantas vezes ela se repete e em quais linhas do texto a palavra está presente. Para que essa busca seja feita, foram implementadas duas formas de busca: por Lista Ligada ou por Árvore Binária, ficando a critério do usuário selecionar qual forma de busca quer-se aplicar. 

1. Para compilar o projeto no windows, siga as seguintes instruções:
1.1 Certifique-se de que os arquivos: arvore.h, esqueleto_EP1.c, functions.h, listaLigada.h encontram-se no mesmo diretório;
1.2 Feito isso, digite no diretório 'gcc .\esqueleto_EP1.c -o .\esqueleto_EP1' ;
1.3 Esse comando irá gerar um executável que será usado durante a execução do programa.

2. Para executar o projeto, siga as seguintes instruções: 
2.1 Após a compilação do projeto, ponha no diretório onde foi gerado executável o arquivo contendo o texto que se deseja realizar a busca de palavras;
2.2 Feito isso, digite o comando: '.\esqueleto_EP1.exe .\ <NomeDoArquivo> <FormaDeBusca>', onde <NomeDoArquivo> refere-se ao nome do arquivo contendo o texto a ser usado na busca (obs: informe a extensão do texto a ser usado) e <FormaDeBusca> refere-se a qual tipo de busca o programa deve usar: busca por Lista Ligada ou busca por Árvore Binária, por exemplo: '.\esqueletoEP1.exe .\text.txt lista' ou '.\esqueletoEP1.exe .\text.txt arvore';
2.3 Feito isso, um prompt de comando aparecerá para o usuário: “>”. Nesse prompt, para buscar as palavras, o usuário deve digitar 'busca <Palavra>', onde <Palavra> se refere a palavra que se deseja buscar no texto. Exemplo '> busca oi'. Ao informar a palavra desejada, o usuário deve receber as seguintes informações:
 
• Quantas ocorrências da palavra buscada existem no texto;
• Em quais linhas do texto essa palavra aparece;
• Transcrição da(s) linha(s) do texto em que a palavra buscada aparece;
• Tempo de busca em milissegundos.

Caso a palavra buscada não exista no texto, o usuário deve receber as seguintes informações: 
• Informação de que a palavra buscada não foi encontrada;
• Tempo de busca em milissegundos.

3. Para encerrar a execução do programa, o usuário deve digitar fim no prompt de comando. Exemplo: '> fim'.

