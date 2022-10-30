#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <climits>
#include <gtest/gtest.h>
#include <omp.h>

#include "Matrix.h"
#include "matrix_functions.h"

// Helpers ----------------------------------------------------------------

int numOfThreadsForMatMul(int height) {
	if (height > omp_get_max_threads()){
        return omp_get_max_threads();
    } else {
        return height;
    }
}

bool is_equal(Matrix<float> a, Matrix<float> b, float eps=FLT_EPSILON) {
	if(a.width == b.width && a.height == b.height){
      	for(int i = 0; i < a.height; i++)
          	for(int j = 0; j < a.width; j++)
              	if (abs(a[i][j] - b[i][j]) > FLT_EPSILON) {
              		cout << "ERROR in element " << i << ", " << j << ":\n";
              		cout << "a = " << a[i][j] << ", b = " << b[i][j] << "\n";
              		return false;
              	}
      	return true;
  	}
  	return false;
}

Matrix<float> id_matrix(uint N) {
	Matrix<float> m(N, N);
	for (int i = 0; i < N; ++i) 
		for (int j = 0; j < N; ++j)
			if (i == j) 
				m[i][j] = 1.0;
			else 
				m[i][j] = 0.0;
	return m;
}

float normRand(float magnitude=100) {
	return (float)((rand() - (double)RAND_MAX/2.0)*magnitude*2/RAND_MAX);
}

int posIntRand(int magnitude=100) {
	return rand() % magnitude + 1;
}

Matrix<float> rand_matrix(uint N) {
	srand(time(0));
	Matrix<float> m(N, N);
	for (int i = 0; i < N; ++i) 
		for (int j = 0; j < N; ++j)
			m[i][j] = normRand();
	return m;
}

Matrix<float> rand_matrix(uint heigth, uint width, float magnitude=100) {
	srand(time(0));
	Matrix<float> m(heigth, width);
	for (int i = 0; i < heigth; ++i) 
		for (int j = 0; j < width; ++j)
			m[i][j] = normRand(magnitude);
	return m;
}

void print_exp_rec(Matrix<float> expMatr, Matrix<float> recMatr) {
	std::cout << "Expected:\n";
	print_matrix(expMatr);
	std::cout << "Received:\n";
	print_matrix(recMatr);
}

void print_matrix(Matrix<float> a, int strnum){
	if (strnum < a.height) {
		cout << "First " << strnum << " strings:\n";
	}
   	for(int i=0; i < a.height and i < strnum; i++){
       for(int j=0; j < a.width; j++){
           std::cout << a[i][j] << " ";
       }
       std::cout << std::endl;
   }
}

void print_matrix(Matrix<float> a, int strnum, int colnum){
	if (strnum < a.height) {
		cout << "First " << strnum << " strings:\n";
	}
	if (colnum < a.width) {
		cout << "First " << colnum << " columns:\n";
	}
   	for(int i=0; i < a.height and i < strnum; i++){
       for(int j=0; j < a.width and j < colnum; j++){
           std::cout << a[i][j] << " ";
       }
       std::cout << std::endl;
   }
}

void print_transp_matrix(Matrix<float> a){
	std::cout << "Transposed:\n";
   	for(int j=0; j < a.width; j++){
       for(int i=0; i < a.height; i++){
           std::cout << a[i][j] << " ";
       }
       std::cout << std::endl;
   }
}

void print_transp_matrix(Matrix<float> a, int colnum){
	std::cout << "Transposed:\n";
	if (colnum < a.width) {
		cout << "First " << colnum << " columns:\n";
	}
   	for(int j=0; j < a.width and j < colnum; j++){
       for(int i=0; i < a.height; i++){
           std::cout << a[i][j] << " ";
       }
       std::cout << std::endl;
   }
}

void print_transp_matrix(Matrix<float> a, int strnum, int colnum){
	std::cout << "Transposed:\n";
	if (strnum < a.height) {
		cout << "First " << strnum << " strings:\n";
	}
	if (colnum < a.width) {
		cout << "First " << colnum << " columns:\n";
	}
   	for(int j=0; j < a.width and j < colnum; j++){
       for(int i=0; i < a.height and i < strnum; i++){
           std::cout << a[i][j] << " ";
       }
       std::cout << std::endl;
   }
}

void print_exp_rec(Matrix<float> expMatr, Matrix<float> recMatr, int strnum) {
	std::cout << "Expected:\n";
	print_matrix(expMatr, strnum);
	std::cout << "Received:\n";
	print_matrix(recMatr, strnum);
}

