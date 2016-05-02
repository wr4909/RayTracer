#include "Matrix.hpp"

// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/ray-traced-images.zip

Matrix::Matrix(){
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++) {
            if (x == y)
                m[x][y] = 1.0;
            else
                m[x][y] = 0.0;
        }
}

Matrix&
Matrix::operator= (const Matrix& rhs){
    if (this == &rhs)
        return (*this);
    
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
            m[x][y] = rhs.m[x][y];
    
    return (*this);
}

Matrix
Matrix::operator* (const Matrix& mat) const{
    Matrix 	product;
    
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++) {
            double sum = 0.0;
            
            for (int j = 0; j < 4; j++)
                sum += m[x][j] * mat.m[j][y];
            
            product.m[x][y] = sum;			
        }
    
    return (product);
}

Matrix
Matrix::operator/ (const double d){
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
            m[x][y] = m[x][y] / d;
    
    return (*this);
}

void
Matrix::set_identity(void){
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++) {
            if (x == y)
                m[x][y] = 1.0;
            else
                m[x][y] = 0.0;
        }
}
// #419end
/*
double
Matrix::det() const{
    double detA =   m[0][0]*m[1][1]*m[2][2]*m[3][3] + m[0][0]*m[1][2]*m[2][3]*m[3][1] + m[0][0]*m[1][3]*m[2][1]*m[3][2] +
                    m[0][1]*m[1][0]*m[2][3]*m[3][2] + m[0][1]*m[1][2]*m[2][0]*m[3][3] + m[0][1]*m[1][3]*m[2][2]*m[3][0] +
                    m[0][2]*m[1][0]*m[2][1]*m[3][3] + m[0][2]*m[1][1]*m[2][3]*m[3][0] + m[0][2]*m[1][3]*m[2][0]*m[3][1] +
                    m[0][3]*m[1][0]*m[2][2]*m[3][1] + m[0][3]*m[1][1]*m[2][0]*m[3][2] + m[0][3]*m[1][2]*m[2][1]*m[3][0] -
                    m[0][0]*m[1][1]*m[2][3]*m[3][2] - m[0][0]*m[1][2]*m[2][1]*m[3][3] - m[0][0]*m[1][3]*m[2][2]*m[3][1] -
                    m[0][1]*m[1][0]*m[2][2]*m[3][3] - m[0][1]*m[1][2]*m[2][3]*m[3][0] - m[0][1]*m[1][3]*m[2][0]*m[3][2] -
                    m[0][2]*m[1][0]*m[2][3]*m[3][1] - m[0][2]*m[1][1]*m[2][0]*m[3][3] - m[0][2]*m[1][3]*m[2][1]*m[3][0] -
                    m[0][3]*m[1][0]*m[2][1]*m[3][2] - m[0][3]*m[1][1]*m[2][2]*m[3][0] - m[0][3]*m[1][2]*m[2][0]*m[3][1];
    return detA;
}*/