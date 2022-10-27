#include <iostream>
#include <omp.h>
#include <vector>
#include "Matrix.h"

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

int m = 3;
int k = 3;
int n = 3;


Matrix<float> matmul(Matrix<float> a, Matrix<float> b){
    Matrix<float> ret_val;
    for(int i=0; i < n; i++){
        for(int j=0; j < m; j++){
            ret_val[i][j] = 0;
            for(int t=0; t < k; t++){
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
    Matrix<float> ret_val(1, 3);
    for(int i=0; i < k; i++){
        ret_val[0][i] = 0;
        for(int j=0; j < n; j++){
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
