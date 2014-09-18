/* 
 * File:   linker.cpp
 * Author: marlon
 * 
 * Created on December 6, 2013, 6:43 PM
 */

#include "linker.h"

//Constructs the object and does all the work regarding the linking and loading
//of the program
linker::linker(int argc, char**argv) {
    
   string moduleName;
   int ii, jj(0);
   numObj = argc - 4;
   modules = new object [numObj];
   for (ii=1;ii<argc-2;ii++)
   {
       moduleName = argv[ii];
       if ((moduleName!="-m"))
       {
           ReadObject(moduleName, modules[jj]);
           jj++;     
       }
       else
           continue;
   }
   PC = 0; SP = 1000;
   AllocateObjects();
   ReAllocateObjects();
   WriteFile(argv[argc-1]);
}

linker::linker(const linker& orig) {
}

linker::~linker() {
    
    delete [] modules;
}


//Given a string output, this method will write the program to a binary file
void linker:: WriteFile(string fileName)
{
    FILE *output;
    //ofstream log("log-m.txt");
    output = fopen(fileName.c_str(), "wb");
    int ii,jj;
    //ofstream output;
    //output.open(fileName.c_str(), ios::out | ios::binary);
    
    char val[] = {'M','K'};
    fwrite(val, sizeof(char), 2, output);
    fwrite(&PC, sizeof(int), 1, output);
    fwrite(&SP, sizeof(int), 1, output);
    modules[0].memory[120] = 1;
    for (ii=numObj-1;ii>=0;ii--)
        {
            for (jj=0;jj<=modules[ii].size;jj++)
            {
                fwrite(&modules[ii].memory[jj], sizeof(int), 1, output);
                //log << modules[ii].memory[jj] << endl;
            }
        }
//    if (output.is_open())
//    {
//        output.write(val, 2);
//        output.write((char*)&PC, 1 );
//        output.write((char*)&SP, 1 );
//        for (ii=numObj-1;ii>=0;ii--)
//        {
//            for (jj=0;jj<=modules[ii].size;jj++)
//            {
//                output.write((char*)&modules[ii].memory[jj],1);
//                cout << modules[ii].memory[jj] << endl;
//            }
//        }
//              
//        
//        //output.write((char*)memory, SIZE );
//    }
    
    
    //output.close();
    //log.close();
    fclose(output);
    
}


//It must receive at least 5 arguments (argc>=5). This function will read each
//module of the program and import the symbol, reference and raw data for each
//one.
void linker:: ReadObject(string fileName, object &o )
{
    int ii, symTableSize, refTableSize, memSize, value;
    string word;
    ifstream input(fileName.c_str());
    input >> symTableSize;
    for (ii=0;ii<symTableSize;ii++)
        //filling the symbol Table for the object
    {
        input >> word;
        input >> value;
        //o.symTable[word].push_back(value);
        o.symTable.insert(pair<string,int>(word, value));
    }
    input >> refTableSize;
    for (ii=0;ii<refTableSize;ii++)
    {
        input >> word;
        input >> value;
        o.refTable.insert(pair<string,int>(word, value));
    }
    input >> memSize;
    for (ii=0;ii<=memSize;ii++)
    {
        input >> value;
        o.memory[ii] = value;
    }
    o.size = memSize;
    

    input.close();   
}

//Does the step of Allocation
void linker:: AllocateObjects()
{
    int ii, aux;
    aux = 0;
    for(ii = numObj-1; ii>=0; ii--)
    {
    modules[ii].begin = aux;
    modules[ii].end = aux + modules[ii].size;
    aux = modules[ii].end + 1;
    //cout << modules[ii].begin << '\n' << modules[ii].end << endl;
    }
}

//Looks in other modules for a certain reference
int linker:: ExternSearch(string label, int index, int begin)
{
    int ii,ILC;
    multimap< string, int >::iterator jj;
	for(ii = numObj-1; ii>=0; ii--){
            jj = modules[ii].symTable.find(label);
		if (jj!=modules[ii].symTable.end()){
                    ILC = jj->second;
			if (index < ii){
				return (ILC + modules[ii].begin - begin);
			}
			else if (index > ii){
				return (ILC + modules[ii].begin);
			}
		}
                else
                {
                    ILC = NOTFOUND;
                }
	}
	return NOTFOUND;
}

//Reallocates each module so that all address references are in the right place
void linker:: ReAllocateObjects()
{
    int ii, seek, id;
    multimap<string, int>:: iterator jj, kk;
    string name;
    
    for(ii = numObj-1; ii>=0; ii--){
		//Aux = objects[i].ReferenceTable.Primeiro->Prox;
        jj = modules[ii].refTable.begin();

		while (jj != modules[ii].refTable.end()){
                name = jj->first;
                id = jj->second;
                    kk = modules[ii].symTable.find(name);
			if (kk==modules[ii].symTable.end()){
			    //If we haven't found the symbol in the own module
                            //we must look on the other modules
				seek = ExternSearch(name, ii, modules[ii].begin);
				if (seek==NOTFOUND){
                                    cout << "Error! There's no reference to " << name << endl;
                                    cout << "Did you include all object files?" << endl;

				}
				else {
					modules[ii].memory[id] =  seek - id -1;
					
				}
				
			}
			jj++;
	    	}
	}

    
    
}

