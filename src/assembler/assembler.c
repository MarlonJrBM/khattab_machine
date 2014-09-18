
/*
 * assembler.c
 *
 *  Created on: Nov 22, 2013
 *      Author: marlon
 */


#include "assembler.h"


/*
 * Below functions related to the data structured utilized to implement
 * the assembler: a simple linked list. The code was taken from Ziviani's book
*/

//------------------------------------------------------------------------

void FLVazia(TipoLista *Lista)
{ Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
  Lista->size = 0;
}

/*
*Verifica se a lista esta vazia
*Parametros:
*        * lista
*/

short Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}

/*
*Insere um item generico na lista
*Parametros:
*        * lista
*        * item - item a ser inserido
*/

void Insere(TipoItem *x, TipoLista *Lista)
{ /*-- Insere depois do ultimo item da lista --*/
  Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = *x;
  Lista->Ultimo->Prox = NULL;
  (Lista->size)++;
}

/*
*Remove um item da lista, retorna um apontador para o item removido
*Parametros:
*        *lista
*        *item_anterior - apontador para a celula do item anterior ao que deve ser removido
*/

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ /*--Obs.: item a ser retirado e o seguinte ao apontado por p--*/
  TipoApontador q;
  if (Vazia(*Lista) || p == NULL || p->Prox == NULL)
  { printf("Erro: Lista vazia ou posicao nao existe\n");
    return;
  }
  q = p->Prox;
  *Item = q->Item;
  p->Prox = q->Prox;
  if (p->Prox == NULL) Lista->Ultimo = p;
  free(q);
}
/*
*Desfaz uma lista encadeada por apontadores
*Parametros:
* Lista
*/

int Busca(char *key, TipoLista Lista){
    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL){
        if(strcmp(Aux->Item.key, key)==0)
            return Aux->Item.id;
      Aux = Aux->Prox;
    }
    return NOTFOUND;
}

void DesfazLista(TipoLista *Lista){
        TipoApontador Aux;
        TipoItem Item;
        Aux=Lista->Primeiro;
        while(!Vazia(*Lista)){
                if(Aux!=NULL){
                while(Aux->Prox->Prox!=NULL){
                Aux=Aux->Prox;
                }
                Retira(Aux,Lista,&Item);
                Aux=Lista->Primeiro;
                }
        }
        free(Lista->Primeiro);
}


/*
* Aloca arranjo do TipoLista
*Parametros
* n - numero de listas
*/

TipoLista* AlocaListas(int n){
        int i;
        TipoLista *Lista;
        Lista=(TipoLista*)calloc(n,sizeof(TipoLista));
        for(i=0;i<n;i++)
                FLVazia(&Lista[i]);

        return Lista;

}

/* Desaloca arranjo do TipoLista
*Parametros
* n - numero de listas
* *Lista - arranjo do tipo lista
*/

void DesalocaListas(int n, TipoLista *Lista){
        int i;
        for(i=0;i<n;i++)
                DesfazLista(&Lista[i]);

        free(Lista);
}


/*
*Imprime os items armazenados na fila
*Parametros:
*        * lista
*
*/

void ImprimeLista(FILE* stream, TipoLista Lista)
{ TipoApontador Aux;
  Aux = Lista.Primeiro->Prox;
  while (Aux != NULL)
    { fprintf(stream, "%s %d\n", Aux->Item.key, Aux->Item.id);
      Aux = Aux->Prox;
    }
}



//------------------------------------------------------------------------

/*
 * Below functions related to reading the input from file.
 * All were taken from the World Wide Web. Note: Memory MUST be 
 * deallocated outside the function
*/

//------------------------------------------------------------------------
char* ReadLine(FILE *file){
    int CUR_MAX = 4095;
    char *buffer = (char*) calloc(CUR_MAX,sizeof(char)); // allocate buffer.
    int count = 0;
    int length = 0;
    char ch='A';
    while ( (ch != '\n') && (ch != EOF) ) {
        if(count ==CUR_MAX) { // time to expand ?
            CUR_MAX *= 2; // expand to double the current size of anything similar.
            count = 0;
            buffer = realloc(buffer, CUR_MAX); // re allocate memory
        }
        ch = getc(file); // read from stream.
        buffer[length] = ch; // stuff in buffer.
        length++;
        count++;
    }
    return buffer;
}

