/* 
 * File:   main.cpp
 * Author: marlon
 *
 * Created on December 6, 2013, 6:43 PM
 */

#include "linker.h"



/*
 * 
 */
int main(int argc, char** argv) {
    if (argc<5)
    {
        cerr << "Insufficient arguments" << endl;
        return 1;
    }
    linker L (argc, argv);
    
        
            

    return 0;
}

