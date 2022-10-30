#include "Matrix.h"
#include <omp.h>

Matrix<float> ref_matmul(Matrix<float> a, Matrix<float> b){
    // Simple, cubic, non parallelized matmul
    // Supposed to be used for testing
    Matrix<float> ret_val(a.height, b.width);
    for(int i=0; i < a.height; i++){
        for(int j=0; j < b.width; j++){
            ret_val[i][j] = 0;
            for(int t=0; t < a.width; t++){
                ret_val[i][j] += a[i][t] * b[t][j];
            }
        }
    } 
    return ret_val;
}


Matrix<float> vector_mat_mul(Matrix<float> a, Matrix<float> b){
    // a [1, k]
    // b [k, n]
    // ret_val [1, n]
    Matrix<float> ret_val(1, b.width);
    for(int i=0; i < b.width; i++){
        ret_val[0][i] = 0;
        for(int j=0; j < b.height; j++){
            ret_val[0][i] += a[0][j] * b[j][i];
        }
    }
    return ret_val;
}

void print_matrix(Matrix<float> a){
   for(int i=0; i < a.height; i++){
       for(int j=0; j < a.width; j++){
           std::cout << a[i][j] << " ";
       }
       std::cout << std::endl;
   }
}

Matrix<float> parallel_matmul(Matrix<float> a, Matrix<float> b){
    // Parllelized implementation of matmul
    // Does partition first matrix (a) by rows
    // and multiplicates each row to matrix b
    // in separate threads
    // If you do have number of threads lower than number of matrix A rows
    // Than we several rounds of multithreading will be performed 
    
    Matrix<float> c(a.height, b.width);
    int num_threads = 0;
    if (a.height > omp_get_max_threads()){
        num_threads = omp_get_max_threads();
    } else {
        num_threads = a.height;
    }
    omp_set_num_threads(num_threads);

    for (int cycle = 0; cycle < (a.height  - 1) / num_threads + 1; cycle++){
        #pragma omp parallel shared(c)
        {
            Matrix<float> d(1, a.width);
            int thread_number = omp_get_thread_num();
            for(int i = 0; i < a.width; i++){
                d[0][i] = a[num_threads * cycle + thread_number][i];
            }
            d = vector_mat_mul(d, b);
            for(int i = 0; i < c.width; i++){
                c[num_threads * cycle + thread_number][i] = d[0][i];
            }
        }
    }
    return c;
}

