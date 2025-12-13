#include <GLES2/gl2.h>
#include <iostream>
#include <vector>
#include <array>
#include <chrono>

#include "window_initializer.h"
#include "shader_compiler.h"
#include "buffer_setter.h"
#include "matrices.h"
#include "quad.h"
#include "image_loader.h"

using namespace std;

vector<GLfloat> v = {
    -0.5f, -0.5f, -5.0f,
    0.5f, -0.5f, -5.0f,
    0.5f, 0.5f, -5.0f,
    -0.5f, 0.5f, -5.0f,
    -0.5f, -0.5f, -6.0f,
    0.5f, -0.5f, -6.0f,
    0.5f, 0.5f, -6.0f,
    -0.5f, 0.5f, -6.0f
};
//test triangle
vector<GLfloat> test = {
    -1, -1, -10, 0, 0,
     1, -1, -10, 1, 0,
     0,  1, -10, 0.5, 1
};

vector<GLfloat> cube;

//add a way to move camera and rotate it with inputs

int main(){
    cube = makeCube(v);
    
    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;
    int width, height;
    
    // Initialize SDL2 and create OpenGL ES 2.0 window
    if (initSDL(window, context, width, height) != 0) {
        return -1;
    }
    cout << "Width: " << width << ", " << "Height: " << height << "\n";
    glViewport(0, 0, width, height);  // width and height from SDL window
    
    //only draw pixel closest to camera
    glEnable(GL_DEPTH_TEST);
    //pass the depth test if new fragment is closer
    glDepthFunc(GL_LESS);
    //dont render triangles facing away from camera
    glEnable(GL_CULL_FACE);
    //triangles vertices using counter-clockwise order is considered the front
    glFrontFace(GL_CCW);
    //discard back faces, draw front faces
    glCullFace(GL_BACK);
    
    GLuint program = makeProgram("shaders/vert.glsl", "shaders/frag.glsl");
    if(program == -1){
        cleanup(window, context);
        return -1;
    }
    glUseProgram(program);
    
    GLuint screensizeUniform = glGetUniformLocation(program, "screensize");
    
    GLuint timeUniform = glGetUniformLocation(program, "u_time");
    
    GLuint textureID = loadTexture("assets/square.png");
    
    GLint texCoordLocation = glGetAttribLocation(program, "a_textureCoord");
    GLint samplerLocation = glGetUniformLocation(program, "u_textureSampler");
    
    GLuint projLoc = glGetUniformLocation(program, "projMtx");    GLuint viewLoc = glGetUniformLocation(program, "viewMtx");
    GLuint rotLoc = glGetUniformLocation(program, "rotMtx");
    
    setProjectionMatrix(program, projLoc, float(width), float(height));
    
    vector<float> camPos = {0.0f, 0.0f, 0.0f};
    vector<float> camRot = {0.0f, 0.0f, 0.0f};
    
    setViewMatrix(program, viewLoc, camPos[0], camPos[1], camPos[2]);
    setRotMatrix(program, rotLoc, camRot[0], camRot[1], camRot[2]);
    
    TriangleVBO(cube, program);
    
    float bgColor[4] = {0.0f,0.0f,0.0f,1.0f};
    SDL_Event event;
    bool running = true;
    
    int dir = -1;
    auto start_time = chrono::high_resolution_clock::now();
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        
        glUseProgram(program);
        
        glUniform2f(screensizeUniform, (float)width, (float)height);
        
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = (std::chrono::duration<float>(end_time - start_time).count());
        start_time = end_time;
        duration *= 5;
        cout << duration << "\n";
        glUniform1f(timeUniform, duration);
        
        //rotate camera with time
        camRot[0] += dir*(duration/5);
        float cap = 2.0f;
        if(camRot[0] > cap || camRot[0] < -cap){
            dir *= -1;
        }
        setViewMatrix(program, viewLoc, camPos[0], camPos[1], camPos[2]);
        setRotMatrix(program, rotLoc, camRot[0], camRot[1], camRot[2]);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        glUniform1i(samplerLocation, 0);
        
        glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //last arg is total vertices (count)
        glDrawArrays(GL_TRIANGLES, 0, cube.size()/5);
        
        SDL_GL_SwapWindow(window);
    }

    // Clean up resources
    cleanup(window, context);
    
    return 0;
}