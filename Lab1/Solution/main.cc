#include <iostream>
#include <fstream> 
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <vector>
#include <pthread.h>
#include <sys/sysinfo.h>
#include "global.hpp"
using namespace std;

int cpu()
{
   return get_nprocs();
}

int64_t now()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

long Sudoku_Problem_Size = 1000;
int Producer_Num = 2;
int Consumer_Num = cpu();

int main(int argc, char* argv[])
{	double time1,time2;
	File_input();
	Sudoku_Problem_Size = Sudoku_Problem.size();
	if(DEBUG_MODE)
		cin >>Consumer_Num;

	if(SHOW_TIME){
		printf("the Sudoku Problem Size %ld \n", Sudoku_Problem_Size);
		int64_t start = now();

		for(int i=0;i<Sudoku_Problem_Size;i++){
			string ans = "";
			ans = solve_sudoku_dancing_links(Sudoku_Problem[i]);
		}
		int64_t end = now();
		double sec = (end-start)/1000000.0;
		time1=sec;
		printf("just  one  thread ,spend  %f  sec \n", sec); 
	}
	

	int64_t start_thread = now();

	// Init();

    // pthread_t Producer_Thread[Producer_Num];
	// for(int i=0;i<Producer_Num;i++)
	// {
	// 	if(pthread_create(&Producer_Thread[i], NULL,  Sudoku_Producer, NULL) != 0)
	// 	{
	// 		perror("pthread_create failed");
	// 		exit(1);
	// 	}
	// }

    pthread_t Consumer_Thread[Consumer_Num];
	ThreadParas thPara[Consumer_Num];

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

	int64_t end_thread = now();

	if(OUTPUT_ANS){
		int count = 0;
		for(int i=0;i<Consumer_Num;i++){
			vector<string>::iterator it;
			for(it=thPara[i].result.begin();it!=thPara[i].result.end();it++){
				if(DEBUG_MODE){
					cout <<endl <<Sudoku_Problem[count] <<endl;
					count++;
				}
				cout <<*it <<endl;
			}
		}
	}
	if(SHOW_TIME){
		double sec_thread = (end_thread-start_thread)/1000000.0;
		time2=sec_thread;
		printf("create  %d  thread ,spend  %f  sec \n", Consumer_Num, sec_thread); 
	}
		double rate=time1/time2;
		printf("the ratio of serial execution time to parallel execution time:%f\n",rate);
	return 0;
}

