#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <semaphore.h>
using namespace std;

typedef struct {
	int num;
	int first;
	int last;
	vector<string> result;
}ThreadParas;

const bool DEBUG_MODE = true;
enum { ROW=9, COL=9, N = 81, NEIGHBOR = 20 };
const int NUM = 9;

extern long Sudoku_Problem_Size;
extern int Producer_Num;
extern int Consumer_Num;

extern sem_t Sudoku_Problem_Mutex;
extern sem_t Sudoku_Problem_Empty;
extern sem_t Sudoku_Problem_Full;

extern std::vector<std::string> Filename;
extern std::vector<std::string> Sudoku_Problem;

std::string solve_sudoku_dancing_links(std::string in);
void File_input();
void Init();
void * Sudoku_Producer(void *arg);
void * Sudoku_Consumer(void *arg);

void * Consume_Sudoku_Problem(void *arg);

#endif
