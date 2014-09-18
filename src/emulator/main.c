/* 
 * File:   main.c
 * Author: Marlon
 *
 * Created on 1 de Novembro de 2013, 22:44
 */


#include "khattab.h"

/*Arquivo principal do simulador da Máquina de Khattab
 * 
 */
int main(int argc, char** argv) {
    
    FILE *f;
    Memory machine;
    bool verbose = false;
    
    f = fopen(argv[1], "rb");
    if (f==NULL)
    {
        perror ("Error opening file: ");
        exit(1);
    }
    if (argc>2)
        if (argv[2][0]=='v')
            verbose = true;
    
    
    LoadProgram(&machine, f); 
    fclose(f);
    
    RunMachine(&machine, verbose);
    
    
    
    
    

    return (EXIT_SUCCESS);
}

