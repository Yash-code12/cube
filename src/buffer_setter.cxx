#include "buffer_setter.h"

void TriangleVBO(std::vector<GLfloat> vertices, GLuint program){
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    glUseProgram(program);
    
    GLuint posAttrib = glGetAttribLocation(program, "position");
    GLuint texAttrib = glGetAttribLocation(program, "a_textureCoord");
    
    constexpr int STRIDE = 5 * sizeof(float);
    
    if(posAttrib != -1){
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, STRIDE, (void*)0);
    }
    
    if(texAttrib != -1){
        glEnableVertexAttribArray(texAttrib);
        glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, STRIDE, (void*)(3*sizeof(float)));
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}