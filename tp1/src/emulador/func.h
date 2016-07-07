#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#ifndef FUNC_H
#define FUNC_H

//Carrega o valor contido em uma posição de memória e o armazena em um registrador.
void load(int r, int m, int* reg, int* mem, int PC, int inicio);

//Armazena o conteúdo do registrador em uma posição de memória.
void store(int r, int m, int* reg, int* mem, int PC, int inicio);

//Armazena o valor inserido pelo usuário em um registrador.
void read(int r, int* reg, int valor);

//Escreve o o conteúdo do registrador.
void write(int r, int* reg);

//Copia o conteúdo do registrador 2 para o registrador 1.
void copy(int r1, int r2, int* reg, int* PSW);

//Inverte o sinal do conteúdo do registrador.
void neg(int r1, int* reg, int* PSW);

//Subtrai o registrador r2 do registrador r1 e armazena o resultado no registrador r1.    
void sub(int r1, int r2, int* reg, int* PSW);

//Soma os registradores r1 e r2, depois armazena o resultado em r1.
void add(int r1, int r2, int* reg, int* PSW);

//Faz AND(bit a bit) dos registradores r1 e r2.
void and(int r1, int r2, int* reg, int* PSW);

//Faz OR(bit a bit) dos registradores r1 e r2.
void or(int r1, int r2, int* reg, int* PSW);

//Faz XOR(bit a bit) dos registradores r1 e r2.
void xor(int r1, int r2, int* reg, int* PSW);

//Faz AND(bit a bit) dos registradores r1 e r2.
void not(int r1, int* reg, int* PSW);

//Desvia para a instrução da posiçao de memória [PC+m].
void jmp(int m, int* PC);

//Se a última operação resultou em zero, desvia para a instrução da posiçao de memória [PC+m].
void jz(int m, int* PSW, int* PC);

//Se a última operação NÃO resultou em zero, desvia para a instrução da posiçao de memória [PC+m].
void jnz(int m, int* PSW, int* PC);

//Se a última operação resultou em valor negativo, desvia para a instrução da posiçao de memória [PC+m].
void jN(int m, int* PSW, int* PC);

//Se a última operação NÃO resultou em valor negativo, desvia para a instrução da posiçao de memória [PC+m].
void jnn(int m, int* PSW, int* PC);

//Empilha o valor do registrador.
void push(int r, int* SP, int* mem, int* reg, int inicio);

//Desempilha o valor do registrador.
void pop(int r, int* SP, int* mem, int* reg, int inicio);

//Chama subrotina da posição de memória[PC+m].
void call(int m, int* SP, int* mem, int* PC, int inicio);

//Retorna da subrotina e volta para a posição de memória armazenada em mem[SP].
void ret(int* PC, int* mem, int* SP, int inicio);

//Instrução de parada.
void halt();

#endif
