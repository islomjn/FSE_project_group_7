#include "Matrix.h"

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



