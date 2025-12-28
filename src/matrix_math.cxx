#include "matrix_math.h"
#include <iostream>
#define PI 3.1415926535

void Matrix4f::printSelf(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            std::cout << m[i*4 + j] << " ";
        }
        std::cout << "\n";
    }
}

// column-major index
float& Matrix4f::at(int i, int j){
    return m[i*4 + j];
}

float Matrix4f::at(int i, int j) const{
    return m[i*4 + j];
}

Matrix4f operator*(const Matrix4f &A, const Matrix4f &B){
    Matrix4f R;
    //for each row
    for(int i = 0; i < 4; i++){
        //for each col
        for(int j = 0; j < 4; j++){
            //for each num in the col
            float sum = 0.0f;
            for(int k = 0; k < 4; k++){
                sum += A.at(i, k) * B.at(k, j);
            }
            R.at(i, j) = sum;
        }
    }
    return R;
}

Matrix4f translate(const Matrix4f &matrix, float tx, float ty, float tz){
    Matrix4f translateMatrix(
    1, 0, 0, tx,
    0, 1, 0, ty,
    0, 0, 1, tz,
    0, 0, 0, 1
    );
    return matrix*translateMatrix;
}

Matrix4f scale(const Matrix4f &matrix, float sx, float sy, float sz){
    Matrix4f scaleMatrix(
    sx, 0, 0, 0,
    0, sy, 0, 0,
    0, 0, sz, 0,
    0, 0, 0, 1
    );
    return matrix*scaleMatrix;
}
//angle is in degrees
Matrix4f rotate2D(const Matrix4f &matrix, float angle){
    angle = PI*(angle/180.0f);
    float cy = cos(angle);
    float sy = sin(angle);
    
    Matrix4f rotMatrix(
    cy, -sy, 0, 0,
    sy, cy,  0, 0,
    0,   0,   1, 0,
    0,   0,   0, 1
    );
    return matrix*rotMatrix;
}