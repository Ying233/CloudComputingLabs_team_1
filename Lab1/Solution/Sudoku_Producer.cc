#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <semaphore.h>
#include <fstream>
#include <iostream>
#include "global.hpp"

//extern sem_t Sudoku_Problem_Mutex;
//extern sem_t Sudoku_Problem_Empty;
//extern sem_t Sudoku_Problem_Full;

extern long Sudoku_Problem_Size;

void Init(){
    sem_init(&Sudoku_Problem_Mutex,0,1);
    sem_init(&Sudoku_Problem_Empty,0,Sudoku_Problem_Size);
    sem_init(&Sudoku_Problem_Full,0,0);
}

void *Produce_Sudoku_Problem(void *args){
	vector<string>::iterator i;
    for(i=Filename.begin();i!=Filename.end();i++){
        std::ifstream ifs;
        ifs.open (*i, std::ifstream::in);
        string line = "";
        while(getline(ifs,line)){
			sem_wait(&Sudoku_Problem_Empty);
			sem_wait(&Sudoku_Problem_Mutex);
            Sudoku_Problem[++handling] = line;
            ++Sudoku_Problem_Size;
            //cout<<"HP:"<<handling<<endl;
			sem_post(&Sudoku_Problem_Mutex);
			sem_post(&Sudoku_Problem_Full);
        }
    }
    flag = 0;
}
/*
void * Sudoku_Producer(void *arg){
    while(1){
        sem_wait(&Sudoku_Problem_Empty);
        sem_wait(&Sudoku_Problem_Mutex);
        Produce_Sudoku_Problem();
        sem_post(&Sudoku_Problem_Mutex);
        sem_post(&Sudoku_Problem_Full);
    }

}
*/

