#include <iostream>
#include <fstream> 
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <vector>
#include <pthread.h>

#include "global.hpp"
using namespace std;

long Sudoku_Problem_Size = 20;
int Producer_Num = 2;
int Consumer_Num = 6;

int64_t now()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

int main(int argc, char* argv[])
{
	File_input();
	Sudoku_Problem_Size = Sudoku_Problem.size();

	// Init();

    // pthread_t Producer_Thread[Producer_Num];
    pthread_t Consumer_Thread[Consumer_Num];
	ThreadParas thPara[Consumer_Num];

	// for(int i=0;i<Producer_Num;i++)
	// {
	// 	if(pthread_create(&Producer_Thread[i], NULL,  Sudoku_Producer, NULL) != 0)
	// 	{
	// 		perror("pthread_create failed");
	// 		exit(1);
	// 	}
	// }

	for(int i=0;i<Consumer_Num;i++)
	{
		int first=(int)(Sudoku_Problem_Size/Consumer_Num)*i;
    	int last;
    	if(i != Consumer_Num-1)
    		last=(int)(Sudoku_Problem_Size/Consumer_Num)*(i+1);
    	else
    		last=Sudoku_Problem_Size;
		thPara[i].num = i;
    	thPara[i].first=first;
    	thPara[i].last=last;
		if(pthread_create(&Consumer_Thread[i], NULL, Consume_Sudoku_Problem, &thPara[i]) != 0)
		{
			perror("pthread_create failed");
			exit(1);
		}
	}


	// for(int i=0;i<Producer_Num;i++)
    // 	pthread_join(Producer_Thread[i], NULL);

	for(int i=0;i<Consumer_Num;i++)
    	pthread_join(Consumer_Thread[i], NULL);

	return 0;
}

