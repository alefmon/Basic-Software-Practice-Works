#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#include <ctype.h>
#include "mont_func.h"
char *load="LOAD", *store="STORE", *read="READ", *write="WRITE", *copy="COPY", *neg="NEG", *sub="SUB", *add="ADD", *and="AND", *or="OR", *xor="XOR", *not="NOT", *jmp="JMP", *jz="JZ", *jnz="JNZ", *jN="JN", *jnn= "JNN", *push="PUSH", *pop="POP", *call="CALL", *ret="RET", *halt="HALT", *word="WORD", *end="END";
char *R0="R0", *R1="R1", *R2="R2", *R3="R3", *R4="R4", *R5="R5", *R6="R6", *R7="R7", *R8="R8", *R9="R9", *R10="R10", *R11="R11", *R12="R12", *R13="R13", *R14="R14", *R15="R15";

int codigo_operador(char* operador){
	if(strcmp(operador, load)==0){
		return 1;
	}
	else if(strcmp(operador,store)==0){
		return 2;
	}
	else if(strcmp(operador,read)==0){
		return 3;
	}
	else if(strcmp(operador,write)==0){
		return 4;
	}
	else if(strcmp(operador,copy)==0){
		return 5;
	}
	else if(strcmp(operador,neg)==0){
		return 6;
	}
	else if(strcmp(operador,sub)==0){
		return 7;
	}					
	else if(strcmp(operador,add)==0){
		return 8;
	}
	else if(strcmp(operador,and)==0){
		return 9;
	}
	else if(strcmp(operador,or)==0){
		return 10;
	}	
	else if(strcmp(operador,xor)==0){
		return 11;
	}
	else if(strcmp(operador,not)==0){
		return 12;
	}
	else if(strcmp(operador,jmp)==0){
		return 13;
	}	
	else if(strcmp(operador,jz)==0){
		return 14;
	}
	else if(strcmp(operador,jnz)==0){
		return 15;
	}
	else if(strcmp(operador,jN)==0){
		return 16;
	}
	else if(strcmp(operador,jnn)==0){
		return 17;
	}
	else if(strcmp(operador,push)==0){
		return 18;
	}
	else if(strcmp(operador,pop)==0){
		return 19;
	}
	else if(strcmp(operador,call)==0){
		return 20;
	}
	else if(strcmp(operador,ret)==0){
		return 21;
	}
	else if(strcmp(operador,halt)==0){
		return 22;
	}
	else if(strcmp(operador,word)==0){
		return 23;
	}
	else if(strcmp(operador,end)==0){
		return 24;
	}
	else{
		printf("OPERAÇÃO INVÁLIDA!\n");
		exit(0);
	}
}	

int quant_operandos(char *operador){
	if(strcmp(operador, load)==0){
		return 2;
	}
	else if(strcmp(operador,store)==0){
		return 2;
	}
	else if(strcmp(operador,read)==0){
		return 1;
	}
	else if(strcmp(operador,write)==0){
		return 1;
	}
	else if(strcmp(operador,copy)==0){
		return 2;
	}
	else if(strcmp(operador,neg)==0){
		return 1;
	}
	else if(strcmp(operador,sub)==0){
		return 2;
	}					
	else if(strcmp(operador,add)==0){
		return 2;
	}
	else if(strcmp(operador,and)==0){
		return 2;
	}
	else if(strcmp(operador,or)==0){
		return 2;
	}	
	else if(strcmp(operador,xor)==0){
		return 2;
	}
	else if(strcmp(operador,not)==0){
		return 1;
	}
	else if(strcmp(operador,jmp)==0){
		return 1;
	}	
	else if(strcmp(operador,jz)==0){
		return 1;
	}
	else if(strcmp(operador,jnz)==0){
		return 1;
	}
	else if(strcmp(operador,jN)==0){
		return 1;
	}
	else if(strcmp(operador,jnn)==0){
		return 1;
	}
	else if(strcmp(operador,push)==0){
		return 1;
	}
	else if(strcmp(operador,pop)==0){
		return 1;
	}
	else if(strcmp(operador,call)==0){
		return 1;
	}
	else if(strcmp(operador,ret)==0){
		return 0;
	}
	else if(strcmp(operador,halt)==0){
		return 0;
	}
	else if(strcmp(operador,word)==0){
		return 1;
	}
	else if(strcmp(operador,end)==0){
		return 0;
	}
	else{
		printf("OPERAÇÃO INVÁLIDA!\n");
		exit(0);
	}
}	

