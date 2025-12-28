#ifndef WORLD_MATRICES_H
#define WORLD_MATRICES_H

#include <GLES2/gl2.h>

void setProjectionMatrix(GLuint program, GLuint projLoc, float width, float height);
void setViewMatrix(GLuint program, GLuint viewLoc, float camX, float camY, float camZ, float yaw, float pitch);

#endif //WORLD_MATRICES_H