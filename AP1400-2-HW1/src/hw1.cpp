#include "hw1.h"
#include <random>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>

namespace algebra{
    static inline void check_empty_matrix(const Matrix& matrix){
        if(matrix.empty()){
            throw std::logic_error("This is an empty matrix!");
        }
    }
    Matrix zeros(size_t n, size_t m){
        Matrix matrix(n,std::vector<double>(m,0.0));
        return matrix;
    }

    Matrix ones(size_t n, size_t m){
        Matrix matrix(n,std::vector<double>(m,1.0));
        return matrix;
    }

    Matrix random(size_t n, size_t m, double min, double max){
        if (max<min){
            throw std::logic_error("Min cannot bigger than Max!");
        }
        std::mt19937 e(std::random_device{}());
        std::uniform_real_distribution<double> u(min, max);
        Matrix matrix(n,std::vector<double>(m));
        for(auto& row:matrix){
            for (auto& elem:row){
                elem = u(e);
            }
        }
        return matrix;
    }

    void show(const Matrix& matrix){
        check_empty_matrix(matrix);
        for(auto& row:matrix){
            std::cout<<" | ";
            for(auto elem:row){
                std::cout << std::fixed << std::setprecision(3)<<elem<<" | ";
            }
            std::cout<<std::endl;
        }
    }

    Matrix multiply(const Matrix& matrix, double c){
        check_empty_matrix(matrix);
        Matrix matrix_return(matrix);
        for(auto& row:matrix_return){
            for (auto& elem:row){
                elem *= c;
            }
        }
        return matrix_return;
    }

    Matrix multiply(const Matrix& Matrix1, const Matrix& Matrix2){
        if (Matrix1.empty()&&Matrix2.empty()){
            return Matrix1;
        }else{
            check_empty_matrix(Matrix1);
            check_empty_matrix(Matrix2);
        }
        size_t a = Matrix1.size();
        size_t b = Matrix1[0].size();
        size_t c = Matrix2.size();
        size_t d = Matrix2[0].size();   //a==d
        if (b != c) {
            throw std::logic_error("these two matrices can't multiply!");
        }
        Matrix mat = zeros(a,d);
        for (int i = 0; i<a; i++){
            for (int j = 0; j<d; j++){
                for(int k = 0; k<b; k++){
                    mat[i][j] += Matrix1[i][k]*Matrix2[k][j];
                }
            }
        }
        return mat;
    }

    Matrix sum(const Matrix& matrix, double c){
        if(matrix.empty()){
            return matrix;
        }
        Matrix mat(matrix);
        for(auto& row:mat){
            for(auto& elem:row){
                elem+=c;
            }
        }
        return mat;
    }

    Matrix sum(const Matrix& matrix1, const Matrix& matrix2){  
        if (matrix1.empty()&&matrix2.empty()){
            return matrix1;
        }else{
            check_empty_matrix(matrix1);
            check_empty_matrix(matrix2);
        }
        if(matrix1.size()!=matrix2.size() && matrix1[0].size()!=matrix2[0].size()){
            throw std::runtime_error("these two matrices can't sum!");
        }
        Matrix mat(matrix1);
        for (int i = 0;i<matrix1.size();i++){
            for(int j =0;j<matrix1[0].size();j++){
                mat[i][j] = matrix1[i][j]+matrix2[i][j];
            }
        }
        return mat;
    }

    Matrix transpose(const Matrix& matrix){
        if(matrix.empty()){
            return matrix;
        }
        size_t n = matrix.size();
        size_t m = matrix[0].size();
        Matrix mat = zeros(m,n);
        for(int i = 0;i<n;i++){
            for(int j = 0;j<m;j++){
                mat[j][i]=matrix[i][j];
            }
        }
        return mat;
    }

