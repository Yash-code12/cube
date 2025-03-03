#include "buffer_setter.h"

void TriangleVBO(std::vector<GLfloat> vertices, GLuint program){
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    glUseProgram(program);
    
    GLuint posAttrib = glGetAttribLocation(program, "position");
    GLuint texAttrib = glGetAttribLocation(program, "texCoord");
    
    glEnableVertexAttribArray(posAttrib);
    glEnableVertexAttribArray(texAttrib);
    
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}