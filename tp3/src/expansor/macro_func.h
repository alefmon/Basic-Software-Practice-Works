#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#ifndef MACRO_H
#define MACRO_H
// O tipo "simbolos" é usado para criar a tabela de macros.
	typedef struct{
		char* nome;
		char* op;
		int endereco;
		int chamadas;
	}simbolos;
//A função cria uma tabela de macros, que contém as macros do arquivo de entrada, o endereço delas e o operando da macro, caso ela possua.
void tabela_macros(FILE* ent, char** label, char** arquivo, char** operando1, simbolos* tabela, int* quant_macros);
//A função imprime o código de saída no arquivo de saída.
void imprime(FILE* saida, char** arquivo, simbolos* tabela, int linhas_arquivo, int quant_macros);
//A função verifica o nome da label contida na linha.
char* nome_label(char* arquivo_i, simbolos* tabela, int quant_macros);
//A função verifica e retorna o operando de uma macro.
char* operando_macro(char* arquivo_i, simbolos* tabela, int quant_macros);
//A função verifica a posição da macro no arquivo de entrada.
int verifica_macro(char* arquivo_i, simbolos* tabela, int quant_macros);
//A função imprime a expansão de uma macro.
void imprime_macro(FILE* saida, char** arquivo, int posicao_macro, int linhas_arquivo, char* macro_op, char* chamada_op, int num_chamadas);
//A função verifica o número de linhas ocupadas pela declaração da macro.
int tamanho_macro(FILE* saida, char** arquivo, int posicao_macro, int linhas_arquivo);

#endif
