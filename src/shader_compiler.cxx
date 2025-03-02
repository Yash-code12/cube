#include "shader_compiler.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

std::string readShaderFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open shader file " << filePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint compileShader(GLenum shaderType, const std::string& shaderCode) {
    GLuint shader = glCreateShader(shaderType);
    const char* code = shaderCode.c_str();
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    // Check if compilation was successful
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> infoLog(logLength);
        glGetShaderInfoLog(shader, logLength, nullptr, infoLog.data());
        std::cerr << "Error compiling shader:\n" << infoLog.data() << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check if linking was successful
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> infoLog(logLength);
        glGetProgramInfoLog(program, logLength, nullptr, infoLog.data());
        std::cerr << "Error linking program:\n" << infoLog.data() << std::endl;
        glDeleteProgram(program);
        return 0;
    }

    return program;
}

GLuint makeProgram(std::string vertPath, std::string fragPath){
    // Read shader files
    std::string vertexShaderCode = readShaderFile(vertPath);
    std::string fragmentShaderCode = readShaderFile(fragPath);

    if (vertexShaderCode.empty() || fragmentShaderCode.empty()) {
        std::cerr << "Failed to load shader files!" << std::endl;
        return -1;
    }

    // Compile shaders
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderCode);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    if (vertexShader == 0 || fragmentShader == 0) {
        return -1;
    }

    // Link shaders into a program
    GLuint shaderProgram = linkProgram(vertexShader, fragmentShader);
    if (shaderProgram == 0) {
        return -1;
    }
    
    return shaderProgram;
}

void makeQuad(const std::vector<GLfloat>& quadVertices, GLuint program) {
    GLuint quadVBO;
    glGenBuffers(1, &quadVBO);  
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, quadVertices.size() * sizeof(GLfloat), quadVertices.data(), GL_STATIC_DRAW);

    glUseProgram(program);  // Activate shader program

    // Get attribute locations
    GLint posAttrib = glGetAttribLocation(program, "position");
    //GLint texAttrib = glGetAttribLocation(program, "texCoord");

    // Enable and set up attributes
    glEnableVertexAttribArray(posAttrib);
    //glEnableVertexAttribArray(texAttrib);

    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    //glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
}