    Matrix minor(const Matrix& matrix, size_t n, size_t m){
        check_empty_matrix(matrix);
        size_t rows = matrix.size()-1;
        size_t cols = matrix[0].size()-1;
        if (rows<n || cols<m){
            throw std::out_of_range("Index out of range!");
        }
        Matrix mat = zeros(rows,cols);
        size_t result_rows=0;
        for (size_t i =0;i<=rows;i++){
            if(i==n){ continue;}
            size_t result_cols=0;
            for(size_t j =0;j<=cols;j++){
                if(j==m){ continue;}
                mat[result_rows][result_cols]=matrix[i][j];
                
                result_cols++;

            }
            result_rows++;
        }
        return mat;
    }
    double determinant(const Matrix& matrix){
        if(matrix.empty()){
            return 1.00;
        }
        size_t rows = matrix.size();
        size_t cols =matrix[0].size();
        if(rows!=cols){
            throw std::invalid_argument("Matrix must be square to compute the determinant.");
        }
        double result =0.0;
        if(rows>1){
            for(int i =0;i<rows;i++){
                result += matrix[i][0] * determinant(minor(matrix,i,0)) *pow(-1.0,i);
            }
        }else{
            result = matrix[0][0];
        }
        return result;
    }

    Matrix inverse(const Matrix& matrix){
        if(matrix.empty()){
            return matrix;
        }
        Matrix adj_matrix = zeros(matrix.size(),matrix[0].size());
        for(int i =0 ;i<matrix.size();i++){
            for(int j =0;j<matrix[0].size();j++){
                adj_matrix[i][j]=determinant(minor(matrix,i,j))*pow(-1,i+j);
            }
        }
        Matrix trans_matrix = transpose(adj_matrix);
        double det = determinant(matrix);
        if (det == 0){
            throw std::logic_error("Cannot invert a matrix with zero determinant.");
        }
        return multiply(trans_matrix,1.0/det);
    }

    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis){
        check_empty_matrix(matrix1);
        check_empty_matrix(matrix2);
        size_t row1 = matrix1.size();
        size_t col1 = matrix1[0].size();
        size_t row2 = matrix2.size();
        size_t col2 = matrix2[0].size();
        Matrix mat(matrix1);
        if (axis==0){
            if(col1!=col2) {
                throw std::logic_error("Cannot concatenate these two matrix");
            }
            for(auto& rows:matrix2){
                mat.push_back(rows);
            }
        }
        if(axis == 1){
            if(row1 != row2){
                throw std::logic_error("Cannot concatenate these two matrix");
            }
            for(int i = 0;i<row2;i++){
                for(int j =0; j<col2;j++){
                    mat[i].push_back(matrix2[i][j]);
                }
            }
        }
        return mat;
    }

    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2){
        if (!(r1 < matrix.size() && r2 < matrix.size()))
		{
			throw std::logic_error("Index out of range!");
		}
        Matrix mat(matrix);
        mat[r1]=matrix[r2];
        mat[r2]=matrix[r1];
        return mat;
    }

    Matrix ero_multiply(const Matrix& matrix, size_t r, double c){
        check_empty_matrix(matrix);
        if(r>matrix.size()){
            throw std::logic_error("Index out of range!");
        }
        Matrix mat(matrix);
        auto& row = mat[r];
        for(auto& elem :row){
            elem *= c;
        }
        return mat;
    }

    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2){
        check_empty_matrix(matrix);
        if(r1> matrix.size()||r2>matrix.size()){
            throw std::out_of_range("Index out of range!");
        }
        Matrix mat(matrix);
        for(int i =0;i<mat[r1].size();i++){
            mat[r2][i] += mat[r1][i]*c;
        }
        return mat;
    }

    Matrix upper_triangular(const Matrix& matrix){
        if(matrix.empty()){
            return matrix;
        }
        if(matrix.size()!=matrix[0].size()){
            throw std::logic_error("This matrix can't be upper_triangular!");
        }
        size_t row =matrix.size();
        size_t col =matrix[0].size();
        Matrix mat(matrix);
        if(row != col){
            throw std::runtime_error("Cannot upper_triangular this matrix");
        }
        for(int i=0;i<row-1;i++){
            for(int j= int(row)-1;j>i;j--){
                //if(mat[j-1][i]==0){
                  //  mat=ero_swap(mat,j,j-1);
                //}
                //mat=ero_sum(mat,j,mat[j][i]/mat[j-1][i],j-1);
                if(mat[j][i]==0){    //两个都等于0,或者后面一个等于0,直接向前
                    continue;
                }else if(mat[j-1][i]==0){            //后面那个不等于0,前面那个等于0,直接交换
                    mat=ero_swap(mat,j,j-1);
                }else{
                    mat=ero_sum(mat,j-1,-1*mat[j][i]/mat[j-1][i],j);
                }
            }
        }
        return mat;
    }
}