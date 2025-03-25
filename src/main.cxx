#include <GLES2/gl2.h>
#include <iostream>
#include <vector>
#include <array>

#include "window_initializer.h"
#include "shader_compiler.h"
#include "buffer_setter.h"
#include "projection_matrix.h"
#include "quad.h"

using namespace std;
/*
vector<GLfloat> v1 = {
    // Positions, Texture Coordinates
    -1.0f,  1.0f,  5.0f,  0.0f, 1.0f,  // Top-left
    -1.0f, -1.0f,  5.0f,  0.0f, 0.0f,  // Bottom-left
     1.0f, -1.0f, 5.0f,  1.0f, 0.0f  // Bottom-right
};

vector<GLfloat> v2 = {
    // Positions, Texture Coordinates
    -1.0f,  1.0f, 5.0f,  0.0f, 1.0f,  // Top-left
    1.0f, 1.0f,  5.0f,  0.0f, 0.0f,  // Top-right
     1.0f, -1.0f,  5.0f,  1.0f, 0.0f  // Bottom-right
};
*/
/*
vector<GLfloat> v = {
    -1.0f, -1.0f, 5.0f,
    1.0f, -1.0f, 5.0f,
    1.0f, 1.0f, 5.0f,
    -1.0f, 1.0f, 5.0f
};

vector<GLfloat> v2 = {
    -1.0f, -1.0f, 10.0f,
    1.0f, -1.0f, 10.0f,
    1.0f, 1.0f, 10.0f,
    -1.0f, 1.0f, 10.0f
};
*/
vector<GLfloat> v = {
    -1.0f, -1.0f, 5.0f,
    1.0f, -1.0f, 5.0f,
    1.0f, 1.0f, 5.0f,
    -1.0f, 1.0f, 5.0f,
    -1.0f, -1.0f, 6.0f,
    1.0f, -1.0f, 6.0f,
    1.0f, 1.0f, 6.0f,
    -1.0f, 1.0f, 6.0f
};

vector<GLfloat> vertices;

int main(){
    vertices = makeCube(v);
    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;
    int width, height;
    
    // Initialize SDL2 and create OpenGL ES 2.0 window
    if (initSDL(window, context, width, height) != 0) {
        return -1;
    }
    cout << "Width: " << width << ", " << "Height: " << height << "\n";
    glViewport(0, 0, width, height);  // width and height from SDL window
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); // Standard depth comparison
    
    GLuint program = makeProgram("shaders/vert.glsl", "shaders/frag.glsl");
    if(program == -1){
        cleanup(window, context);
        return -1;
    }
    glUseProgram(program);
    
    GLuint screensizeUniform = glGetUniformLocation(program, "screensize");
    
    GLuint projLoc = glGetUniformLocation(program, "projMtx");
    SetProjectionMatrix(program, projLoc, float(width), float(height));
    
    TriangleVBO(vertices, program);
    
    float bgColor[4] = {0.0f,0.0f,0.0f,1.0f};
    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        
        glUseProgram(program);
        
        glUniform2f(screensizeUniform, (float)width, (float)height);
        
        glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //last arg is total vertices (count)
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/5);
        
        SDL_GL_SwapWindow(window);
    }

    // Clean up resources
    cleanup(window, context);
    
    return 0;
}