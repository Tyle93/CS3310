#include "..\h\Matrix.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <map>
#include <fstream>
#include <iterator>

void standardMult(int n, std::vector<std::vector<int>> matA, std::vector<std::vector<int>> matB);
void divideAndConquer(int n, std::vector<std::vector<int>> matA, std::vector<std::vector<int>> matB);
void strassenRun(int n , std::vector<std::vector<int>> matA, std::vector<std::vector<int>> matB);

int main(int argc, char** argv){
    int n;
    if(argc > 1){
        n = atoi(argv[1]);
    }else{
        n = 2;
    }
    srand(time(NULL));
    auto matA = Matrix::generateMatrix(n);
    auto matB = Matrix::generateMatrix(n);
    standardMult(n,matA,matB);
    //divideAndConquer(n,matA,matB);
    //strassenRun(n,matA,matB);
}

void standardMult(int n, std::vector<std::vector<int>> matA, std::vector<std::vector<int>> matB){
    std::map<int, double> times;
    int runs = 32;
    for(int i = n; i <= 2048; i*=2){
        double totalTime = 0;
        for(int j = 0; j < 32;j++){
            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
            auto newA = Matrix::resize(matA,i);
            auto newB = Matrix::resize(matB,i);
            auto matC = Matrix::mult(matA,matB);
            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> trialTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);    
            totalTime += trialTime.count();
        }
        double elapsedTime = totalTime/runs;
        times.insert(std::pair<int,double>(i,elapsedTime));
    }
    std::map<int,double>::iterator itr;
    std::cout << "Runs per matrix of size n: " << runs << std::endl << std::fixed;
    std::cout.precision(3);
    for(itr = times.begin(); itr != times.end();++itr){
        std::cout << "n="<< itr->first << "\t" 
                         << itr->second*1000 << "ms" << std::endl;
    }
}

void divideAndConquer(int n, std::vector<std::vector<int>> matA, std::vector<std::vector<int>> matB){
    std::cout << "n = " << n << std::endl << std::endl;
    Matrix::printMatrix(matA);
    Matrix::printMatrix(matB);
    auto matC = Matrix::divConq(matA,matB);
    std::cout << "n = " << n << std::endl << std::endl;
    Matrix::printMatrix(matC);
}

void strassenRun(int n, std::vector<std::vector<int>> matA, std::vector<std::vector<int>> matB){
    std::cout << "n = " << n << std::endl << std::endl;
    Matrix::printMatrix(matA);
    Matrix::printMatrix(matB);
    auto matC = Matrix::strassen(matA,matB);
    Matrix::printMatrix(matC);
}


