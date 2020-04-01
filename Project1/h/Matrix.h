#include <vector>
#include <cmath>
#include <time.h>
#include <iostream>

namespace Matrix{
    void mult(std::vector<std::vector<int>> matA, std::vector<std::vector<int>> matB, std::vector<std::vector<int>> &matC) {
        for (int i = 0; i < matC.size(); i++) {
            for (int k = 0; k < matC.size(); k++) {
                for (int j = 0; j < matC.size(); j++) {
                matC[i][j] += matA[i][k] * matB[k][j];
                }
            }
        }   
    }
    std::vector<std::vector<int>> mult(std::vector<std::vector<int>> matA, std::vector<std::vector<int>> matB) {
        auto matC = Matrix::generateMatrix(matA.size(),0);
        for (int i = 0; i < matA.size(); i++) {
            for (int k = 0; k < matA.size(); k++) {
                for (int j = 0; j < matA.size(); j++) {
                    matC[i][j] += matA[i][k] * matB[k][j];
                }
            }
        }  
        return matC; 
    }
    std::vector<std::vector<int>> add(std::vector<std::vector<int>> A,std::vector<std::vector<int>> B){

    }
    void sub(){

    }
    void partition(std::vector<std::vector<int>> &original,
                    std::vector<std::vector<int>> &M11,
                    std::vector<std::vector<int>> &M12,
                    std::vector<std::vector<int>> &M21,
                    std::vector<std::vector<int>> &M22){
        int n = M11.size();
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                M11[i][j] = original[i][j];
                M12[i][j] = original[i][j + n];
                M21[i][j] = original[i + n][j];
                M22[i][j] = original[i + n][j + n];
            }
        }
        
    }
    std::vector<std::vector<int>> divConqMult(std::vector<std::vector<int>> matA, std::vector<std::vector<int>> matB){
        int n = matA.size();
        if(n <= 1){
            return Matrix::mult(matA,matB);
        }else{
            int newSize = Matrix::getNextPower2(n/2);
            std::vector<std::vector<int>> A11(newSize, std::vector<int>(newSize,0));
            std::vector<std::vector<int>> A12(newSize, std::vector<int>(newSize,0));
            std::vector<std::vector<int>> A21(newSize, std::vector<int>(newSize,0));
            std::vector<std::vector<int>> A22(newSize, std::vector<int>(newSize,0));
            std::vector<std::vector<int>> B11(newSize, std::vector<int>(newSize,0));
            std::vector<std::vector<int>> B12(newSize, std::vector<int>(newSize,0));
            std::vector<std::vector<int>> B21(newSize, std::vector<int>(newSize,0));
            std::vector<std::vector<int>> B22(newSize, std::vector<int>(newSize,0));
            std::vector<std::vector<int>> C11(newSize, std::vector<int>(newSize,0));
            std::vector<std::vector<int>> C12(newSize, std::vector<int>(newSize,0));
            std::vector<std::vector<int>> C21(newSize, std::vector<int>(newSize,0));
            std::vector<std::vector<int>> C22(newSize, std::vector<int>(newSize,0));

            partition(matA,A11,A12,A21,A22);
            partition(matB,B11,B12,B21,B22);

            C11 = Matrix::add(divConqMult(A11,B11),divConqMult(A12,B21));

            
        }
    }
    int getNextPower2(int n) {
        return pow(2, int(ceil(log2(n))));
    }
    std::vector<std::vector<int>> generateMatrix(int n){
        srand(time(NULL));
        std::vector<std::vector<int>> ret(n, std::vector<int>(n,0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                ret[i][j] = rand() % 10;
            }
        }
        return ret;
    }
    std::vector<std::vector<int>> generateMatrix(int n, int defaultVal){
        srand(time(NULL));
        std::vector<std::vector<int>> ret(n, std::vector<int>(n,defaultVal));
        return ret;
    }

    void printMatrix(std::vector<std::vector<int>> &mat){
        for (int i = 0; i < mat.size(); i++) {
            for (int j = 0; j < mat[i].size(); j++) {
                std::cout << mat[i][j] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << std::endl; 
    }
}