/* 
 * File:   linker.h
 * Author: marlon
 *
 * Created on December 6, 2013, 6:43 PM
 */

#ifndef LINKER_H
#define	LINKER_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#define SIZE 1024
#define NOTFOUND 666666

using namespace std;


struct object
{
    int memory[SIZE], begin, end, size;
    multimap<string, int> symTable, refTable;
};


class linker {
public:
    linker(int argc, char**argv);
    linker(const linker& orig);
    virtual ~linker();

    
private:
    int memory[SIZE];
    int  PC, SP;
    object *modules;
    int numObj;
    void WriteFile(string output);
    void ReadObject(string fileName, object &o);
    void AllocateObjects();
    void ReAllocateObjects();
    int ExternSearch(string label, int index, int begin);
};

#endif	/* LINKER_H */