void imprime_saida(char* operador, FILE* saida, int codigo, int op1, int op2){
	if(strcmp(operador, load)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
		fprintf(saida, "%d\n", op2);
	}
	else if(strcmp(operador,store)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
		fprintf(saida, "%d\n", op2);
	}
	else if(strcmp(operador,read)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
	}
	else if(strcmp(operador,write)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
	}
	else if(strcmp(operador,copy)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
		fprintf(saida, "%d\n", op2);
	}
	else if(strcmp(operador,neg)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
	}
	else if(strcmp(operador,sub)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
		fprintf(saida, "%d\n", op2);
	}					
	else if(strcmp(operador,add)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
		fprintf(saida, "%d\n", op2);
	}
	else if(strcmp(operador,and)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
		fprintf(saida, "%d\n", op2);
	}
	else if(strcmp(operador,or)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
		fprintf(saida, "%d\n", op2);
	}	
	else if(strcmp(operador,xor)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
		fprintf(saida, "%d\n", op2);
	}
	else if(strcmp(operador,not)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
	}
	else if(strcmp(operador,jmp)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
	}	
	else if(strcmp(operador,jz)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
	}
	else if(strcmp(operador,jnz)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
	}
	else if(strcmp(operador,jN)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
	}
	else if(strcmp(operador,jnn)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
	}
	else if(strcmp(operador,push)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
	}
	else if(strcmp(operador,pop)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
	}
	else if(strcmp(operador,call)==0){
		fprintf(saida, "%d\n", codigo);
		fprintf(saida, "%d\n", op1);
	}
	else if(strcmp(operador,ret)==0){
		fprintf(saida, "%d\n", codigo);
	}
	else if(strcmp(operador,halt)==0){
		fprintf(saida, "%d\n", codigo);
	}
	else if(strcmp(operador,word)==0){
		fprintf(saida, "%d\n", codigo);
	}
}
int codigo_op(char* operando){
	if(strcmp(operando, R0)==0){
		return 0;
	}
	else if(strcmp(operando, R1)==0){
		return 1;
	}
	else if(strcmp(operando, R2)==0){
		return 2;
	}
	else if(strcmp(operando, R3)==0){
		return 3;
	}
	else if(strcmp(operando, R4)==0){
		return 4;
	}
	else if(strcmp(operando, R5)==0){
		return 5;
	}
	else if(strcmp(operando, R6)==0){
		return 6;
	}
	else if(strcmp(operando, R7)==0){
		return 7;
	}					
	else if(strcmp(operando, R8)==0){
		return 8;
	}
	else if(strcmp(operando, R9)==0){
		return 9;
	}
	else if(strcmp(operando, R10)==0){
		return 10;
	}	
	else if(strcmp(operando, R11)==0){
		return 11;
	}
	else if(strcmp(operando, R12)==0){
		return 12;
	}
	else if(strcmp(operando, R13)==0){
		return 13;
	}	
	else if(strcmp(operando, R14)==0){
		return 14;
	}
	else if(strcmp(operando, R15)==0){
		return 15;
	}
	else
		return 100;
}
int valor_label(char* label, simbolos* tabela, int tamanho_tabela){
	int i=0;
	while(i<tamanho_tabela){
		if(strcmp(label, tabela[i].rotulo)==0){
			return tabela[i].valor;
		}	
		i++;	
	}
	return 0;
}
int endereco_label(char* label, simbolos* tabela, int tamanho_tabela){
	int i=0;
	while(i<tamanho_tabela){
		if(strcmp(label, tabela[i].rotulo)==0){
			return tabela[i].posicao;
		}	
		i++;	
	}
	return 0;
}






