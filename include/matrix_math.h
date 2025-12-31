#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

//Row major as its stored countinously in memory
class Matrix4f{
public:
    float m[16];
    //defualt init (identity matrix)
    Matrix4f(){
    m[0] = 1; m[1] = 0; m[2] = 0;  m[3] = 0; 
    m[4] = 0; m[5] = 1; m[6] = 0; m[7] = 0; 
    m[8] = 0; m[9] = 0; m[10] = 1; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15]= 1;
    }
    Matrix4f(
    float a00, float a01, float a02, float a03,
    float a10, float a11, float a12, float a13,
    float a20, float a21, float a22, float a23,
    float a30, float a31, float a32, float a33
    ){
        m[0] = a00; m[1] = a10; m[2] = a20; m[3] = a30; 
        m[4] = a01; m[5] = a11; m[6] = a21; m[7] = a31; 
        m[8] = a02; m[9] = a12; m[10] = a22; m[11] = a32;
        m[12] = a03; m[13] = a13; m[14] = a23; m[15] = a33;
    }
    float& at(int i, int j);
    float at(int i, int j) const;
    
    void printSelf();
};
//proper matrix mul order should be right to left becuase col major matrices
Matrix4f operator*(const Matrix4f &A, const Matrix4f &B);

Matrix4f translate(const Matrix4f &matrix, float tx, float ty, float tz);

Matrix4f scale(const Matrix4f &matrix, float sx, float sy, float sz);

Matrix4f rotate2D(const Matrix4f &matrix, float angle);

#endif //MATRIX_MATH_H