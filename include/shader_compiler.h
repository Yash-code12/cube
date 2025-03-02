#ifndef SHADER_COMPILER_H
#define SHADER_COMPILER_H

#include <iostream>
#include <GLES2/gl2.h>

GLuint compileShader(GLenum shaderType, const std::string& shaderCode);

GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader);

GLuint makeProgram(std::string vertPath, std::string fragPath);

void makeQuad(const std::vector<GLfloat>& quadVertices, GLuint program);

#endif // SHADER_COMPILER_H