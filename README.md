# FSE_project_group_7
This is a repo for Foundations of Software Engineering project.

Simple matrix multiplication parallelized algo using OpenMP library and Matrix dataclass https://github.com/pwwiur/Matrix

### Project structure
* main.cpp - example of usage
* Matrix.h - realization of matrix class
* matrix_functions.cpp - functions to work with matrices
* test_matrix_functions - tests for matrix functions

### build the image from dockerfile and run the container
```
docker build -t project:v1  -f Dockerfile .
docker run -it project:v1
```

### Launch
To run:
```
sudo apt install g++
sudo apt install libomp-dev
g++ main.cpp matrix_functions.cpp -fopenmp -o main
./main
```

### Testing
To install testing framework:
```
./test_libs_install.sh
```

To test:
```
./test_run.sh
```

IMPORTANT NOTE: supposed start from project directory within Docker container, otherwise add sudo command to scripts.
