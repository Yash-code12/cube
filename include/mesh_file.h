#ifndef MESH_FILE_H
#define MESH_FILE_H

#include <GLES2/gl2.h>
#include <vector>
#include "program_file.h"

class Mesh{
public:
    GLuint vbo;
    GLsizei count; //indices to be rendered
    
    Mesh(const std::vector<float>& data);
};

class ButtonMesh{
public:
    GLuint vbo;
    GLsizei count; //indices to be rendered
    
    ButtonMesh();
    
    ButtonMesh(const std::vector<float>& data);
};



#endif //MESH_FILE_H