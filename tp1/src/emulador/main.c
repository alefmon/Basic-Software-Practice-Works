#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "func.h"

int main(int argc, char *argv[]){
	
	int mem[1000], reg[16], inicio, PC, SP, PSW[2]={0, 0}, i=0, comando, r, r1, r2, m, cont=0;
	char* saida;
	//Zerar a memória e os registradores.
	for(i=0; i<1000; i++){
		mem[i]=0;
		if(i<16)
			reg[i]=0;
	}	
	//Alocar os argumentos recebidos pela entrada.
	PC= atoi(argv[1]);
	SP= atoi(argv[2]);
	inicio= atoi(argv[3]);
	FILE* f;
	f= fopen(argv[4], "r");
	saida= (argv[5]);
	i=0;
	//Armazenar todas as instruções e operandos do arquivo na memória.
	while((fscanf(f, "%d", &comando))!=EOF){
		mem[inicio+i]= comando;
		i++;
		cont++;
	}
	printf("%d\n", cont);
	fclose(f);
	//Leitura da memória e execução das instruções, a partir da posição de PC.
	while(PC<cont){
		int valor;
		//O comando switch avalia a próxima e instrução e direciona o programa para a função correspondente.
		switch(mem[inicio+PC]){
			
			case 1: 
				// Executa a instruçao LOAD.
				if(*saida=='v'){
					printf("Instrucao executada: LOAD\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
					printf("\n");
				}	
				PC++;
				r= mem[inicio+PC];
				PC++;
				m= mem[inicio+PC];
				PC++;
				load(r, m, reg, mem, PC, inicio);
				break;
			case 2:
				// Executa a instruçao STORE.
				if(*saida=='v'){
					printf("Instrucao executada: STORE\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
					printf("\n");
				}	
				PC++;
				r= mem[inicio+PC];
				PC++;
				m= mem[inicio+PC];
				PC++;
				store(r, m, reg, mem, PC, inicio);
				break;
			case 3:	
				// Executa a instruçao READ.
				if(*saida=='v'){
					printf("Instrucao executada: READ\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
					printf("\n");
				}	
				PC++;
				r= mem[inicio+PC];
				PC++;
				scanf("%d", &valor);
				read(r, reg, valor);
				break;
			case 4:	
				// Executa a instruçao WRITE.
				if(*saida=='v'){
					printf("Instrucao executada: WRITE\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
					printf("\nSAIDA->-> ");
				}	
				PC++;
				r= mem[inicio+PC];
				PC++;
				write(r, reg);
				break;
			case 5:
				// Executa a instruçao COPY.
				if(*saida=='v'){
					printf("Instrucao executada: COPY\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
					printf("\n");
				}
				PC++;
				r1= mem[inicio+PC];
				PC++;
				r2= mem[inicio+PC];
				PC++;
				copy(r1, r2, reg, PSW);
				break;
			case 6:
				// Executa a instruçao NEG.
				if(*saida=='v'){
					printf("Instrucao executada: NEG\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
					printf("\n");
				}
				PC++;
				r1= mem[inicio+PC];
				PC++;
				neg(r1, reg, PSW);
				break;
			case 7:
				// Executa a instruçao SUB.
				if(*saida=='v'){
					printf("Instrucao executada: SUB\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);	
					printf("\n");
				}
				PC++;
				r1= mem[inicio+PC];
				PC++;
				r2= mem[inicio+PC];
				PC++;
				sub(r1, r2, reg, PSW);			
					break;
			case 8:
				// Executa a instruçao ADD.
				if(*saida=='v'){
					printf("Instrucao executada: ADD\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
				printf("\n");
				}
				PC++;
				r1= mem[inicio+PC];
				PC++;
				r2= mem[inicio+PC];
				PC++;
				add(r1, r2, reg, PSW);			
				break;
			case 9:	
				// Executa a instruçao AND.
				if(*saida=='v'){
					printf("Instrucao executada: AND\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
					printf("\n");
				}
				PC++;
				r1= mem[inicio+PC];
				PC++;
				r2= mem[inicio+PC];
				PC++;
				and(r1, r2, reg, PSW);
				break;
			case 10:	
				// Executa a instruçao OR.
				if(*saida=='v'){
					printf("Instrucao executada: OR\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
		
					printf("\n");
				}
				PC++;
				r1= mem[inicio+PC];
				PC++;
				r2= mem[inicio+PC];
				PC++;
				or(r1, r2, reg, PSW);
				break;
			case 11:
				// Executa a instruçao XOR.
				if(*saida=='v'){
					printf("Instrucao executada: XOR\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
				
				printf("\n");
				}
				PC++;
				r1= mem[inicio+PC];
				PC++;
				r2= mem[inicio+PC];
				PC++;
				xor(r1, r2, reg, PSW);
				break;
			case 12:
				// Executa a instruçao NOT.
				if(*saida=='v'){
					printf("Instrucao executada: NOT\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
				for(i=0; i<16; i++)
					printf("R%d(%d) ", i, reg[i]);	
			
				printf("\n");
				}
				PC++;
				r1= mem[inicio+ PC];
				PC++;
				not(r1, reg, PSW);
				break;
			case 13:
				// Executa a instruçao JMP.
				if(*saida=='v'){
					printf("Instrucao executada: JMP\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
					printf("\n");
				}
				PC++;
				m= mem[inicio+PC];
				PC++;
				jmp(m, &PC);
				break;
			case 14:	
				// Executa a instruçao JZ.
				if(*saida=='v'){
					printf("Instrucao executada: JZ\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
					printf("\n");
				}
				PC++;
				m= mem[inicio+PC];
				PC++;
				jz(m, PSW, &PC);
					break;
			case 15:	
				// Executa a instruçao JNZ.
					if(*saida=='v'){
					printf("Instrucao executada: JNZ\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
				printf("\n");
				}
				PC++;
				m=mem[inicio+PC];
				PC++;
				jnz(m, PSW, &PC);
				break;
			case 16:
				// Executa a instruçao JN.
				if(*saida=='v'){
					printf("Instrucao executada: JN\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
					printf("\n");
				}
				PC++;
				m= mem[inicio+PC];
				PC++;
				jN(m, PSW, &PC);
				break;
			case 17:	
				// Executa a instruçao JNN.
				if(*saida=='v'){
					printf("Instrucao executada: JNN\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
				
					printf("\n");
				}
				PC++;
				m= mem[inicio+PC];
				PC++;
				jnn(m, PSW, &PC);
				break;
			case 18:
				// Executa a instruçao PUSH.
				if(*saida=='v'){
					printf("Instrucao executada: PUSH\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
					printf("\n");
				}
				PC++;
				r= mem[inicio+PC];
				PC++;
				push(r, &SP, mem, reg, inicio);
				break;
			case 19:	
				// Executa a instruçao POP.
				if(*saida=='v'){
					printf("Instrucao executada: POP\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
					printf("\n");
				}
				PC++;
				r= mem[inicio+PC];
				PC++;
				pop(r, &SP, mem, reg, inicio);
				break;
			case 20:
				// Executa a instruçao CALL.
				if(*saida=='v'){
				printf("Instrucao executada: CALL\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
					printf("R%d(%d) ", i, reg[i]);
				printf("\n");
				}
				PC++;
				m= mem[inicio+PC];
				PC++;
				call(m, &SP, mem, &PC, inicio);
				break;
			case 21:
				// Executa a instruçao RET.
				if(*saida=='v'){
					printf("Instrucao executada: RET\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
					printf("\n");
				}
				PC++;
				ret(&PC, mem, &SP, inicio);
				break;
			case 22:	
				// Executa a instruçao HALT.
				if(*saida=='v'){
					printf("Instrucao executada: HALT\nPC-> %d\nSP-> %d\nPSW-> (%d, %d)\nRegistradores: ", PC, SP, PSW[0], PSW[1]);
					for(i=0; i<16; i++)
						printf("R%d(%d) ", i, reg[i]);
					printf("\n");
				}
				PC++;
				halt();	
				break;
		}
	}
	return 0;
}