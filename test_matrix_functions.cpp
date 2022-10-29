#include <gtest/gtest.h>
#include <iostream>

#include "Matrix.h"
#include "matrix_functions.h"

TEST(Calculations, id_matrices) {
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
	
	calcRes = matmul(id1, id2);

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