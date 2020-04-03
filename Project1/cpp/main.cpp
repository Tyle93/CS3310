#include "..\h\Matrix.h"
#include <iostream>

void standardMult(int n);
void divideAndConquer(int n);
void strassenRun(int n);

int main(){
    srand(time(NULL));
    //standardMult(32);
    //divideAndConquer(4);
    strassenRun(4);
}

void standardMult(int n){
    for(int i = 1; i < n; i*=2){
        auto matA = Matrix::generateMatrix(i);
        auto matB = Matrix::generateMatrix(i);
        auto matC = Matrix::generateMatrix(i,0);
        Matrix::mult(matA,matB,matC);
        std::cout << "n = " << i << std::endl << std::endl;
        Matrix::printMatrix(matA);
        Matrix::printMatrix(matB);
        Matrix::printMatrix(matC);
    }
}

void divideAndConquer(int n){
    auto matA = Matrix::generateMatrix(n);
    Matrix::printMatrix(matA);
    auto matB = Matrix::generateMatrix(n);
    Matrix::printMatrix(matB);
    auto matC = Matrix::divConq(matA,matB);
    std::cout << "n = " << n << std::endl << std::endl;
    Matrix::printMatrix(matC);
}

void strassenRun(int n){
    std::cout << "n = " << n << std::endl << std::endl;
    auto matA = Matrix::generateMatrix(n);
    Matrix::printMatrix(matA);
    auto matB = Matrix::generateMatrix(n);
    Matrix::printMatrix(matB);
    auto matC = Matrix::strassen(matA,matB);
    Matrix::printMatrix(matC);
}


