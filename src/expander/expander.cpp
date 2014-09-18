/* 
 * File:   expander.cpp
 * Author: marlon
 * 
 * Created on December 2, 2013, 11:13 PM
 */

#include "expander.h"

expander::expander() {
}

expander::expander(const expander& orig) {
}

expander::~expander() {
}

void expander::ExpandMacros(string input, string output)
{
    ReadFile(input);
    
    PassOne();
    
    //cout << "Just testing stuff..." << endl;
    //PrintList(cout, macroMap["INPUT"]);
    
    PassTwo();
    
    
    
    
    WriteFile(output);
}

void expander::ReadFile(string fileName) {
    ifstream input;
    string line;
    input.open(fileName.c_str(), ios::in);
    if (input.is_open())
        //Read the file line by line, transforming its lines on nodes of a 
        //linked list
    {
        while (getline(input, line))
        {
           program.push_back(line);
        }   
    }   
    input.close();
    
}


void expander::WriteFile(string fileName)
{
    ofstream output;
    //iterator that goes through the list
    output.open(fileName.c_str(), ios::out);
    if (output.is_open())
        
    {
        PrintList(output, program);
        
    }
    
    output.close();    
}


//The first pass will scan the list for the definition of macros, and save them
//to the macroMap
void expander::PassOne()
{
    list<string>::iterator ii;
    map<string, list<string> >:: iterator jj;
    bool isMacro = false;
    bool parameter = false;
    string line, word, macroName, macroP;
    int found; //aux to deal with string token
    for (ii=program.begin(); ii!=program.end(); ii++)
    {
        line = *ii;
        if (isMacro)
            //Are we reading the definition of a macro?
        {
            found = line.find("ENDMACRO");
            //Have we reached the end of the macro?
            if (found==string::npos)
                //if not, push the line on the macroMap's list
            {
                
            (macroMap[macroName]).push_back(line);

            }
            

            else //if yes, set the flag to false
                isMacro=false;      
            ii = program.erase(ii);
              //we don't the want the macro definition in the actual file,
              //so we erase it from the program list.
              ii--;
        }
        else
            //we're not reading the definition of a macro
        {
          found = line.find("BEGINMACRO");
          if (found!=string::npos)
            //Have we found the beginning of a macro?
          {
              found = line.find(":");
              macroName = line.substr(0,found); //extracts the macro's name
              word = line.substr(found+1);
              isParameter(word, parameter, macroP);
              //extract the macro's name and possible parameter
              
              parameterMap[macroName] = macroP;
              
              //macroName = line;
              
              //cout << macroName << endl;
              
              
              isMacro = true;
              ii = program.erase(ii);
              //we don't the want the macro definition in the actual file,
              //so we erase it from the program's linked list.
              ii--;
              //the erase method sets the iterator one position forward,
              //since the for loop will do that for us, we set it one position
              //back, so no line will be skipped
          }
          //if we haven't found the beginning of a macro, 
          //just move to the next line
        }
    }
    
    
}

void expander::PassTwo()
{
    string line, word, macroName, macroP;
    list<string>::iterator ii, kk, zz;
    map<string, list<string> >:: iterator jj;
    list<string> aux;
    bool isMacro = false;
    bool parameter = false;
    int found;
    
    
    for (ii=program.begin();ii!=program.end();ii++)
        //We'll go thru each line of the program's list, looking for a 
        //possible macro's name
    {
        line = *(ii);
        for (jj=macroMap.begin();((jj!=macroMap.end()) && (!isMacro))
                ;jj++)
            //We need to look the whole macroMap to see if we find a match
        {
            macroName = (jj)->first;
            found = line.find(macroName);
            if (found!=string::npos)
                //Yeah, we have found a macro!
            {
                isMacro=true;
            }
        }
        
        if (isMacro)
            //We have found the use of a macro, now it's the time to get
            //the hands dirty and expand the damn thing
        {
            //First, let's see if we're dealing with a macro with parameter
            isParameter(line, parameter, macroP );
            aux = macroMap[macroName];
            if (parameter)
                //if we have indeed a parameter, then let's replace the
                //macromap's list with the parameter   
            {
                ReplaceParameter(macroP, parameterMap[macroName], aux);
            }
             //PrintList(cout, macroMap[macroName]);
            
            parameter = false;
            
            line = line.substr(0,found); //get rid of the macro's name
            kk = (aux).begin();
            line+=*(kk); kk++; //Add the first instruction of the macro to 
            //that line
            *(ii) = line; //update the line on the actual list
            ii++;
            zz= aux.end();
            program.insert(ii,kk, zz);
           //insert the rest of the macro
            isMacro  = false;
            ii--;//let's proceed to the other lines     
        }
        
        
    }
    
    
}

//Given a linked list containing the macro definition, replaces
//the parameter p by the argument a
void expander:: ReplaceParameter(string p, string a, list<string> &l)
{
    //Since it's not have been done yet, the parameter must be extracted from
    //the macro's name
    
//    vector<string> v;
//    string token, p;
//    
    int found;  
//    found = macroName.find(":");
//    if (found!=string::npos)
//        //if there is a ":", get rid of it and of the label as well
//    {
//        macroName = macroName.substr(found+1);
//    }
//    
//    stringstream aux(macroName);
//    
//    while (aux >> token)
//    {
//        v.push_back(token);
//    }
//    
//    //cout << v.size() << endl;
//    
//    if (v.size()==2)
//        //if we have more than one word, the second one is defnitely the
//        //paremeter
//    {
//        p = v[v.size() - 1];
//    }
//    
//    //cout << p << endl;
    
    
    list<string>::iterator jj;
    string line;
    
    for (jj=l.begin();jj!=l.end();jj++)
        //Iterates through all the lines of the macro's definition
    {
        line = *(jj);
        //cout << line;
        found = line.rfind(a);
        if (found!=string::npos)
            //have we found the argument?
        {
            line = line.substr(0, found);
            line += p;
            //if we have found it, then replace the parameter p by the argument
            //a
            *(jj) = line;   
        }
    }  
}


//Neat function that gets as input, and boolean b and string p as output
//It sets b to true if the macro contained in line has a parameter
//and the string p to the value of the parameter, if there is one
//and to "\0", if there isn't any.
void expander:: isParameter(string line, bool &b, string &p )
{
    vector<string> v;
    string token;
    
    int found;  
    found = line.find(":");
    if (found!=string::npos)
        //if there is a ":", get rid of it and of the label as well
    {
        line = line.substr(found+1);
    }
    
    //cout << line << endl;
    
    stringstream aux(line);
    
    while (aux >> token)
    {
        v.push_back(token);
    }
    
    if (v.size()==2)
        //if we have more than one word, the second one is defnitely the
        //paremeter
    {
        b = true;
        p = v[v.size()-1];
        
    }
    else
    {
     b= false;
     p = '\0';
    }
    

    

    
    
          
}


void expander::PrintList(ostream &f, list<string> l)
{
    list<string>::iterator ii;
    
    for (ii=l.begin(); ii!=l.end(); ii++)
            //Loop that iterates through the list and prints it on the file,
            //line by line
        {
            f << *(ii) << endl;
        }
}