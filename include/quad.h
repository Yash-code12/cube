#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <GLES2/gl2.h>
std::vector<GLfloat> makeQuad(std::vector<GLfloat>& faceValues);
std::vector<GLfloat> makeCube(std::vector<GLfloat> vertices);

#endif //CUBE_H