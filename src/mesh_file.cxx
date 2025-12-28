#include "mesh_file.h"
#include "matrix_math.h"
#include <iostream>

ButtonMesh::ButtonMesh(){
    count = 0;
}

Mesh::Mesh(const std::vector<float>& data){
    count = data.size()/5; //3 pos + 2 uv
    
    glGenBuffers(1, &vbo);
    
    //Means "From now on, when I talk about GL_ARRAY_BUFFER, I mean THIS buffer."
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    //upload vbo to gpu memory
    glBufferData(
    GL_ARRAY_BUFFER, //target
    data.size()*sizeof(float), //size in bytes
    data.data(), //pointer to first element
    GL_STATIC_DRAW); //usage pattern
}

ButtonMesh::ButtonMesh(const std::vector<float>& data){
    count = data.size()/4; //2 pos + 2 uv
    
    glGenBuffers(1, &vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(
    GL_ARRAY_BUFFER,
    data.size()*sizeof(float),
    data.data(),
    GL_STATIC_DRAW
    );
}

