#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#include <ctype.h>
#include "macro_func.h"
int main(int argc, char const *argv[]){

//Validação da entrada.
	if(argc!=3){
		printf("ENTRADA INVÁLIDA! A entrada deve conter 2 argumentos obrigatórios: arquivo de entrada e arquivo de saída.\n");
		exit(0);
	}
//Declaração de variáveis.
	int linhas_arquivo=0, quant_macros=0, i=0;
	FILE *ent, *saida;
	ent= fopen (argv[1], "r");
	saida= fopen (argv[2], "w");
//Verificar o número de linhas do arquivo de entrada.
	char entrada[1000];
	while(fgets(entrada,1000,ent)!= NULL){		
		linhas_arquivo++;
	}
	fclose(ent);
	ent= fopen(argv[1], "r");
//Labels e Macros serão representadas por um vetor de strings.	
	char *label[linhas_arquivo], *arquivo[linhas_arquivo], *operando1[linhas_arquivo];
	for(i=0; i< linhas_arquivo; i++){
		label[i]=" ";
		arquivo[i]= " ";
		operando1[i]=" "; 
	}
//Tabela que conterá a posição das macros e seus respectiovos endereços.	
	simbolos tabela[linhas_arquivo];
	for(i=0; i< linhas_arquivo; i++){
		tabela[i].endereco=0;
		tabela[i].chamadas=1;
	}
//Completar a tabela de macros.	
	tabela_macros(ent, label, arquivo, operando1, tabela, &quant_macros);
//Imprimir o código no arquivo de saída.
	imprime(saida, arquivo, tabela, linhas_arquivo, quant_macros);
//Desalocar a memória.	
	for(i=0; i<quant_macros; i++){
		free(tabela[i].nome);
		if(tabela[i].op!=0)
			free(tabela[i].op);	
	}	
	for(i=1; i<=linhas_arquivo; i++){
		free(arquivo[i]);
	}
	fclose(ent);
	fclose(saida);
	return 0;
}
