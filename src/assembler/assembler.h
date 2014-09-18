/*
 * assembler.h
 *
 *  Created on: Nov 22, 2013
 *      Author: marlon
 */

#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

#define SIZE 1024
#define NOTFOUND 666666
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>




//Struct used to represent the Khattab Machine
typedef struct Memory
{
    int mem[SIZE]; //memory vector
    int gpr[8]; //8 general purpose registers
    int pc, sp, psw; //3 special purpose registers
    //PSW=0 if OP>0. PSW=1 if OP=0. PSW=2 if OP<0
    bool halt; //signal for halt
} Memory;


typedef struct TipoItem {
    char* key;
    //int length;
    int id;
}TipoItem;

typedef struct TipoCelula *TipoApontador;

struct TipoCelula {
    TipoItem Item;
    TipoApontador Prox;
}TipoCelula;

typedef struct TipoLista {
        int ID;
        int size;
        int Conjuge;
        int Posicao;
        TipoApontador Primeiro, Ultimo;
} TipoLista;


int Busca(char *Chave, TipoLista Lista);
/*
*Faz a lista vazia
*Parametros:
*        *lista
*/
void FLVazia(TipoLista *Lista);
/*
*Verifica se a lista esta vazia
*Parametros:
*        * lista
*/
short Vazia(TipoLista Lista);
/*
*Insere um item generico na lista
*Parametros:
*        * lista
*        * item - item a ser inserido
*/
void Insere(TipoItem *x, TipoLista *Lista);
/*
*Remove um item da lista, retorna um apontador para o item removido
*Parametros:
*        *lista
*        *item_anterior - apontador para a celula do item anterior ao que deve ser removido
*/
void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item);

/*
* Desfaz uma lista encadeada por apontadores
*Parametros:
* Lista
*/
void DesfazLista(TipoLista *Lista);

/*
*Imprime os items armazenados na fila
*Parametros:
*        * lista
*
*/
void ImprimeLista(FILE* stream, TipoLista Lista);

/*
* Aloca arranjo do TipoLista
*Parametros
* n - numero de listas
*/
TipoLista* AlocaListas(int n);

/* Desaloca arranjo do TipoLista
*Parametros
* n - numero de listas
* *Lista - arranjo do tipo lista
*/
void DesalocaListas(int n, TipoLista *Lista);




//Functions to read from file
//------------------------------------------------------------------------
char* ReadLine(FILE *file);

char* NextWord(char *line);

char** SplitLine(char *line);
//------------------------------------------------------------------------

//Functions to initialize the tables

void InsertOpcode(TipoLista *t, char* opcode, int code);

void CreateOpcodeTable(TipoLista *t, int n);

int OperatorAux(char* op);

//Function that carries out the first pass of the assembler
void PassOne(FILE* f, TipoLista* symTable, TipoLista* lenTable, bool verbose);

//Function that carries out the second pass of the assembler
void PassTwo(FILE* input, FILE* output,
        Memory* p, TipoLista symTable, TipoLista opTable,
        TipoLista lenTable, TipoLista *refTable);

bool PassTwoAux(char *line, Memory* p, TipoLista symTable, TipoLista opTable,
        TipoLista lenTable, TipoLista *refTable);

void CreateFile(FILE* f, Memory p);



#endif /* ASSEMBLER_H_ */
