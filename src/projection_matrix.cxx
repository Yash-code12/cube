#include "projection_matrix.h"
#include <cmath>
#define PI 3.1415926538f
#include <iostream>
void SetProjectionMatrix(GLuint program, GLuint projLoc, float width, float height) {
    float fov = (60.0f / 180.0f) * PI;
    float n = 1.0f;
    float f = 100.0f;
    float a = width / height;
    
    GLfloat projMtx[16] = {
        1.0f / (a * tan(fov * 0.5f)), 0, 0, 0,
        0, 1.0f / (tan(fov * 0.5f)), 0, 0,
        0, 0, f / (f - n),  -n * f / (f - n),
        0, 0, 1.0, 0
    };
    
    glUseProgram(program);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projMtx);
}