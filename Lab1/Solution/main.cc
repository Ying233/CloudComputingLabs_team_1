#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "global.hpp"

int board[N];

int64_t now()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000 + tv.tv_usec;
}

void input(const char in[N])
{
  for (int cell = 0; cell < N; ++cell) {
    board[cell] = in[cell] - '0';
    assert(0 <= board[cell] && board[cell] <= NUM);
  }
}

int main(int argc, char* argv[])
{
  FILE* fp = fopen(argv[1], "r");
  char puzzle[128];
  int total_solved = 0;
  int total = 0;
  bool (*solve)(int) = solve_sudoku_dancing_links;
  int64_t start = now();
  while (fgets(puzzle, sizeof puzzle, fp) != NULL) {
    if (strlen(puzzle) >= N) {
      ++total;
      input(puzzle);
      for(int i=0;i<N;i++)
        printf("%d",board[i]);
      printf("\n");
      if (solve(0))
        ++total_solved;
      else {
        printf("No: %s", puzzle);
      }
    }
  }
  int64_t end = now();
  double sec = (end-start)/1000000.0;
  printf("%f sec %f ms each %d\n", sec, 1000*sec/total, total_solved);

  return 0;
}

