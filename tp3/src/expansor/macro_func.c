#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#include <ctype.h>
#include "macro_func.h"

void tabela_macros(FILE* ent, char** label, char** arquivo, char** operando1, simbolos* tabela, int* quant_macros){

//Declaração de variáveis.
	int r=0, i=0, j=0, k=0, m=0, p=0, flag=0, flag_operando=0, linha_lida=1;
	int tamanho_inst=0;
	char operador[11];
	char x,linha[1000]={0}, aux[1000]={0};
	char *begin="BEGINMACRO", *espaco="  ";

//Leitura de cada linha do arquivo de entrada (uma por ciclo).
	while(fgets(linha,1000,ent)!= NULL){

			//Copiar o conteúdo da entrada para o vetor arquivo.
				arquivo[linha_lida]= (char*) malloc (sizeof(linha));
				strcpy(arquivo[linha_lida],linha);
			//verificar o conteúdo da linha.
				for(i=0;i< 1000; i++){
					// FLAG= 1 -> Há label ou macro na instrução.
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
			//Caso a linha tenha apenas comentários ou esteja vazia, o conteúdo deve ser ignorado.
				if(flag==2){
					strcpy(arquivo[linha_lida],espaco);
				}
			//Passar os espaços vazios da linha.
				x= linha[i];
				while(isblank(x) && flag!=2){
					i++;
					x= linha[i];
				}
			//Se FLAG= 1, verificar a label ou macro da instrução.
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
			//verificar se o operador da instrução indica o inicio de uma macro. Caso indique, a label na verdade é uma macro.
				if(flag==1){
					//Verifica o operador.
						while(!isblank(x) && x!='\n' && x!=EOF && j<11){
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
					//Caso o operador seja BEGINMACRO, armazena o endereço da macro.
						if(strcmp(operador,begin)==0){
							//Passar os espaços vazios.
								while(isblank(x) && x!= ';' && x!='\n' && x!=EOF){
									i++;
									x= linha[i];
								}								
							//verificar o operando da MACRO.
								while(!isblank(x) && x!= ';' && x!='\n' && x!=EOF){
									aux[j]= linha[i];
									j++;
									i++;
									x= linha[i];
									flag_operando=1;
								}
							//Caso a Macro tenha operando, identifica-lo.	
								if(flag_operando==1){
										operando1[p]= (char*) malloc(j*sizeof(char)+1);
										strcpy(operando1[p], aux);
									//Aloca o valor do operando na tabela de MACROS.
										tabela[r].op= (char*) malloc(j*sizeof(char)+1);	
										strcpy(tabela[r].op,operando1[p]);
										free(operando1[p]);
										p++;
								}
								else
									tabela[r].op=NULL;
							//Zerar o vetor auxiliar.
								for(j=0; j<1000; j++)
									aux[j]=0;
								j=0, k=0;
							//adiciona a macro na tabela de simbolos.
								tabela[r].nome= (char*) malloc(j*sizeof(char)+1);
								strcpy(tabela[r].nome,label[m]);
							//adiciona o endereço da label na tabela de símbolos.
								tabela[r].endereco= linha_lida;
								(*quant_macros)++;
						}					
				}	
			//Se houve label ou macro na linha, desaloca a memória.	
				if(flag==1){
					free(label[m]);
					m++;
				}	
				if(strcmp(operador,begin)==0)
					r++;
			//Zerar o vetor operador, o vetor linha e as variáveis.
				for(k=0;k<11;k++)
					operador[k]=0;
				for(k=0;k<1000;k++)
					linha[k]=0;
				flag=0, j=0, k=0, i=0, tamanho_inst=0, flag_operando=0;

				linha_lida++;
	}
}

void imprime(FILE* saida, char** arquivo, simbolos* tabela, int linhas_arquivo, int quant_macros){
	int i=1, j=0, k=0, m=0, p=0, q=0, flag_macro=0, flag_label=0, posicao_macro=0, flag=0, flag_chamada_macro=0, flag_espaco=0;
	char x, aux[1000]={0};
	char *operador[linhas_arquivo], *operando[linhas_arquivo];
	char *label, *auxiliar;
	for(i=1; i<=linhas_arquivo; i++){
			//verificar o conteúdo da linha.
				for(j=0;j< 1000; j++){
					// FLAG= 1 -> Há label ou macro na instrução.
					if(arquivo[i][j]==':')
						flag=1;
					// FLAG= 2 -> A linha só contém comentários ou está vazia.
					if(arquivo[i][j]==';' && flag==0)
						flag=2;
					if(arquivo[i][j]=='\n' && flag==0)
						flag=2;				
					// FLAG= 3 -> A linha tem uma instrução, mas não contém Label.
					if(!isblank(arquivo[i][j]) && flag!=1 && flag!=2)
						flag=3; 
				}
				j=0;
		//Passar os espaços vazios.
			x= arquivo[i][j];
			while(isblank(x) && x!='\n' && x!=EOF){
				j++;
				x= arquivo[i][j];
			}			
		//Verifica se é label ou macro na linha.	
			if(flag==1){
				posicao_macro= verifica_macro(arquivo[i], tabela, quant_macros);
			//Caso seja uma macro.	
				if(posicao_macro!= -1){
					//ignora as linhas até o ENDMACRO.
					i=tamanho_macro(saida, arquivo, posicao_macro, linhas_arquivo);
					flag_macro=1;
				}	
			//Se for uma label.	
				else{
				//Passar o espaço ocupado pela label.
					x= arquivo[i][j];
					while(!isblank(x)){
						j++;
						x= arquivo[i][j];
					}	
					//Passar os espaços vazios.
					x= arquivo[i][j];
					while(isblank(x) && x!='\n' && x!=EOF){
						j++;
						x= arquivo[i][j];
					}	
				}
			}
		//Se não houve declaração de macro na linha, verificar se o operador não é uma chamada para macro.	
			if(flag_macro!=1){
				//verificar o operador.
				while(!isblank(x) && x!='\n' && x!=EOF && x!='\0'){
					aux[k]= arquivo[i][j];
					j++;
					k++;
					x= arquivo[i][j];
				}
				operador[m]= (char*) malloc(k*sizeof(char)+1);
				strcpy(operador[m], aux);
				j++;
				m++;
			//Caso o operador seja uma chamada para macro.
				for(j=0; j<quant_macros; j++){
					if(strcmp(tabela[j].nome, operador[m-1])==0){
						//Caso haja uma label antes do BEGINMACRO, ela deve ser impressa.
						if(flag==1){
							auxiliar= nome_label(arquivo[i], tabela, quant_macros);
							label= (char*) malloc(sizeof(auxiliar));
							strcpy(label, auxiliar);
							fprintf(saida, "%s: ", label);
							free(label);
						}	
						//Caso a macro necessite de um operando.
						if(tabela[j].op!=0){
								x= arquivo[i][q];
							//Passar os espaços em branco.	
								while(isblank(x) && x!='\n' && x!=EOF && x!='\0'){
									q++;
									x= arquivo[i][q];
								}
							//Passar os espaços ocupados pela label.	
								if(flag==1){
									while(!isblank(x) && x!='\n' && x!=EOF && x!='\0'){
										q++;
										x= arquivo[i][q];
									}
									//Passar os espaços em branco.	
									while(isblank(x) && x!='\n' && x!=EOF && x!='\0'){
										q++;
										x= arquivo[i][q];
									}
								}	
							//Passar os espaços ocupados pelo operador.	
								while(!isblank(x) && x!='\n' && x!=EOF && x!='\0'){
									q++;
									x= arquivo[i][q];
								}
							//Passar os espaços em branco.	
								while(isblank(x) && x!='\n' && x!=EOF && x!='\0'){
									q++;
									x= arquivo[i][q];
								}	
							//Zerar o vetor auxiliar.
								for(k=0; k<1000; k++)
									aux[k]=0;
								k=0;
							//Verificar o operando da instrução.	
								while(!isblank(x) && x!='\n' && x!=EOF && x!='\0'){
									aux[k]= arquivo[i][q];
									q++;
									k++;
									x= arquivo[i][q];
								}
								operando[p]= (char*) malloc(k*sizeof(char)+1);
								strcpy(operando[p], aux);
								q++;
								p++;
							//Imprimir a Macro que foi chamada.	
								imprime_macro(saida, arquivo, tabela[j].endereco, linhas_arquivo, tabela[j].op, operando[p-1],tabela[j].chamadas);
								flag_chamada_macro=1;
								free(operando[p-1]);
								q=0;
						}	
						//Caso a macro não exija um operando, imprimir a Macro chamada.
						else{
							imprime_macro(saida, arquivo, tabela[j].endereco, linhas_arquivo, tabela[j].op, operando[p-1], tabela[j].chamadas);
							flag_chamada_macro=1;
						}
						tabela[j].chamadas++;
					}
				}		
				free(operador[m-1]);
			//Caso não haja chamada para macro, imprimir a linha original. 
				if(flag_chamada_macro!=1){
					j=0;
					while(arquivo[i][j]!='\n' && arquivo[i][j]!='\0'){
						if(!isblank(arquivo[i][j]) || flag_espaco==1){
							fprintf(saida, "%c", arquivo[i][j]);
							flag_espaco=1;
						}	
						j++;
					}
					if(flag_espaco==1)
						fprintf(saida, "\n");
				}
			}		

		//Zerar o vetor auxiliar.
			for(j=0; j<1000; j++)
				aux[j]=0;
			j=0, k=0;
			posicao_macro=0;
			flag_chamada_macro=0;
			flag_macro=0;
			flag_label=0;
			flag_espaco=0;
			flag=0;
	}
}

int verifica_macro(char* arquivo_i, simbolos* tabela, int quant_macros){
	char x;
	int j=0, k=0;
	char aux[1000]={0};
	char* macro;
			//Passar os espaços vazios da linha.
				x= arquivo_i[j];
				while(isblank(x)){
					j++;
					x= arquivo_i[j];
				}
			//Verificar a label ou macro da instrução.
				while(x!=':'){
							aux[k]= arquivo_i[j];
							k++;
							j++;
							x= arquivo_i[j];		
				}
				macro= (char*) malloc(j*sizeof(char)+1);
				strcpy(macro, aux);
			//Retornar a posição da macro no vetor Arquivo.	
				for(j=0; j<quant_macros; j++){
					if(strcmp(tabela[j].nome, macro)==0)
						return (tabela[j].endereco);
				}
				return (-1);

}

char* nome_label(char* arquivo_i, simbolos* tabela, int quant_macros){
	char x;
	int j=0, k=0;
	char aux[1000]={0};
	char* label;
			//Passar os espaços vazios da linha.
				x= arquivo_i[j];
				while(isblank(x)){
					j++;
					x= arquivo_i[j];
				}
			//Verificar a label ou macro da instrução.
				while(x!=':'){
							aux[k]= arquivo_i[j];
							k++;
							j++;
							x= arquivo_i[j];		
				}
				label= (char*) malloc(j*sizeof(char)+1);
				strcpy(label, aux);
			//Retornar o nome da label.	
				return (label);

}

char* operando_macro(char* arquivo_i, simbolos* tabela, int quant_macros){
	char x;
	int j=0, k=0;
	char aux[1000]={0};
	char* macro;
			//Passar os espaços vazios da linha.
				x= arquivo_i[j];
				while(isblank(x)){
					j++;
					x= arquivo_i[j];
				}
			//Verificar a label ou macro da instrução.
				while(x!=':'){
							aux[k]= arquivo_i[j];
							k++;
							j++;
							x= arquivo_i[j];		
				}
				macro= (char*) malloc(j*sizeof(char)+1);
				strcpy(macro, aux);
			//Retornar o operando esperado pela Macro.	
				for(j=0; j<quant_macros; j++){
					if(strcmp(tabela[j].nome, macro)==0)
						return (tabela[j].op);
				}
				return 0;

}


void imprime_macro(FILE* saida, char** arquivo, int posicao_macro, int linhas_arquivo, char* macro_op, char* chamada_op, int num_chamadas){
	char* endMacro= "ENDMACRO", *auxiliar=NULL, *operando1=NULL, *operando2=NULL, *label=NULL;
	int i=1, j=0, k=0, m=0, p=0, flag=0;
	label= (char*) malloc(sizeof(arquivo[posicao_macro + i]));
	auxiliar= (char*) malloc(sizeof(arquivo[posicao_macro + i]));
	operando1= (char*) malloc(sizeof(arquivo[posicao_macro + i]));
	operando2= (char*) malloc(sizeof(arquivo[posicao_macro + i]));
//inicializar os vetores.	
	for(j=0;j<(posicao_macro +i); j++){
		auxiliar[j]=0;
		operando1[j]=0;
		operando2[j]=0;
	}
	j=0;	
//verificar o conteúdo da linha.
	for(j=0;j< 1000; j++){
		// FLAG= 1 -> Há label ou macro na instrução.
			if(arquivo[posicao_macro + i][j]==':')
				flag=1;
		// FLAG= 2 -> A linha só contém comentários ou está vazia.
			if(arquivo[posicao_macro + i][j]==';' && flag==0)
				flag=2;
			if(arquivo[posicao_macro + i][j]=='\n' && flag==0)
				flag=2;				
		// FLAG= 3 -> A linha tem uma instrução, mas não contém Label.
			if(!isblank(arquivo[posicao_macro + i][j]) && flag!=1 && flag!=2)
				flag=3; 
	}
	j=0;
//Caso a linha contenha alguma label.	
	if(flag==1){
		while(isblank(arquivo[posicao_macro + i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
			k++;
		}
		while(arquivo[posicao_macro +i][k]!=':' && !isblank(arquivo[posicao_macro +i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
			label[j]= arquivo[posicao_macro + i][k];
			j++;
			k++;
		}
	}
//Verificar a instrução da linha e alocar na string auxiliar.
	while(isblank(arquivo[posicao_macro + i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
		k++;
	}
	while(!isblank(arquivo[posicao_macro +i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
		auxiliar[j]= arquivo[posicao_macro + i][k];
		j++;
		k++;
	}
	while(isblank(arquivo[posicao_macro + i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
		k++;
	}
	while(!isblank(arquivo[posicao_macro +i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
		operando1[m]= arquivo[posicao_macro + i][k];
		m++;
		k++;	
	}	
	while(isblank(arquivo[posicao_macro + i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
		k++;
	}
	while(!isblank(arquivo[posicao_macro +i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
		operando2[p]= arquivo[posicao_macro + i][k];
		p++;
		k++;	
	}	
	j=0;
	k=0;
	m=0;
	p=0;	
//Imprimir as linhas da Macro até encontrar o ENDMACRO.	
	while(strcmp(auxiliar, endMacro)!=0 && (posicao_macro + i)<= linhas_arquivo){		
		//Se tiver label, imprimir a label.
			if(flag==1){
				if(num_chamadas>1)
					fprintf(saida, "%s%d: ", label, num_chamadas);	
				else
					fprintf(saida, "%s: ", label);	
			}			
		//Imprimir o operador.	
			fprintf(saida, "%s ", auxiliar);
		//Caso um dos operandos seja o mesmo operando da Macro imprimir o valor passado como argumento na chamada da Macro.	
			if(operando1!=NULL){
				if(macro_op!=NULL && strcmp(operando1, macro_op)==0)
					fprintf(saida, "%s ", chamada_op);	
				else
					fprintf(saida, "%s ", operando1);
			}
			if(operando2!=NULL){
				if(macro_op!=NULL && strcmp(operando2, macro_op)==0)
					fprintf(saida, "%s ", chamada_op);	
				else
					fprintf(saida, "%s ", operando2);
			}
			fprintf(saida, "\n");
			i++;
			j=0;
			flag=0; 
			label= malloc(sizeof(arquivo[posicao_macro + i]));
			auxiliar= malloc(sizeof(arquivo[posicao_macro + i])); 
			operando1= (char*) malloc(sizeof(arquivo[posicao_macro + i]));
			operando2= (char*) malloc(sizeof(arquivo[posicao_macro + i]));
		//verificar o conteúdo da linha.
			for(j=0;j< 1000; j++){
				// FLAG= 1 -> Há label ou macro na instrução.
					if(arquivo[posicao_macro + i][j]==':')
						flag=1;
				// FLAG= 2 -> A linha só contém comentários ou está vazia.
					if(arquivo[posicao_macro + i][j]==';' && flag==0)
						flag=2;
					if(arquivo[posicao_macro + i][j]=='\n' && flag==0)
						flag=2;				
				// FLAG= 3 -> A linha tem uma instrução, mas não contém Label.
					if(!isblank(arquivo[posicao_macro + i][j]) && flag!=1 && flag!=2)
						flag=3; 
			}
			j=0;
		//Caso a linha contenha alguma label.	
			if(flag==1){
				while(isblank(arquivo[posicao_macro + i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
					k++;
				}
				while(arquivo[posicao_macro +i][k]!=':' && !isblank(arquivo[posicao_macro +i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
					label[j]= arquivo[posicao_macro + i][k];
					j++;
					k++;
				}
			}
			//Verificar a instrução da próxima linha.
			while(isblank(arquivo[posicao_macro + i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
				k++;
			}
			while(!isblank(arquivo[posicao_macro +i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
				auxiliar[j]= arquivo[posicao_macro + i][k];
				j++;
				k++;
			}
			while(isblank(arquivo[posicao_macro + i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
				k++;
			}
			while(!isblank(arquivo[posicao_macro +i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
				operando1[m]= arquivo[posicao_macro + i][k];
				m++;
				k++;	
			}	
			while(isblank(arquivo[posicao_macro + i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
				k++;
			}
			while(!isblank(arquivo[posicao_macro +i][k]) && arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
				operando2[p]= arquivo[posicao_macro + i][k];
				p++;
				k++;	
			}	
			j=0;
			k=0;
			m=0;
			p=0;
	}	
	free(label);
	free(auxiliar);
	free(operando1);
	free(operando2);
}


int tamanho_macro(FILE* saida, char** arquivo, int posicao_macro, int linhas_arquivo){
	char* endMacro= "ENDMACRO", *auxiliar;
	int i=1, j=0, k=0, flag=0;
	auxiliar= (char*) malloc(sizeof(arquivo[posicao_macro + i]));
//Armazenar a instrução da linha no vetor auxiliar.	
	while(arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
		if(!isblank(arquivo[posicao_macro +i][k]) || flag==1){
			auxiliar[j]= arquivo[posicao_macro + i][k];
			j++;
			flag=1;
		}
		k++;
		flag=0;
	}	
	k=0;
	j=0;
//Verificar em qual linha a instrução é a ENDMACRO. 	
	while(strcmp(auxiliar, endMacro)!=0 && (posicao_macro + i)< linhas_arquivo){
		i++;
		auxiliar= malloc(sizeof(arquivo[posicao_macro + i])); 
		while(arquivo[posicao_macro +i][k]!='\n' && arquivo[posicao_macro +i][k]!='\0'){
			if(!isblank(arquivo[posicao_macro +i][k]) || flag==1){
				auxiliar[j]= arquivo[posicao_macro + i][k];
				j++;
				flag=1;
			}
			k++;
			flag=0;
		}	
		j=0;
		k=0;
	}
	free(auxiliar);
//Retorna a posição da instrução ENDMACRO.	
	return (posicao_macro +i);

}
