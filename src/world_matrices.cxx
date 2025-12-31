#include "world_matrices.h"
#include "matrix_math.h"
#include <cmath>
#define PI 3.1415926538f
#include <iostream>

/*
The output matrix should be column-major that is fill columns first
The GL_False in
glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrixInMemory);
says "do not transpose"

Matrix-vector multiplication in opengl
M*v
where M and v are both column majorl
*/
void setProjectionMatrix(GLuint program, GLuint projLoc, float width, float height) {
    float fov = (60.0f / 180.0f) * PI;
    float n = 0.5f;
    float f = 100.0f;
    float a = width / height;
    
    //correct projMtx from calculations for z € [-n, f-]
    Matrix4f projMtx(
    1.0f / (a * tan(fov * 0.5f)), 0, 0, 0,
    0, 1.0f / (tan(fov * 0.5f)), 0, 0,
    0, 0, -(f+n) / (f - n),  -(2*f*n) / (f - n),
    0.0f, 0.0f, -1.0f, 0
    );
    
    glUseProgram(program);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projMtx.m);
}

//cameta position and view direction
//scale, rotate then translate
void setViewMatrix(GLuint program, GLuint viewLoc, float camX, float camY, float camZ, float yaw, float pitch){
    
    float cy = cos(yaw);
    float sy = sin(yaw);
    float cx = cos(pitch);
    float sx = sin(pitch);
    
    Matrix4f YRot(
    cy, 0, -sy, 0,
    0,   1, 0,    0,
    sy, 0, cy,  0,
    0,   0, 0,   1
    );
    
    Matrix4f XRot(
    1, 0,   0,    0,
    0, cx, -sx, 0,
    0, sx, cx,  0,
    0, 0,   0,    1
    );
    
    Matrix4f Translate(
    1, 0, 0, -camX,
    0, 1, 0, -camY,
    0, 0, 1, -camZ,
    0, 0, 0, 1
    );
    //matrix mul order goes right to left becuase col major matrices
    Matrix4f viewMtx = Translate * (YRot * XRot);
    
    glUseProgram(program);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, viewMtx.m);
}