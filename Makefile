FLAGS = -Werror -std=c++11 -g
CC = g++

all: main

main: main.o cache.o cached_runner.o
	$(CC) $(FLAGS) -o main main.o cache.o cached_runner.o

main.o: main.cpp cache.h cached_runner.h task.h
	$(CC) $(FLAGS) -c -o main.o main.cpp

cache.o: cache.cpp cache.h
	$(CC) $(FLAGS) -c -o cache.o cache.cpp

cached_runner.o: cached_runner.cpp cached_runner.h task_runner.h
	$(CC) $(FLAGS) -c -o cached_runner.o cached_runner.cpp

clean:
	del /f *.o main.exe main
