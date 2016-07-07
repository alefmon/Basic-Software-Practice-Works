#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#include <ctype.h>
#include "mont_func.h"

int main(int argc, char *argv[]){

	
//Validação da entrada.
	if(argc!=3 && argc!=4){
		printf("ENTRADA INVÁLIDA! A entrada deve conter 2 argumentos obrigatórios: arquivo de entrada e arquivo de saída.\n");
		exit(0);
	}
//Declaração de variáveis.
	int r=0, i=0, j=0, k=0, m=0, p=0, q=0, flag=0, linhas_arquivo=0;
	int ILC=1, PC=1, cod=0, op1=0, op2=0, tamanho_inst=0;
	char operador[6];
	char x,linha[1000]={0}, aux[1000]={0};
	FILE *ent, *saida;
	ent= fopen (argv[1], "r");
	saida= fopen (argv[2], "w");
//verificar o modo de saída foi passado como argumento.	
	char* modo_saida;
	if(argv[3]!=NULL)
		modo_saida= argv[3];
//Verificar o número de linhas do arquivo de entrada.
	char entrada[1000];
	while(fgets(entrada,1000,ent)!= NULL){		
		linhas_arquivo++;
	}
	fclose(ent);
	ent= fopen(argv[1], "r");
//Label, operador e operandos serão um vetor de strings.	
	char *label[linhas_arquivo], *operando1[linhas_arquivo], *operando2[linhas_arquivo];
	simbolos tabela[linhas_arquivo];


	
////////////////////////******************** PASSAGEM UM DO MONTADOR **********************/////////////////////////////////
	
//Leitura de cada linha do arquivo de entrada (uma por ciclo).
	while(fgets(linha,1000,ent)!= NULL){

			//verificar o conteúdo da linha.
				for(i=0;i< 1000; i++){
					// FLAG= 1 -> Há label na instrução.
					if(linha[i]==':')
						flag=1;
					// FLAG= 2 -> A linha só contém comentários ou está vazia.
					if(linha[i]==';' && flag==0)
						flag=2;
					if(linha[i]=='\n' && flag==0)
						flag=2;				
					// FLAG= 3 -> A linha tem uma instrução, mas não contém Label.
					if(!isblank(linha[i]) && flag!=1 && flag!=2)
						flag=3; 
				}
				i=0;

			//Passar os espaços vazios da linha.
				x= linha[i];
				while(isblank(x) && flag!=2){
					i++;
					x= linha[i];
				}
			//Se FLAG= 1, verificar a label da instrução.
				if(flag==1){
						while(x!=':'){
							aux[j]= linha[i];
							j++;
							i++;
							x= linha[i];		
						}
						label[m]= (char*) malloc(j*sizeof(char)+1);
						strcpy(label[m], aux);
						i++;
					//adiciona a label na tabela de simbolos.
						tabela[r].rotulo= (char*) malloc(j*sizeof(char)+1);
						strcpy(tabela[r].rotulo,label[m]);
					//adiciona o endereço da label na tabela de símbolos.
						tabela[r].posicao= ILC;
						
					//Passar os espaços vazios.
						x= linha[i];
						while(isblank(x) && flag!=2){
							i++;
							x= linha[i];
						}			
					//Zerar o vetor auxiliar.
						for(j=0; j<1000; j++)
							aux[j]=0;
						j=0, k=0;
				}
			//verificar o operador da instrução.
				if(flag!=2){
						while(!isblank(x) && x!='\n' && x!=EOF && j<6){
							aux[j]= linha[i];
							j++;
							i++;
							x= linha[i];
						}
						for(k=0;k<j;k++){
							operador[k]= aux[k];
						}		
					//Zerar o vetor auxiliar.
						for(j=0; j<1000; j++)
							aux[j]=0;
						j=0, k=0;
					//Caso o operador seja WORD, executa a pseudo-instrução WORD.
						if(codigo_operador(operador)==23){
							//Passar os espaços vazios.
								while(isblank(x)){
									i++;
									x= linha[i];
								}								
							//verificar o operando da pseudo-instrução WORD.
								while(!isblank(x) && x!= ';' && x!='\n' && x!=EOF){
									aux[j]= linha[i];
									j++;
									i++;
									x= linha[i];
								}
								operando1[p]= (char*) malloc(j*sizeof(char)+1);
								strcpy(operando1[p], aux);
							//Passar os espaços vazios.
								while(isblank(x)){
									i++;
									x= linha[i];
								}			
							//Zerar o vetor auxiliar.
								for(j=0; j<1000; j++)
									aux[j]=0;
								j=0, k=0;
							//Aloca o valor do operando à Label.	
								tabela[r].valor= atoi(operando1[p]);
								free(operando1[p]);
								p++;
						}
				}	
			//verifica o tamanho da instrução e incrementa o ILC.
				if(flag!=2){
					tamanho_inst= quant_operandos(operador);
					ILC+= (tamanho_inst +1);
				}
			//Se houve label na linha, desaloca a memória.	
				if(flag==1){
					free(label[m]);
					m++;
				}	
				if(flag==1)
					r++;
			//Zerar o vetor operador, o vetor linha e as variáveis.
				for(k=0;k<6;k++)
					operador[k]=0;
				for(k=0;k<1000;k++)
					linha[k]=0;
				flag=0, j=0, k=0, i=0, tamanho_inst=0;

	}	
	
//Imprimir a tabela de simbolos, caso o modo de saída seja "Verbose".
	if(argv[3]!=NULL && *modo_saida=='v'){
		printf("\tLABEL\t\tENDEREÇO\n");
		for(k=0; k< r; k++)	
			printf("\t%s\t\t%d\n", tabela[k].rotulo, tabela[k].posicao);
	}	
//Fechar e abrir o arquivo de entrada novamente.
	fclose(ent);
	ent= fopen(argv[1], "r");



//////////////////////////////////************************ PASSAGEM DOIS DO MONTADOR ***************************////////////////////////////

//Leitura de cada linha do arquivo de entrada (uma por ciclo). 
	while(fgets(linha,1000,ent)!= NULL){
			//verificar o conteúdo da linha.
				for(i=0;i< 1000; i++){
					// FLAG= 1 -> Há label na instrução.
					if(linha[i]==':')
						flag=1;
					// FLAG= 2 -> A linha só contém comentários ou está vazia.
					if(linha[i]==';' && flag==0)
						flag=2;
					if(linha[i]=='\n' && flag==0)
						flag=2;				
					// FLAG= 3 -> A linha tem uma instrução, mas não contém Label.
					if(!isblank(linha[i]) && flag!=1 && flag!=2)
						flag=3; 
				}
				i=0;
			//Passar os espaços vazios.
				x= linha[i];
				while(isblank(x) && flag!=2){
					i++;
					x= linha[i];
				}
			//Zerar o vetor auxiliar.
				for(j=0; j<1000; j++)
					aux[j]=0;
				j=0,k=0;
			//Se FLAG=1, verificar a label da instrução.
				if(flag==1){
						while(x!=':'){
							aux[j]= linha[i];
							j++;
							i++;
							x= linha[i];
						}
						label[m]= (char*) malloc((j+1)*sizeof(char)+1);
						strcpy(label[m],aux);
						i++;
						//Passar os espaços vazios.
						x= linha[i];
						while(isblank(x) && flag!=2){
							i++;
							x= linha[i];
						}			
					//Zerar o vetor auxiliar.
						for(j=0; j<1000; j++)
							aux[j]=0;
						j=0, k=0;
				}
			//verificar o operador da instrução.
				if(flag!=2){
						PC++;
						while(!isblank(x) && x!='\n' && x!=EOF && j<6){
							aux[j]= linha[i];
							j++;
							i++;
							x= linha[i];
						}
						for(k=0;k<j;k++){
							operador[k]= aux[k];
						}		
				}
		//verificar os operandos da instrução.	
			//Caso sejam dois operandos.	
				if(flag!=2 && quant_operandos(operador)==2){
						PC+=2;
					//Passar os espaços vazios.
						while(isblank(x)){
							i++;
							x= linha[i];
						}			
					//Zerar o vetor auxiliar.
						for(j=0; j<1000; j++)
							aux[j]=0;
						j=0, k=0;
					//verificar o operando 1.
						while(!isblank(x)){
							aux[j]= linha[i];
							j++;
							i++;
							x= linha[i];
						}
						operando1[p]= (char*) malloc(j*sizeof(char)+1);
						strcpy(operando1[p], aux);
					//Passar os espaços vazios.
							while(isblank(x)){
							i++;
							x= linha[i];
						}			
					//Zerar o vetor auxiliar.
						for(j=0; j<1000; j++)
						aux[j]=0;
						j=0, k=0;
					//verificar o operando 2.
						while(!isblank(x) && x!= ';' && x!='\n' && x!=EOF){
							aux[j]= linha[i];
							j++;
							i++;
							x= linha[i];
						}
						operando2[q]= (char*) malloc(j*sizeof(char)+1);
						strcpy(operando2[q],aux);
					//Zerar o vetor auxiliar.
						for(j=0; j<1000; j++)
							aux[j]=0;
				}
			//Caso seja apenas um operando.	
				else if(flag!=2 && quant_operandos(operador)==1){
						PC++;
					//Passar os espaços vazios.
						while(isblank(x)){
							i++;
							x= linha[i];
						}			
					//Zerar o vetor auxiliar.
						for(j=0; j<1000; j++)
							aux[j]=0;
						j=0, k=0;
					//verificar o operando 1.
						while(!isblank(x) && x!= ';' && x!='\n' && x!=EOF){
							aux[j]= linha[i];
							j++;
							i++;
							x= linha[i];
						}
						operando1[p]= (char*) malloc(j*sizeof(char)+1);
						strcpy(operando1[p], aux);
					//Zerar o vetor auxiliar.
						for(j=0; j<1000; j++)
							aux[j]=0;
				}

			//Verificar o codigo numérico do operador a ser impresso no arquivo de saída.	
				if(flag!=2){
						cod= codigo_operador(operador);
					//Caso o operador seja WORD, o valor a ser impresso é o operando.
						if(cod==23){				
							cod=valor_label(label[m], tabela, r);
						}
					//Caso o operador seja END, o programa é finalizado
						if(cod==24){
							for(i=0; i< r; i++)
								free(tabela[i].rotulo); 	
							fclose(ent);
							fclose(saida);
							exit(0);
						}		
				}
			//Verificar o codigo numérico do operando a ser impresso no arquivo de saída.	
				if(flag!=2 && quant_operandos(operador)==1){
					op1= codigo_op(operando1[p]);
				}
				else if(flag!=2 && quant_operandos(operador)==2){
					op1= codigo_op(operando1[p]);
					op2= codigo_op(operando2[q]);
				}	
			//Caso o operando seja uma Label, será impresso a sua posição de memória em relação ao PC.	
				if(op1==100){
					op1=(endereco_label(operando1[p], tabela, r)-PC);
					if(op1==(-PC))
						op1= atoi(operando1[p]);
				}
				if (op2==100){
					op2=(endereco_label(operando2[q], tabela, r)-PC);
					if(op2==(-PC))
						op2= atoi(operando2[q]);
				}
			
			//IMPRESSÃO NO ARQUIVO DE SAÍDA.
				imprime_saida(operador, saida, cod, op1, op2);	
				
			//Desalocar memória utilizada no ciclo do loop.	
				if(flag==1){
					free(label[m]);
					m++;
				}
				if(flag!=2 && quant_operandos(operador)==1){
					free(operando1[p]);
					p++;
				}
				else if(flag!=2 && quant_operandos(operador)==2){
					free(operando1[p]);
					free(operando2[q]);
					p++;
					q++;
				}	
			//Zerar o vetor operador, o vetor linha e as variáveis.
				for(k=0;k<6;k++)
					operador[k]=0;
				for(k=0;k<1000;k++)
					linha[k]=0;
				flag=0, j=0, k=0, i=0;
		}	

	return 0;
}