char* NextWord(char *line){
    char *word;
    int i,j,count;
    i = 0;
    while (1){
        if (line[i]==' ' || line[i]=='\t' || line[i]=='\0' || line[i]=='\r'){
            line[i] = ' ';
            i++;
        }
        else if (line[i]=='\n' || line[i]==';' || line[i] == EOF){
            if (line[i] == ';'){
                while (line[i]!='\n'){
                    line[i] = ' ';
                    i++;
                }
            }
            word = (char*) calloc (1,sizeof(char));
            word = '\0';
            break;
        }
        else{
            count = 0;
            while (line[i]!=' ' && line[i]!='\t' && line[i]!='\n' && line[i]!='\r' ){
                i++;
                count++;
            }
            i -= count;
            word = (char*)calloc(count+1,sizeof(char));
            j = 0;
            while (line[i]!=' ' && line[i]!='\t' && line[i]!='\n' && line[i]!='\r' ){
                word[j] = line[i];
                line[i] = ' ';
                i++;
                j++;
            }
            word[j] = '\0';
            break;
        }

    }
    return word;
}


char** SplitLine(char *line){
    char *split;
    char **list;
    int i=0;
    int n;
    list = (char**) calloc(10,sizeof(char*));
    split = strtok(line,"\n\t");
    split = strtok(split," ");
    while (split != NULL){
        if (split[0] !=';'){
            if ((split[0] !='\n')&&(split[0] !=EOF)){
                n = strlen(split);
                list[i] = (char*) calloc(n, sizeof(char));
                strcpy(list[i], split);
                i++;
            }
        }
        else {
            break;
        }
        split = strtok (NULL, " ");
    }
    return list;
}

//-----------------------------------------------------------------



/*
 * This function initializes the opcode table with all the opcodes from
 * the Khattab Machine and their respective instruction lengths
*/
void InsertOpcode(TipoLista *t, char* opcode, int code)
{
    TipoItem x;
    int n;
    n = (int) strlen(opcode)+1;
    x.key = (char*) calloc(n,sizeof(char));
    x.key = opcode;
    x.id = code;
    Insere(&x, t);
}

/*
 * This function is used to initialize the opcode table. If n ==1,
 * the id of the cells will represent the numerical code of the opcode,
 * whereas if n==2, the id will represent the length of the instruction
*/
void CreateOpcodeTable(TipoLista *t, int n)
{
    if (n==1)
    {
    InsertOpcode(t,"LOAD\0",01);
    InsertOpcode(t,"STORE\0",02);
    InsertOpcode(t,"READ\0",03);
    InsertOpcode(t,"WRITE\0",04);
    InsertOpcode(t,"COPY\0",05);
    InsertOpcode(t,"ADD\0",06);
    InsertOpcode(t,"SUB\0",07);
    InsertOpcode(t,"AND\0",8);
    InsertOpcode(t,"OR\0",9);
    InsertOpcode(t,"XOR\0",10);
    InsertOpcode(t,"NOT\0",11);
    InsertOpcode(t,"JMP\0",12);
    InsertOpcode(t,"JZ\0",13);
    InsertOpcode(t,"JNZ\0",14);
    InsertOpcode(t,"JN\0",15);
    InsertOpcode(t,"JP\0",16);
    InsertOpcode(t,"PUSH\0",17);
    InsertOpcode(t,"POP\0",18);
    InsertOpcode(t,"CALL\0",19);
    InsertOpcode(t,"RET\0",20);
    InsertOpcode(t,"HALT\0",21);
    InsertOpcode(t,"WORD\0",22);
    InsertOpcode(t,"END\0",23);
    }
    else
    {
    InsertOpcode(t,"LOAD\0",3);
    InsertOpcode(t,"STORE\0",3);
    InsertOpcode(t,"READ\0",2);
    InsertOpcode(t,"WRITE\0",2);
    InsertOpcode(t,"COPY\0",3);
    InsertOpcode(t,"ADD\0",3);
    InsertOpcode(t,"SUB\0",3);
    InsertOpcode(t,"AND\0",3);
    InsertOpcode(t,"OR\0",3);
    InsertOpcode(t,"XOR\0",3);
    InsertOpcode(t,"NOT\0",2);
    InsertOpcode(t,"JMP\0",2);
    InsertOpcode(t,"JZ\0",2);
    InsertOpcode(t,"JNZ\0",2);
    InsertOpcode(t,"JN\0",2);
    InsertOpcode(t,"JP\0",2);
    InsertOpcode(t,"PUSH\0",2);
    InsertOpcode(t,"POP\0",2);
    InsertOpcode(t,"CALL\0",2);
    InsertOpcode(t,"RET\0",1);
    InsertOpcode(t,"HALT\0",1);
    InsertOpcode(t,"WORD\0",1);
    InsertOpcode(t,"END\0",1);
    }
}


