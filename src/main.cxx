#include <GLES2/gl2.h>
#include <iostream>
#include <vector>
#include <array>

#include "window_initializer.h"
#include "shader_compiler.h"
#include "buffer_setter.h"

using namespace std;

vector<GLfloat> triVertices = {
    // Positions, Texture Coordinates
    -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,  // Top-left
    -1.0f, -1.0f,  0.0f,  0.0f, 0.0f,  // Bottom-left
     1.0f, -1.0f,  0.0f,  1.0f, 0.0f  // Bottom-right
};

int main(){
    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;
    int width, height;
    
    // Initialize SDL2 and create OpenGL ES 2.0 window
    if (initSDL(window, context, width, height) != 0) {
        return -1;
    }
    cout << "Width: " << width << ", " << "Height: " << height << "\n";
    //glViewport(0, 0, width, height);  // width and height from SDL window
    
    GLuint program = makeProgram("shaders/vert.glsl", "shaders/frag.glsl");
    if(program == -1){
        cleanup(window, context);
        return -1;
    }
    GLuint screensizeUniform = glGetUniformLocation(program, "screensize");
    
    TriangleVBO(triVertices, program);
    
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
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        SDL_GL_SwapWindow(window);
    }

    // Clean up resources
    cleanup(window, context);
    
    return 0;
}