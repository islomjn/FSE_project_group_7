COMPILER=g++
FLAGS=-fopenmp

main: main.cpp
	$(COMPILER) main.cpp matrix_functions.cpp $(FLAGS) -o main

clean:
	rm main
