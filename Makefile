all: program
#program: mpi.c
#        mpicc mpi.c -o program

program: main_matrix.cpp
        mpicc main_matrix.cpp -o program
#test:


clean: 
        rm program

