#include <iostream>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <semaphore.h>
#include "global.hpp"
using namespace std;

extern sem_t Sudoku_Problem_Mutex;
extern sem_t Sudoku_Problem_Empty;
extern sem_t Sudoku_Problem_Full;

void * Consume_Sudoku_Problem(void *arg){
    ThreadParas* para = (ThreadParas*) arg;
    int num = para->num;
    int first=para->first;
    int last=para->last;

    string ans = "";
    for(int i=first;i<last;i++){
        ans = solve_sudoku_dancing_links(Sudoku_Problem[i]);
        if(DEBUG_MODE){
            printf("[%ld]  worker thread : %d \n", pthread_self(),num);
            cout <<i <<" : " <<ans <<endl;
        }
        para->result.push_back(ans);
    }  
}

void * Sudoku_Consumer(void *arg){
    while(1){
        sem_wait(&Sudoku_Problem_Full);
        sem_wait(&Sudoku_Problem_Mutex);
        Consume_Sudoku_Problem(NULL);
        sem_post(&Sudoku_Problem_Mutex);
        sem_post(&Sudoku_Problem_Empty);
    }

}

