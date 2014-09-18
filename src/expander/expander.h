/* 
 * File:   expander.h
 * Author: marlon
 *
 * Created on December 2, 2013, 11:13 PM
 */

#ifndef EXPANDER_H
#define	EXPANDER_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

class expander {
public:
    expander();
    expander(const expander& orig);
    virtual ~expander();
    void ExpandMacros(string input, string output);
    
private:
    list<string> program; 
    //linked list of strings that contains the assembler code
    map<string, list<string> > macroMap;
    map<string,string> parameterMap;
    void PrintList(ostream &f, list<string> l);
    void ReadFile(string fileName);
    void WriteFile(string fileName);
    void PassOne();
    void PassTwo();
    void ReplaceParameter(string p,string a, list<string> &l);
    void isParameter(string line, bool &b, string &p );
    
    
   
    
    
    

};

#endif	/* EXPANDER_H */