/*
 * This function was heavily based on the function presented on Tanenbaum
*/
void PassOne(FILE* f, TipoLista* symTable, TipoLista* lenTable, bool verbose)
{
    int counter = 0;
    int length, jj , end;
    char *line;
    char * word;

    
    while (!feof(f))
    {
        line = ReadLine(f); //Reads one line from input
        word = NextWord(line); //Gets the word
        if(word ==NULL)
            continue;
        end = (int) strlen(word);
        //If the word's a symbol
        if (word[end-1]==':'){
            //Removes the colon from the symbol
                TipoItem item;
                word[end-1] = '\0';
                item.id = counter;
                item.key = (char*)calloc(end,sizeof(char));
                item.key = word;
                Insere(&item,symTable);
                word = NextWord(line);
                length = Busca(word,
                        *lenTable); //Gets the size of the instruction
                counter +=length;

            }
            //If the word's not a symbol
            else{
                length = Busca(word,*lenTable);
                // If we have found an END, we must stop
                if (length ==23)
                    return;
                counter +=length;
            }
            jj++;
        free(line);
    }
    
    
    if (verbose)
    {
        printf("Symbol ILC\n");
        ImprimeLista(stdout, *symTable);
    }
    
   
}

int OperatorAux(char* c)
{
    c[2] = '\0';
    if (!strcmp(c,"R7"))
        return 7;
    else if (!strcmp(c,"R6"))
        return 6;
    else if (!strcmp(c,"R5"))
        return 5;
    else if (!strcmp(c,"R4"))
        return 4;
    else if (!strcmp(c,"R3"))
        return 3;
    else if (!strcmp(c,"R2"))
        return 2;
    else if (!strcmp(c,"R1"))
        return 1;
    else if (!strcmp(c,"R0"))
        return 0;
    return 8;
}

void PassTwo(FILE* input, FILE* output,
        Memory* p, TipoLista symTable, TipoLista opTable,
        TipoLista lenTable, TipoLista *refTable)
{
    
   //Initialize the program file (p)
    int ii;
    p->pc = 0; p->sp = 1000;
    bool end = false; //keeps track if END instruction has been read
    char *line;
    while (!feof(input)) {
        line = ReadLine(input);
        end = PassTwoAux(line,p,  symTable, opTable, lenTable, refTable);
        free(line);
        if (end)
            break;
    }
    
    
    //This adaptation to the original assembler will print an "object" file
    //in form of text. Thus, the output is no longer an executable binary file,
    //but a text file that represents the object to be linked
    fprintf(output, "%d\n", symTable.size);
    ImprimeLista(output, symTable);
    fprintf(output, "%d\n", refTable->size);
    ImprimeLista(output, *refTable); 
    fprintf(output, "%d\n", p->pc - 1);
    for (ii=0;ii<p->pc;ii++)
    {
        fprintf(output, "%d\n", p->mem[ii] );
    }
    
    
    
    
    p->pc = 0; p->sp = 1000;
    
    //CreateFile(output, *p);
    
    
}

