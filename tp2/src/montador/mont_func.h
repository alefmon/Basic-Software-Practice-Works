#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
// O tipo "simbolos" é usado para criar a tabela de símbolos.
	typedef struct{
		char* rotulo;
		int valor;
		int posicao;
	}simbolos;
// A  função verifica a quantidade de operandos a ser lidos pelo programa em cada linha.	
	int quant_operandos(char *operador);
// A função retorna o código numérico do operador.	
	int codigo_operador(char *operador);
// A função imprime o código numérico da instrução ou do operando no arquivo de saída.	
	void imprime_saida(char* operador, FILE* saida, int codigo, int op1, int op2);
// A função retorna o código numérico do operando ( R0 -> 0, R1 -> 1 ...)	
	int codigo_op(char* operando);
// A função retorna o valor associado à posição de memória da Label.	
	int valor_label(char* label, simbolos* tabela, int tamanho_tabela);
// A função retorna o endereço de memória da Label.	
	int endereco_label(char* label, simbolos* tabela, int tamanho_tabela);

