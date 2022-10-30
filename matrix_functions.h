#ifndef MAIN_MATRIX_H
#define MAIN_MATRIX_H

#include "Matrix.h"

Matrix<float> ref_matmul(Matrix<float> a, Matrix<float> b);
Matrix<float> parallel_matmul(Matrix<float> a, Matrix<float> b);
Matrix<float> vector_mat_mul(Matrix<float> a, Matrix<float> b);
void print_matrix(Matrix<float> a);

#endif // MAIN_MATRIX_H