#include "../cpp/Matrix.cpp"

std::vector<std::vector<int>> Matrix::generateMatrix(int n){
    std::vector<std::vector<int>> ret(n, std::vector<int>(n,0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            ret[i][j] = rand() % 10;
        }
    }
    return ret;
}
std::vector<std::vector<int>> Matrix::generateMatrix(int n, int defaultVal){
    std::vector<std::vector<int>> ret(n, std::vector<int>(n,defaultVal));
    return ret;
}
int Matrix::getNextPower2(int n) {
    return pow(2, int(ceil(log2(n))));
}
std::vector<std::vector<int>> Matrix::resize(const std::vector<std::vector<int>> &mat,int n ){
    int size = mat.size();
    int m = getNextPower2(n);
    auto newMat = Matrix::generateMatrix(m,0);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            newMat[i][j] = mat[i][j];
        }
    }
    return newMat;
}
std::vector<std::vector<int>> Matrix::mult(const std::vector<std::vector<int>> &matA, const std::vector<std::vector<int>> &matB) {
    auto matC = Matrix::generateMatrix(matA.size(),0);
    for (int i = 0; i < matC.size(); i++) {
        for (int k = 0; k < matC.size(); k++) {
            for (int j = 0; j < matC.size(); j++) {
                matC[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }  
    return matC; 
}
std::vector<std::vector<int>> Matrix::add(const std::vector<std::vector<int>> &A,const std::vector<std::vector<int>> &B){
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n,0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}
std::vector<std::vector<int>> Matrix::sub(const std::vector<std::vector<int>> &A,const std::vector<std::vector<int>> &B){
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n,0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}
void Matrix::partition(const std::vector<std::vector<int>> &original,
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
std::vector<std::vector<int>> Matrix::strassenMult(const std::vector<std::vector<int>> &matA, const std::vector<std::vector<int>> &matB){
    int n = matA.size();
    if(n == 2){
        return Matrix::mult(matA,matB);
    }else{
        
        int newSize = n/2;
        auto A11 = Matrix::generateMatrix(newSize,0);
        auto A12 = Matrix::generateMatrix(newSize,0);
        auto A21 = Matrix::generateMatrix(newSize,0);
        auto A22 = Matrix::generateMatrix(newSize,0);
        auto B11 = Matrix::generateMatrix(newSize,0);
        auto B12 = Matrix::generateMatrix(newSize,0);
        auto B21 = Matrix::generateMatrix(newSize,0);
        auto B22 = Matrix::generateMatrix(newSize,0);

        partition(matA,A11,A12,A21,A22);
        partition(matB,B11,B12,B21,B22);

        auto P1 =  Matrix::strassenMult(Matrix::add(A11,A22),Matrix::add(B11,B22));
        auto P2 =  Matrix::strassenMult(Matrix::add(A21,A22),B11);
        auto P3 =  Matrix::strassenMult(A11,Matrix::sub(B12,B22));
        auto P4 =  Matrix::strassenMult(A22,Matrix::sub(B21,B11));
        auto P5 =  Matrix::strassenMult(Matrix::add(A11,A12),B22);
        auto P6 =  Matrix::strassenMult(Matrix::sub(A21,A11),Matrix::add(B11,B12));
        auto P7 =  Matrix::strassenMult(Matrix::sub(A12,A22),Matrix::add(B21,B22));

        auto C11 = Matrix::sub(Matrix::add(P1,P4),Matrix::add(P5,P7));
        auto C12 = Matrix::add(P3,P5);
        auto C21 = Matrix::add(P2,P4);
        auto C22 = Matrix::sub(Matrix::add(P1,P3),Matrix::add(P2,P6));

        auto matC = Matrix::generateMatrix(n,0);
        for(int i = 0; i < newSize; i++){
            for(int j = 0; j < newSize; j++){
                matC[i][j] = C11[i][j];
                matC[i][j + newSize] = C12[i][j];
                matC[i + newSize][j] = C21[i][j];
                matC[i + newSize][j + newSize] = C22[i][j];
            }
        }
        return matC;
    }
}
std::vector<std::vector<int>> Matrix::divConqMult(const std::vector<std::vector<int>> &matA, const std::vector<std::vector<int>> &matB){
    int n = matA.size();
    if(n <= 1){
        return Matrix::mult(matA,matB);
    }else{
        
        int newSize = n/2;

        std::vector<std::vector<int>> A11(newSize, std::vector<int>(newSize,0));
        std::vector<std::vector<int>> A12(newSize, std::vector<int>(newSize,0));
        std::vector<std::vector<int>> A21(newSize, std::vector<int>(newSize,0));
        std::vector<std::vector<int>> A22(newSize, std::vector<int>(newSize,0));
        std::vector<std::vector<int>> B11(newSize, std::vector<int>(newSize,0));
        std::vector<std::vector<int>> B12(newSize, std::vector<int>(newSize,0));
        std::vector<std::vector<int>> B21(newSize, std::vector<int>(newSize,0));
        std::vector<std::vector<int>> B22(newSize, std::vector<int>(newSize,0));

        partition(matA,A11,A12,A21,A22);
        partition(matB,B11,B12,B21,B22);

        auto C11 = Matrix::add(Matrix::divConqMult(A11,B11),Matrix::divConqMult(A12,B21));
        auto C12 = Matrix::add(Matrix::divConqMult(A11,B12),Matrix::divConqMult(A12,B22));
        auto C21 = Matrix::add(Matrix::divConqMult(A21,B11),Matrix::divConqMult(A22,B21));
        auto C22 = Matrix::add(Matrix::divConqMult(A21,B12),Matrix::divConqMult(A22,B22));

        auto matC = Matrix::generateMatrix(n);

        for(int i = 0; i < newSize; i++){
            for(int j = 0; j < newSize; j++){
                matC[i][j] = C11[i][j];
                matC[i][j + newSize] = C12[i][j];
                matC[i + newSize][j] = C21[i][j];
                matC[i + newSize][j + newSize] = C22[i][j];
            }
        }
        return matC;
    }
}
std::vector<std::vector<int>> Matrix::strassen(const std::vector<std::vector<int>> &matA, const std::vector<std::vector<int>> &matB){
    int size = matA.size();
    auto newA = Matrix::resize(matA,size);
    auto newB = Matrix::resize(matB,size);
    auto matC = Matrix::strassenMult(newA,newB);
    auto shrunkMat = Matrix::generateMatrix(size,0);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            shrunkMat[i][j] = matC[i][j];
        }
    }
    return shrunkMat;
}
std::vector<std::vector<int>> Matrix::divConq(const std::vector<std::vector<int>> &matA, const std::vector<std::vector<int>> &matB){
    int size = matA.size();
    auto newA = Matrix::resize(matA,size);
    auto newB = Matrix::resize(matB,size);
    auto matC = Matrix::divConqMult(newA,newB);
    auto shrunkMat = Matrix::generateMatrix(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            shrunkMat[i][j] = matC[i][j];
        }
    }
    return shrunkMat;
}
void Matrix::printMatrix(const std::vector<std::vector<int>> &mat){
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            std::cout << mat[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl; 
}
