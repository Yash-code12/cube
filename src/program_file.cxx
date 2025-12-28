#include "program_file.h"
#include "shader_compiler.h"
#include "image_loader.h"
#include "world_matrices.h"
#include <iostream>

using namespace std;

//program without texture
ProgramClass::ProgramClass(const std::string &vertShaderPath, const std::string &fragShaderPath, 
    const std::string &posLocName, const std::string &uvLocName) {
        //make program
    program = makeProgram(vertShaderPath, fragShaderPath);
    if(program == -1){
        std::cerr << "Error in making program, line: " << __LINE__ << "\n";
    }
    
    glUseProgram(program);
    
    //Fetch attribute indices
    posLoc = glGetAttribLocation(program, posLocName.c_str());
    uvLoc = glGetAttribLocation(program, uvLocName.c_str());
    if(posLoc == -1){
        std::cerr << "Error in fetching pos loc, line: " << __LINE__ << "\n";
    }
    if(uvLoc == -1){
        std::cerr << "Error in fetching uv loc, line: " << __LINE__ << "\n";
    }
}

//program with texture
ProgramClass::ProgramClass(const std::string &vertShaderPath, const std::string &fragShaderPath, 
    const std::string &posLocName, const std::string &uvLocName,
    const std::string &texturePath, const std::string &textureLocName, int unit) : 
textureLocName(textureLocName), unit(unit) {
    //make program
    program = makeProgram(vertShaderPath, fragShaderPath);
    if(program == -1){
        std::cerr << "Error in making program, line: " << __LINE__ << "\n";
    }
    
    glUseProgram(program);
    
    //Fetch attribute indices
    posLoc = glGetAttribLocation(program, posLocName.c_str());
    uvLoc = glGetAttribLocation(program, uvLocName.c_str());
    if(posLoc == -1){
        std::cerr << "Error in fetching pos loc, line: " << __LINE__ << "\n";
    }
    if(uvLoc == -1){
        std::cerr << "Error in fetching uv loc, line: " << __LINE__ << "\n";
    }
    
    //load file and bind to the unit
    textureID = loadTexture(texturePath.c_str());
    if(textureID == -1){
        std::cerr << "Error in loading texture, line: " << __LINE__ << "\n";
    }
    
    //Activate texture unit
    glActiveTexture(GL_TEXTURE0 + unit);
    
    //get sampler location
    textureLocation = glGetUniformLocation(program, textureLocName.c_str());
    if(textureLocation == -1){
        std::cerr << "Error in loading texture, line: " << __LINE__ << "\n";
    }
    
    //tell shader "This sampler uses unit X""
    glUniform1i(textureLocation, unit);
}
//only call this for worldProgram
void renderWorld(ProgramClass &program, Camera &cam, GLuint viewLoc){
    //only draw pixel closest to camera
    glEnable(GL_DEPTH_TEST);
    
    // Enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glUseProgram(program.program);
    setViewMatrix(program.program, viewLoc, cam.x, cam.y, cam.z, cam.yaw, cam.pitch);
    
    glActiveTexture(GL_TEXTURE0 + program.unit);
    glBindTexture(GL_TEXTURE_2D, program.textureID);
            
    glUniform1i(program.textureLocation, program.unit);
}

void renderUI(ProgramClass &program){
    glDisable(GL_DEPTH_TEST);
    glUseProgram(program.program);
    
    glActiveTexture(GL_TEXTURE0 + program.unit);
    glBindTexture(GL_TEXTURE_2D, program.textureID);
            
    glUniform1i(program.textureLocation, program.unit);
}