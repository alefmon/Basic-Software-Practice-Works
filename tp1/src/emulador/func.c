#include "func.h"

void load(int r, int m, int* reg, int* mem, int PC, int inicio){
    reg[r]= mem[inicio+ m + PC];
}
void store(int r, int m, int* reg, int* mem, int PC, int inicio){
    mem[inicio+ m + PC]= reg[r];
}
void read(int r, int* reg, int valor){
    reg[r]= valor;
}
void write(int r, int* reg){
    printf("%d\n", reg[r]);
}
void copy(int r1, int r2, int* reg, int* PSW){
    reg[r1]= reg[r2];
    if(reg[r1]==0)
        PSW[0]=1;
    else
        PSW[0]=0;
    if(reg[r1]<0)
        PSW[1]=1;
    else
        PSW[1]=0;
}
void neg(int r1, int* reg, int* PSW){
    reg[r1]= -reg[r1];
    if(reg[r1]==0)
        PSW[0]=1;
    else
        PSW[0]=0;
    if(reg[r1]<0)
        PSW[1]=1;
    else
        PSW[1]=0;
}
void sub(int r1, int r2, int* reg, int* PSW){
    reg[r1]= reg[r1] - reg[r2];
    if(reg[r1]==0)
        PSW[0]=1;
    else
        PSW[0]=0;
    if(reg[r1]<0)
        PSW[1]=1;
    else
        PSW[1]=0;
}
void add(int r1, int r2, int* reg, int* PSW){
    reg[r1]= reg[r1] + reg[r2];
    if(reg[r1]==0)
        PSW[0]=1;
    else
        PSW[0]=0;
    if(reg[r1]<0)
        PSW[1]=1;
    else
        PSW[1]=0;
}
void and(int r1, int r2, int* reg, int* PSW){
    reg[r1]= reg[r1] & reg[r2];
    if(reg[r1]==0)
        PSW[0]=1;
    else
        PSW[0]=0;
    if(reg[r1]<0)
        PSW[1]=1;
    else
        PSW[1]=0;
}
 void or(int r1, int r2, int* reg, int* PSW){
    reg[r1]= reg[r1] | reg[r2];
    if(reg[r1]==0)
        PSW[0]=1;
    else
        PSW[0]=0;
    if(reg[r1]<0)
        PSW[1]=1;
    else
        PSW[1]=0;
 }
 void xor(int r1, int r2, int* reg, int* PSW){
    reg[r1]= reg[r1] ^ reg[r2];
    if(reg[r1]==0)
        PSW[0]=1;
    else
        PSW[0]=0;
    if(reg[r1]<0)
        PSW[1]=1;
    else
        PSW[1]=0;
 }
 void not(int r1, int* reg, int* PSW){
    reg[r1]= ~reg[r1];
    if(reg[r1]==0)
        PSW[0]=1;
    else
        PSW[0]=0;
    if(reg[r1]<0)
        PSW[1]=1;
    else
        PSW[1]=0;
 }
void jmp(int m, int* PC){
    (*PC)+=m;
}
void jz(int m, int* PSW, int* PC){
    if(PSW[0]==1)
        (*PC)+=m;
}
void jnz(int m, int* PSW, int* PC){
    if(PSW[0]==0)
        (*PC)+=m;
}
void jN(int m, int* PSW, int* PC){
    if(PSW[1]==1)
        (*PC)+=m;
}
void jnn(int m, int* PSW, int* PC){
    if(PSW[1]==0)
        (*PC)+=m;
}
void push(int r, int* SP, int* mem, int* reg, int inicio){
    (*SP)--;
    mem[inicio + *SP]= reg[r];
}
void pop(int r, int* SP, int* mem, int* reg, int inicio){
    reg[r]= mem[inicio+ *SP];
    (*SP)++;
}
void call(int m, int* SP, int* mem, int* PC, int inicio){
    (*SP)--;
    mem[inicio+ *SP]= *PC;
    (*PC)+= m;
}
void ret(int* PC, int* mem, int* SP, int inicio){
    *PC= mem[inicio+ *SP];
    (*SP)++;
} 
void halt(){
    exit(0);
}