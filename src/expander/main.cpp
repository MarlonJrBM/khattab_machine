/* 
 * File:   main.cpp
 * Author: marlon
 *
 * Created on December 5, 2013, 10:24 PM
 */

#include "expander.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
      
    expander t;
    t.ExpandMacros(argv[1], argv[2]);
    
    
    return 0;
}


