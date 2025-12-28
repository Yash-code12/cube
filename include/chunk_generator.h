#ifndef CHUNK_GENERATOR_H
#define CHUNK_GENERATOR_H

#include <vector>
#include <GLES2/gl2.h>

std::vector<GLfloat> makeChunk(float x, float y, float z, int cubesTowardX, int cubesTowardY, int cubesTowardZ);

#endif //CHUNK_GENERATOR_H