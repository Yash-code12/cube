#ifndef PROGRAM_FILE_H
#define PROGRAM_FILE_H

#include <GLES2/gl2.h>
#include <string>
#include "camera.h"

class ProgramClass{
public:
    GLuint program, textureID;
    std::string textureLocName;
    //location of sampler(2D texture) in vertShader
    GLint textureLocation;
    int unit; //the unit sampler texture uses
    GLint posLoc, uvLoc;
    
    ProgramClass(const std::string &vertShaderPath, const std::string &fragShaderPath, 
    const std::string &posLocName, const std::string &uvLocName);
    
    ProgramClass(const std::string &vertShaderPath, const std::string &fragShaderPath, 
    const std::string &posLocName, const std::string &uvLocName,
    const std::string &texturePath, const std::string &textureLocName, int unit);
};

void renderWorld(ProgramClass &program, Camera &cam, GLuint viewLoc);void renderUI(ProgramClass &program);

#endif //PROGRAM_FILE_H