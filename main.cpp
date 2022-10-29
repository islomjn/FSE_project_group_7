#include <iostream>
#include <omp.h>
#include <vector>
#include "Matrix.h"
#include "matrix_functions.h"

Matrix<float> a(3, 3);

Matrix<float> b(3, 3);

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

    b[0][0] = 5;
    b[0][1] = 0;
    b[0][2] = 1;
    b[1][0] = 3;
    b[1][1] = 2;
    b[1][2] = 0;
    b[2][0] = 2;
    b[2][1] = 0;
    b[2][2] = 0;
}

std::vector <int> global_vector = {1, 2, 3, 4};

int main(){
    fill_matrices();
    std::cout << std::endl;
    std::cout << "A =\n";
    print_matrix(a);
    std::cout << "\nB =\n";
    print_matrix(b);
    
    Matrix<float> c(a.height, b.width);
    omp_set_num_threads(a.width);
    #pragma omp parallel shared(c)
    {  
        Matrix<float> d(1, a.width); 
        int thread_number = omp_get_thread_num();
        for(int i = 0; i < a.width; i++){
            d[0][i] = a[thread_number][i];
        }
        d = vector_mat_mul(d, b);
     for(int i = 0; i < c.width; i++){
         c[thread_number][i] = d[0][i];
     }
    }
    std::cout << "\nA X B = \n";
    print_matrix(c);
    return 0;
}