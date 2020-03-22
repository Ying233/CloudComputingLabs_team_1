#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <semaphore.h>
#include "global.hpp"

sem_t Sudoku_Problem_Mutex;
sem_t Sudoku_Problem_Empty;
sem_t Sudoku_Problem_Full;

extern long Sudoku_Problem_Size;

void Init(){
    sem_init(&Sudoku_Problem_Mutex,0,1);
    sem_init(&Sudoku_Problem_Empty,0,Sudoku_Problem_Size);
    sem_init(&Sudoku_Problem_Full,0,0);
}

void Produce_Sudoku_Problem(){
  
}

void * Sudoku_Producer(void *arg){
    while(1){
        sem_wait(&Sudoku_Problem_Empty);
        sem_wait(&Sudoku_Problem_Mutex);
        Produce_Sudoku_Problem();
        sem_post(&Sudoku_Problem_Mutex);
        sem_post(&Sudoku_Problem_Full);
    }

}

