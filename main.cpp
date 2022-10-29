#include <iostream>
#include <omp.h>
#include <vector>
#include "Matrix.h"
#include "matrix_functions.h"

int n = 4;
int m = 5;
int k = 3;

Matrix<float> a(n, k);

Matrix<float> b(k, m);

void fill_matrices(){
    a[0][0] = 2;
    a[0][1] = 1;
    a[0][2] = 0;
    a[1][0] = 0;
    a[1][1] = 1;
    a[1][2] = 0;
    a[2][0] = 2;
    a[2][1] = 0;
    a[2][2] = 0;
    a[3][0] = 2;
    a[3][1] = 0;
    a[3][2] = 0;

    b[0][0] = 5;
    b[0][1] = 0;
    b[0][2] = 1;
    b[1][0] = 3;
    b[1][1] = 2;
    b[1][2] = 0;
    b[2][0] = 2;
    b[2][1] = 0;
    b[2][2] = 0;
    b[2][0] = 2;
    b[2][1] = 0;
    b[2][2] = 0;
    b[2][0] = 2;
    b[2][1] = 0;
    b[2][2] = 0;
}


int main(){
    fill_matrices();
    std::cout << std::endl;
    std::cout << "A =\n";
    print_matrix(a);
    std::cout << "\nB =\n";
    print_matrix(b);

    std::cout << "Maximum available number of threads: " << omp_get_max_threads();
    
    std::cout << "\nResult of parallelized matmul:\n";
    print_matrix(parallel_matmul(a, b));
    std::cout << "Reference result:\n";
    print_matrix(ref_matmul(a, b));
    return 0;
}