#include <iostream>
#include <fstream> 
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "global.hpp"
using namespace std;

vector<string> Filename;
vector<string> Sudoku_Problem;


void File_input(){
    string filename = "";
    while(getline(cin,filename) && filename != ""){
        Filename.push_back(filename);
    }

    vector<string>::iterator i;
    for(i=Filename.begin();i!=Filename.end();i++){
        std::ifstream ifs;
        ifs.open (*i, std::ifstream::in);
        string line = "";
        while(getline(ifs,line)){
            Sudoku_Problem.push_back(line);
        }
    }
}


//
int num=文件数目；
pthread_t Input_Thread[2];

	for(int i=0;i<2;i++)
	{
		//首先根据文件的数目，由两个线程进行读取
一分为2，静态分配
	}
    	

		pthread_create(&Input_Thread[i], NULL, input, &thPara[i]) != 0)
	
	}