bool PassTwoAux(char* line, Memory* p, TipoLista symTable, TipoLista opTable,
        TipoLista lenTable, TipoLista *refTable)
{
        char * word;
        int end;
        int code;
        //Gets the first word of the line
        word = NextWord(line);
        if (word==NULL){
            return false;
        }
        
        else{
            end = (int) strlen(word);
            if (word[end-1]==':'){
                word = NextWord(line);
            }
        }
        code = Busca(word, opTable);
        //If opcode == END, we're finished
        if (code == 23)
            return true;
        int op1,op2;
        p->mem[p->pc] = code;
       (p->pc)++;
        switch( code ){
            case 1: //LOAD
            case 2: //STORE
                word = NextWord(line);
                op1 = OperatorAux(word);
                p->mem[p->pc] = op1;
               (p->pc)++;
                word = NextWord(line);
                op2 = Busca(word, symTable);
                //op2 = op2 - p->pc-1;
                //p->mem[p->pc] = op2;
                if (op2==NOTFOUND)
                    //are we dealing with a reference from another file?
                {
                        TipoItem z;
			z.id = p->pc;
		        z.key = word;
			Insere(&z,refTable);
			p->mem[(p->pc)] = NOTFOUND;
                }
                else
                {
                        TipoItem z;
			z.id = p->pc;
		        z.key = word;
			Insere(&z,refTable);
                        op2 -= (p->pc + 1);
			p->mem[(p->pc)] = op2;
                }
                     
               (p->pc)++;
                break;
            case 3: //READ
            case 4: //WRITE
            case 17: //PUSH
            case 18: //POP
                word = NextWord(line);
                op1 = OperatorAux(word);
                p->mem[p->pc] = op1;
               (p->pc)++;
                break;
                
            case 5: //COPY
            case 6: //ADD
            case 7: //SUB
            case 8: //AND
            case 9: //OR
            case 10: //XOR
                word = NextWord(line);
                op1 = OperatorAux(word);
                p->mem[p->pc] = op1;
               (p->pc)++;
                word = NextWord(line);
                op2 = OperatorAux(word);
                p->mem[p->pc] = op2;
               (p->pc)++;
                break;
            //NOT
            case 11:
                word = NextWord(line);
                op1 = OperatorAux(word);
                 p->mem[p->pc] = op1;
               (p->pc)++;
                break;
            
            case 12: //JMP
            case 13: //JZ
            case 14: //JNZ
            case 15: //JN
            case 16: //JP
            case 19: //CALL
                word = NextWord(line);
                op1 = Busca(word, symTable);
               //(p->pc)++;
                //op1 = op1 - p->pc;
                //p->mem[p->pc-1] = op1;
                if (op1==NOTFOUND)
                    //are we dealing with a reference from another file?
                {
                        TipoItem z;
			z.id = p->pc;
		        z.key = word;
			Insere(&z,refTable);
			p->mem[(p->pc)] = NOTFOUND;
                }
                else
                {
                        TipoItem z;
			z.id = p->pc;
		        z.key = word;
			Insere(&z,refTable);
                        op1 -= (p->pc + 1);
			p->mem[(p->pc)] = op1;
                }
                (p->pc)++;
                break;
            case 20: //RET
            case 21: //HALT
                break;
            case 22: //WORD
                word = NextWord(line);
                op1 = atoi(word);
                p->mem[p->pc -1] = op1;
                break;
        }
        return false;
    
}


/*
 * Given an output file open in WRITE BINARY mode, and the file's structure for
 * Khattab's machine "p". This function will write the program on the file
*/
void CreateFile(FILE* f, Memory p)
{
    //values that validate the Khattab's machines file
    char val [] = {'M' , 'K'};
    int ii;
    
    //fwrite(val,sizeof(char),sizeof(val),f);
    //fwrite(&p.pc,sizeof(int),1,f);
    //fwrite(&p.sp,sizeof(int),1,f);
    fwrite(p.mem, sizeof(int), 1000, f);
    
/*
    printf("%d\n", p.pc);
    printf("%d\n", p.sp);
    
    for (ii=0;ii<50;ii++)
    {
        printf("%d\n", p.mem[ii]);
    }
*/
    
    
}