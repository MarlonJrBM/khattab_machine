/* 
 * File:   khattab.h
 * Author: Marlon
 *
 * Created on 1 de Novembro de 2013, 22:46
 */

#ifndef KHATTAB_H
#define	KHATTAB_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif


#define SIZE 1000

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Memory 
{
    int mem[SIZE]; //memory vector
    int gpr[8]; //8 general purpose registers
    int pc, sp, psw; //3 special purpose registers
    //PSW=0 if OP>0. PSW=1 if OP=0. PSW=2 if OP<0
    bool halt; //signal for halt
} Memory;


//P -> Processor. R -> Register Number. M -> Memory Address. OP -> opcode
void Load(Memory* p, int r, int m);
void Store(Memory* p, int r, int m);


void Read(Memory* p, int r);
void Write(Memory* p, int r);
void Copy(Memory* p, int r1, int r2);
void OP(Memory* p, int r1, int r2, char op);
void Jump(Memory* p, int m, char op);


void Push (Memory* p, int r);
void Pop (Memory* p, int r);
void Call (Memory* p, int m);
void Ret(Memory* p);
void Halt(Memory* p);


void LoadProgram(Memory* p, FILE* f);



void RunMachine(Memory* p, bool verbose);

void PrintStatus(Memory* p, int opcode);


#endif	/* KHATTAB_H */

