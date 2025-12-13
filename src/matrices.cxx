#include "matrices.h"
#include <cmath>
#define PI 3.1415926538f
#include <iostream>
void setProjectionMatrix(GLuint program, GLuint projLoc, float width, float height) {
    float fov = (60.0f / 180.0f) * PI;
    float n = 1.0f;
    float f = 100.0f;
    float a = width / height;
    
    GLfloat projMtx[16] = {
        1.0f / (a * tan(fov * 0.5f)), 0, 0, 0,
        0, 1.0f / (tan(fov * 0.5f)), 0, 0,
        0, 0, -(f+n) / (f - n),  -(2*f*n) / (f - n),
        0.0f, 0.0f, -1.0f, 0
    };
    
    /*
    GLfloat projMtx[16] = {
        1.0f / (a * tan(fov * 0.5f)), 0, 0, 0,
        0, 1.0f / (tan(fov * 0.5f)), 0, 0,
        0, 0, -f / (f - n),  -n * f / (f - n),
        0.0f, 0.0f, -1.0f, 0
    };
    */
    
    glUseProgram(program);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projMtx);
}

//translation of camera (position)
void setViewMatrix(GLuint program, GLuint viewLoc, float camX, float camY, float camZ){
    
    GLfloat viewMtx[16] = {
        1, 0, 0, -camX,
        0, 1, 0, -camY,
        0, 0, 1, -camZ,
        0, 0, 0, 1
    };
    
    glUseProgram(program);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, viewMtx);
}

//rotation of camera (direction cam faces)
void setRotMatrix(GLuint program, GLuint rotLoc, float rotX, float rotY, float rotZ){
    
    GLfloat rotMtx[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        -rotX, -rotY, -rotZ, 1
    };
    
    glUseProgram(program);
    glUniformMatrix4fv(rotLoc, 1, GL_FALSE, rotMtx);
}