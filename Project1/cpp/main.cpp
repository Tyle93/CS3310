#include "..\h\Matrix.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <map>
#include <fstream>
#include <iomanip>
#include <iterator>

void matrixTest(int n, std::vector<std::vector<int>> matA, std::vector<std::vector<int>> matB, std::string fileName, std::vector<std::vector<int>> (*matrixMult)(const std::vector<std::vector<int>>&, const std::vector<std::vector<int>>& ));

std::string output = "Output.csv";
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
    matrixTest(n,matA,matB, "StandardMatrixMult", Matrix::mult);
    matrixTest(n,matA,matB, "DivideAndConquerMult" , Matrix::divConq);
    matrixTest(n,matA,matB, "StassenMult" , Matrix::strassen);
}

void matrixTest(int n, std::vector<std::vector<int>> matA, std::vector<std::vector<int>> matB, std::string fileName ,std::vector<std::vector<int>> (*matrixMult)(const std::vector<std::vector<int>>& ,const std::vector<std::vector<int>>& )){
    std::map<int, double> times;
    int runs = 32;
    for(int i = n; i <= 2048*8; i*=2){
        double totalTime = 0;
        for(int j = 0; j < runs;j++){
            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
            auto newA = Matrix::resize(matA,i);
            auto newB = Matrix::resize(matB,i);
            auto matC = matrixMult(matA,matB);
            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> trialTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);    
            totalTime += trialTime.count();
        }
        double elapsedTime = totalTime/runs;
        times.insert(std::pair<int,double>(i,elapsedTime));
    }
    std::ofstream file(fileName + output, std::ofstream::trunc);
    file << std::fixed << std::setprecision(3);
    std::map<int,double>::iterator itr;
    std::cout << "Runs per matrix of size n: " << runs << std::endl << std::fixed;
    std::cout.precision(3);
    for(itr = times.begin(); itr != times.end();++itr){
        std::cout << "n="<< itr->first << "\t" 
                         << itr->second*1000 << "ms" << std::endl;
        file << itr->first << "," << itr->second*1000 << "\n";
    }
    file.close();
}

