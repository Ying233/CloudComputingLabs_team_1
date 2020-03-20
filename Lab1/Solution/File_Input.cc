#include <iostream>
#include <fstream> 
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "global.hpp"
using namespace std;

vector<string> Filename;
string Sudoku_Problem[100000];


void File_input(){
    string filename = "";
    while(getline(cin,filename) && filename != ""){
        Filename.push_back(filename);
    }
    /*
    vector<string>::iterator i;
    for(i=Filename.begin();i!=Filename.end();i++){
        std::ifstream ifs;
        ifs.open (*i, std::ifstream::in);
        string line = "";
        while(getline(ifs,line)){
            Sudoku_Problem.push_back(line);
        }
    }
    */
}