void print_exp_rec(Matrix<float> expMatr, Matrix<float> recMatr, int strnum, int colnum) {
	std::cout << "Expected:\n";
	print_matrix(expMatr, strnum, colnum);
	std::cout << "Received:\n";
	print_matrix(recMatr, strnum, colnum);
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

// Tests  ----------------------------------------------------------------

/// Predefined tests ------------------------------------------------------

//// Matrix class test -----------------------------------------------------

TEST(Predefined_matrix_class_test_invalid, id_min1) {
	try {
		int N = -1;
		Matrix<float> id1(N, N);
		FAIL();
	}
	catch(const char* errstr) {
		cout << errstr << endl;
		SUCCEED();
	}
}

TEST(Predefined_matrix_class_test_invalid, id_0) {
	try {
		int N = 0;
		Matrix<float> id1(N, N);
		FAIL();
	}
	catch(const char* errstr) {
		cout << errstr << endl;
		SUCCEED();
	}
}

TEST(Predefined_matrix_class_test_valid, id_1) {
	try {
		int N = 1;
		Matrix<float> id1(N, N);
		SUCCEED();
	}
	catch(const char* errstr) {
		cout << errstr << endl;
		FAIL();
	}
}

TEST(Predefined_matrix_class_test_valid, id_100) {
	try {
		int N = 100;
		Matrix<float> id1(N, N);
		SUCCEED();
	}
	catch(const char* errstr) {
		cout << errstr << endl;
		FAIL();
	}
}

//// Reference test --------------------------------------------------------

TEST(Predefined_reference_test_valid, id_1) {
	int N = 1;
	Matrix<float> id1(N, N), id2(N, N), calcRes(N, N), expRes(N, N);
	id1 = id_matrix(N);
	id2 = id_matrix(N);
	expRes = id_matrix(N);
	
	calcRes = ref_matmul(id1, id2);

	EXPECT_TRUE(is_equal(expRes, calcRes));
	print_exp_rec(expRes, calcRes);
}

TEST(Predefined_reference_test_valid, id_100) {
	int N = 100;
	Matrix<float> id1(N, N), id2(N, N), calcRes(N, N), expRes(N, N);
	id1 = id_matrix(N);
	id2 = id_matrix(N);
	expRes = id_matrix(N);
	
	calcRes = ref_matmul(id1, id2);

	EXPECT_TRUE(is_equal(expRes, calcRes));
	print_exp_rec(expRes, calcRes, 5, 5);
}

//// Parallel test -----------------------------------------------

TEST(Predefined_parallel_test_valid, id_1) {
	int N = 1;
	Matrix<float> id1(N, N), id2(N, N), calcRes(N, N), expRes(N, N);
	id1 = id_matrix(N);
	id2 = id_matrix(N);
	expRes = id_matrix(N);
	
	calcRes = parallel_matmul(id1, id2);

	EXPECT_TRUE(is_equal(expRes, calcRes));
	print_exp_rec(expRes, calcRes);
}

TEST(Predefined_parallel_test_valid, id_100) {
	int N = 100;
	Matrix<float> id1(N, N), id2(N, N), calcRes(N, N), expRes(N, N);
	id1 = id_matrix(N);
	id2 = id_matrix(N);
	expRes = id_matrix(N);
	
	calcRes = parallel_matmul(id1, id2);

	EXPECT_TRUE(is_equal(expRes, calcRes));
	print_exp_rec(expRes, calcRes, 5, 5);
}

TEST(Predefined_parallel_test_valid, NxK_KxM) {
	int N = 4;
	int K = 3;
	int M = 5;
	Matrix<float> a(N, K), b(K, M), calcRes(N, M), expRes(N, M);
	fill_n_4_k_3_m_5_matrices(a, b);
	fill_n_4_k_3_m_5_reference(expRes);

	calcRes = parallel_matmul(a, b);

	EXPECT_TRUE(is_equal(expRes, calcRes));
	print_exp_rec(expRes, calcRes);
}

//// Parallel vs reference test -------------------------------------------------------

TEST(Parallel_vs_reference_valid, id_3) {
	int N = 3;
	Matrix<float> id1(N, N), id2(N, N), refRes(N, N), parRes(N, N);
	id1 = id_matrix(N);
	id2 = id_matrix(N);
	
	refRes = ref_matmul(id1, id2);
	parRes = parallel_matmul(id1, id2);

	EXPECT_TRUE(is_equal(refRes, parRes));
	print_exp_rec(refRes, parRes);
}

TEST(Parallel_vs_reference_valid, id_100) {
	int N = 100;
	Matrix<float> id1(N, N), id2(N, N), refRes(N, N), parRes(N, N);
	id1 = id_matrix(N);
	id2 = id_matrix(N);
	
	refRes = ref_matmul(id1, id2);
	parRes = parallel_matmul(id1, id2);

	EXPECT_TRUE(is_equal(refRes, parRes));
	print_exp_rec(refRes, parRes, 5, 5);
}

TEST(Parallel_vs_reference_valid, NxK_KxM) {
	int N = 4;
	int K = 3;
	int M = 5;
	Matrix<float> a(N, K), b(K, M), refRes(N, M), parRes(N, M);
	fill_n_4_k_3_m_5_matrices(a, b);

	refRes = ref_matmul(a, b);
	parRes = parallel_matmul(a, b);

	EXPECT_TRUE(refRes == parRes);
	print_exp_rec(refRes, parRes);
}

TEST(Parallel_vs_reference_valid, random) {
	srand(time(0));

	for (int i = 0; i < 10; ++i) {

		cout << "Random test number " << i << ":\n";
		int N = posIntRand();
		int K = posIntRand();
		int M = posIntRand();
		Matrix<float> a(N, K), b(K, M), refRes(N, M), parRes(N, M);
		a = rand_matrix(N, K);
		b = rand_matrix(K, M);

		cout << "A = " << N << ", " << K << ":\n";
		print_matrix(a, 5, 5);
		cout << "B = " << K << ", " << M << ":\n";
		print_transp_matrix(b, 5, 5);

		refRes = ref_matmul(a, b);
		parRes = parallel_matmul(a, b);
		print_exp_rec(refRes, parRes, 5, 5);
		EXPECT_TRUE(refRes == parRes);
		EXPECT_TRUE(is_equal(refRes, parRes));
	}
}

///Random tests ---------------------------------------------------------------------

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  cout << endl;
  cout << "----------------------------------------------------------\n";
  cout << "------------------TESTS START-----------------------------\n";
  cout << "----------------------------------------------------------\n";
  cout << endl;

  return RUN_ALL_TESTS();
}