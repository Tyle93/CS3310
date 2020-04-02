#include <vector>
#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>    
#include <cmath>
#include <time.h>
#include <iostream>


namespace Matrix{
    std::vector<std::vector<int>> generateMatrix(int n);
    std::vector<std::vector<int>> generateMatrix(int n, int defaultVal);
    int getNextPower2(int n);
    std::vector<std::vector<int>> resize(const std::vector<std::vector<int>> &mat,int n );
    void mult(const std::vector<std::vector<int>> &matA, const std::vector<std::vector<int>> &matB, std::vector<std::vector<int>> &matC) ;
    std::vector<std::vector<int>> mult(const std::vector<std::vector<int>>& matA, const std::vector<std::vector<int>> &matB) ;
    std::vector<std::vector<int>> add(const std::vector<std::vector<int>> &A,const std::vector<std::vector<int>> &B);
    std::vector<std::vector<int>> sub(const std::vector<std::vector<int>> &A,const std::vector<std::vector<int>> &B);
    void partition(const std::vector<std::vector<int>> &original,
                    std::vector<std::vector<int>> &M11,
                    std::vector<std::vector<int>> &M12,
                    std::vector<std::vector<int>> &M21,
                    std::vector<std::vector<int>> &M22);
    std::vector<std::vector<int>> divConqMult(const std::vector<std::vector<int>> &matA, const std::vector<std::vector<int>> &matB);
    std::vector<std::vector<int>> divConq(const std::vector<std::vector<int>> &matA, const std::vector<std::vector<int>> &matB);
    void printMatrix(const std::vector<std::vector<int>> &mat);
    std::vector<std::vector<int>> strassenMult(const std::vector<std::vector<int>> &matA, const std::vector<std::vector<int>> &matB);
    std::vector<std::vector<int>> strassen(const std::vector<std::vector<int>> &matA, const std::vector<std::vector<int>> &matB);   
}