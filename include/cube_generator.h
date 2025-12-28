#ifndef CUBE_GENERATOR_H
#define CUBE_GENERATOR_H

#include <vector>
#include <GLES2/gl2.h>

std::vector<GLfloat> makeQuad(std::vector<GLfloat>& faceValues);

std::vector<GLfloat> makeCube(std::vector<GLfloat> vertices);

std::vector<GLfloat> makeVertices(float x, float y, float z);

#endif //CUBE_GENERATOR_H