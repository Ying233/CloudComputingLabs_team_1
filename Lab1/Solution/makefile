CXXFLAGS+=-O2 -ggdb -DDEBUG
CXXFLAGS+=-Wall -Wextra

all: sudoku

sudoku: main.cc Dancing_Links_Solver.cc Sudoku_Producer.cc Sudoku_Consumer.cc File_Input.cc
	g++ -O2 -pthread -o $@ $^
