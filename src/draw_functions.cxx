#include "draw_functions.h"
#include "matrix_math.h"
#include <iostream>

void drawMesh(const ProgramClass &program, const Mesh &mesh){
    glUseProgram(program.program);
    
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    
    constexpr int STRIDE = 5 * sizeof(float);
    
    //enable attribute
    glEnableVertexAttribArray(program.posLoc);
    glVertexAttribPointer(
    program.posLoc, //index in shader
    3, //components per vertex (x y z)
    GL_FLOAT, //data type
    GL_FALSE, //normalize or not (No)
    STRIDE, //byte offset per vertex
    (void*)0); //pointer to first component
    
    glEnableVertexAttribArray(program.uvLoc);
    glVertexAttribPointer(program.uvLoc, 2, GL_FLOAT, GL_FALSE, STRIDE, (void*)(3*sizeof(float)));
    
    glDrawArrays(GL_TRIANGLES, 0, mesh.count);
}

void drawButton(const ProgramClass &program, const Button &button){
    glUseProgram(program.program);
    
    glBindBuffer(GL_ARRAY_BUFFER, button.mesh.vbo);
    
    float angle = 0.0f;
    if(button.use == MOVE_FORWARD || button.use == MOVE_UP){
        angle = 0.0f;
    } else if(button.use == MOVE_BACK || button.use == MOVE_DOWN){
        angle = 180.0f;
    } else if(button.use == MOVE_LEFT){
        angle = -90.0f;
    } else if(button.use == MOVE_RIGHT){
        angle = 90.0f;
    }
    
    Matrix4f model;
    //move square so that its center is 0,0
    model = translate(model, -0.5f, -0.5f, 0);
    //then rotate around 0,0
    model = rotate2D(model, angle);
    //move square to original position
    model = translate(model, 0.5f, 0.5f, 0);
    
    //then scale
    model = scale(model, button.width, button.height, 0);
    //finally translate
    model = translate(model, button.x, button.y, 0);
    
    
    GLint modelLoc = glGetUniformLocation(program.program, "u_model");
    if(modelLoc == -1){
        std::cerr << "Error in fetching model loc, line: " << __LINE__ << "\n";
    }
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.m);
    /*
    model.printSelf();
    std::cout << "\n";
    */
    constexpr int STRIDE = 4 * sizeof(float);
    
    glEnableVertexAttribArray(program.posLoc);
    glVertexAttribPointer(program.posLoc, 2, GL_FLOAT, GL_FALSE, STRIDE, (void *)0);
    
    glEnableVertexAttribArray(program.uvLoc);
    glVertexAttribPointer(program.uvLoc, 2, GL_FLOAT, GL_FALSE, STRIDE, (void *)(2*sizeof(float)));
    
    glDrawArrays(GL_TRIANGLES, 0, button.mesh.count);
}