#pragma once
#include <GLES2/gl2.h>
void setProjectionMatrix(GLuint program, GLuint projLoc, float width, float height);
void setViewMatrix(GLuint program, GLuint viewLoc, float camX, float camY, float camZ);
void setRotMatrix(GLuint program, GLuint rotLoc, float rotX, float rotY, float rotZ);