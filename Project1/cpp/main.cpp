#include "..\h\Matrix.h"
#include <iostream>

void standardMult(int n);

int main(){
    standardMult(32);
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

