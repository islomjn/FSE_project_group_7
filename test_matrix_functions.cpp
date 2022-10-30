#include <gtest/gtest.h>
#include <iostream>

#include "Matrix.h"
#include "matrix_functions.h"

TEST(Calculations, id_matrices_1_1) {
	int N = 1;
	Matrix<float> id1(N, N), id2(N, N), calcRes(N, N), expRes(N, N);
	id1[0][0] = 1.0;
	id2[0][0] = 1.0;
	expRes[0][0] = 1.0;
	
	calcRes = matmul(id1, id2);

	EXPECT_TRUE(calcRes == expRes);

	std::cout << "Expected:\n";
	print_matrix(expRes);
	std::cout << "Received:\n";
	print_matrix(calcRes);
}

TEST(Calculations, id_matrices_test_refererence_matmul) {
	int N = 3;
	Matrix<float> id1(N, N), id2(N, N), calcRes(N, N), expRes(N, N);
	for (int i = 0; i < N; ++i) 
		for (int j = 0; j < N; ++j)
			if (i == j) {
				id1[i][j] = 1.0;
				id2[i][j] = 1.0;
				expRes[i][j] = 1.0;
			} else {
				id1[i][j] = 0.0;
				id2[i][j] = 0.0;
				expRes[i][j] = 0.0;
			}
	
	calcRes = ref_matmul(id1, id2);

	EXPECT_TRUE(calcRes == expRes);

	std::cout << "Expected:\n";
	print_matrix(expRes);
	std::cout << "Received:\n";
	print_matrix(calcRes);
}

TEST(Calculations, id_matrices_parallel_vs_reference) {
	int N = 3;
	Matrix<float> id1(N, N), id2(N, N), calcRes(N, N), expRes(N, N);
	for (int i = 0; i < N; ++i) 
		for (int j = 0; j < N; ++j)
			if (i == j) {
				id1[i][j] = 1.0;
				id2[i][j] = 1.0;
				expRes[i][j] = 1.0;
			} else {
				id1[i][j] = 0.0;
				id2[i][j] = 0.0;
				expRes[i][j] = 0.0;
			}
	
	expRes = ref_matmul(id1, id2);
	calcRes = parallel_matmul(id1, id2);

	EXPECT_TRUE(calcRes == expRes);

	std::cout << "Expected:\n";
	print_matrix(expRes);
	std::cout << "Received:\n";
	print_matrix(calcRes);
}

void fill_n_4_k_3_m_5_matrices(Matrix<float> a, Matrix<float> b){
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
    b[0][3] = 0;
    b[0][4] = 0;
    b[1][0] = 3;
    b[1][1] = 2;
    b[1][2] = 0;
    b[1][3] = 0;
    b[1][4] = 0;
    b[2][0] = 2;
    b[2][1] = 0;
    b[2][2] = 0;
    b[2][3] = 0;
    b[2][4] = 0;
}

void fill_n_4_k_3_m_5_reference(Matrix<float> c){
    c[0][0] = 13;
    c[0][1] = 2;
    c[0][2] = 2;
	c[0][3] = 0;
    c[0][4] = 0;
    c[1][0] = 3;
    c[1][1] = 2;
    c[1][2] = 0;
    c[1][3] = 0;
    c[1][4] = 0;
    c[2][0] = 10;
    c[2][1] = 0;
    c[2][2] = 2;
    c[2][3] = 0;
    c[2][4] = 0;
    c[3][0] = 10;
    c[3][1] = 0;
    c[3][2] = 2;
    c[3][3] = 0;
    c[3][4] = 0;
}

TEST(Calculations, NxK_KXM_matrices_reference) {
	int N = 4;
	int K = 3;
	int M = 5;
	Matrix<float> a(N, K), b(K, M), calcRes(N, M), expRes(N, M);
	fill_n_4_k_3_m_5_matrices(a, b);
	fill_n_4_k_3_m_5_reference(expRes);

	calcRes = parallel_matmul(a, b);

	EXPECT_TRUE(calcRes == expRes);

	std::cout << "Expected:\n";
	print_matrix(expRes);
	std::cout << "Received:\n";
	print_matrix(calcRes);
}

TEST(Calculations, NxK_KXM_matrices_ref_vs_parallel) {
	int N = 4;
	int K = 3;
	int M = 5;
	Matrix<float> a(N, K), b(K, M), calcRes(N, M), expRes(N, M);
	fill_n_4_k_3_m_5_matrices(a, b);

	expRes = ref_matmul(a, b);
	calcRes = parallel_matmul(a, b);

	EXPECT_TRUE(calcRes == expRes);

	std::cout << "Expected:\n";
	print_matrix(expRes);
	std::cout << "Received:\n";
	print_matrix(calcRes);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}