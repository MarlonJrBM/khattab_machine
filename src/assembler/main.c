/*
 * main.c
 *
 *  Created on: Nov 22, 2013
 *      Author: marlon
 */

#include "assembler.h"

//-----------------------------------------------------------------------------
        //



//-----------------------------------------------------------------------------

int main (int argc, char** argv)
{
    
    
//-----------------------------------------------------------------------------
    //Handle the opening of the input and output files
    bool verbose = false;
    FILE *input, *output;
    input = fopen(argv[1], "r");
    if (input==NULL)
    {
        perror ("Error opening file: ");
        exit(1);
    }
    output = fopen(argv[2], "w");
    if (output==NULL)
    {
        fclose(input);
        perror ("Error opening file: ");
        exit(1);
    }
    
    if (argc>3)
        if (argv[3][0]=='v')
            verbose = true;
    
//-----------------------------------------------------------------------------
	

//-----------------------------------------------------------------------------
    //Initialize the tables (allocate memory for linked lists)
        TipoLista symTable,opTable,lenTable, refTable;
        FLVazia(&symTable);
        FLVazia(&opTable);
        FLVazia(&lenTable);
        FLVazia(&refTable);
        CreateOpcodeTable(&opTable, 1);
        CreateOpcodeTable(&lenTable,2);
        Memory program;
//-----------------------------------------------------------------------------

        PassOne(input, &symTable, &lenTable,verbose);
        rewind(input);
        PassTwo(input, output, &program, symTable, opTable, lenTable, &refTable );
        
        
        
        
        
        
//-----------------------------------------------------------------------------
        //Deallocate memory for the linked lists and files
        DesfazLista(&symTable);
        DesfazLista(&opTable);
        DesfazLista(&lenTable);
        fclose(input);
        fclose(output);
	


//-----------------------------------------------------------------------------
        

	return 0;
}
