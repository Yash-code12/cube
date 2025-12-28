#include <GLES2/gl2.h>
#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include <string>

#include "window_initializer.h"
#include "world_matrices.h"
#include "camera.h"
#include "cube_generator.h"
#include "chunk_generator.h"
#include "buttons.h"
#include "user_input.h"
#include "program_file.h"
#include "draw_functions.h"

//to do, add functionality for camera rotation by user input

using namespace std;
/*
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
*/
vector<GLfloat> floatData;

void setGLConfiguration(int width, int height);

void setupScene(GLuint &program, GLuint &projLoc, GLuint &viewLoc, int width, int height, Camera &cam);

void processInput(bool &running, GLuint program, GLuint projLoc, int &screen_width, int &screen_height, std::vector<Button> buttonsList, UserInput &ui_input);

int main()
{
    floatData = makeChunk(-5.0f, -2.0f, 5.0f, 10, 1, 10);
    //for(auto i : floatData) cout << i << ", ";

    SDL_Window *window = nullptr;
    SDL_GLContext context = nullptr;
    int width, height;

    // Initialize SDL2 and create OpenGL ES 2.0 window
    if (initSDL(window, context, width, height) != 0)
    {
        return -1;
    }
    cout << "Width: " << width << ", "
         << "Height: " << height << "\n";

    int buttonSize = 200;

    Button upBtn(width, height, 300, height - 3 * buttonSize, buttonSize, buttonSize, UP);

    Button downBtn(width, height, upBtn.x, upBtn.y + 1.5 * buttonSize, buttonSize, buttonSize, DOWN);

    Button leftBtn(width, height, upBtn.x - buttonSize, upBtn.y + 0.75 * buttonSize, buttonSize, buttonSize, LEFT);

    Button rightBtn(width, height, upBtn.x + buttonSize, upBtn.y + 0.75 * buttonSize, buttonSize, buttonSize, RIGHT);

    vector<Button> buttonsList = {
        upBtn, downBtn, leftBtn, rightBtn};

    setGLConfiguration(width, height);

    string vertShaderPath = "shaders/vert.glsl";
    string fragShaderPath = "shaders/frag.glsl";
    string texturePath = "assets/square.png";
    string textureLocName = "u_textureSampler";
    int worldUnit = 0;
    string posLocName = "a_position";
    string uvLocName = "a_textureCoord";

    string ui_vertShaderPath = "shaders/ui_vert.glsl";
    string ui_fragShaderPath = "shaders/ui_frag.glsl";
    string ui_texturePath = "assets/up_arrow.png";
    string ui_textureLocName = "u_ui_textureSampler";
    int uiUnit = 1;
    string ui_posLocName = "a_ui_position";
    string ui_uvLocName = "a_ui_textureCoord";
    string screensizeLocName = "screensize";

    ProgramClass worldProgram(vertShaderPath, fragShaderPath, posLocName, uvLocName, texturePath, textureLocName, worldUnit);

    Mesh chunkMesh(floatData);

    ProgramClass uiProgram(ui_vertShaderPath, ui_fragShaderPath, ui_posLocName, ui_uvLocName, ui_texturePath, ui_textureLocName, uiUnit);

    glUseProgram(uiProgram.program);

    GLuint screensizeLoc = glGetUniformLocation(uiProgram.program, screensizeLocName.c_str());
    if (screensizeLoc == -1)
    {
        std::cerr << "Error in fetching screensize loc, line: " << __LINE__ << "\n";
    }

    glUniform2f(screensizeLoc, (float)width, (float)height);

    if (worldProgram.program == -1)
    {
        cleanup(window, context);
        return 1;
    }
    GLuint projLoc, viewLoc;
    Camera cam;
    setupScene(worldProgram.program, projLoc, viewLoc, width, height, cam);

    float bgColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    bool running = true;
    UserInput ui_input;

    auto start_time = chrono::high_resolution_clock::now();
    while (running)
    {
        processInput(running, worldProgram.program, projLoc, width, height, buttonsList, ui_input);

        auto end_time = chrono::high_resolution_clock::now();
        auto duration = (std::chrono::duration<float>(end_time - start_time).count());
        start_time = end_time;
        duration *= 5;
        //cout << duration << "\n";

        glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderWorld(worldProgram, cam, viewLoc);

        drawMesh(worldProgram, chunkMesh);

        renderUI(uiProgram);

        for (Button button : buttonsList)
        {
            drawButton(uiProgram, button);
        }

        //upBtn.renderSelf(renderer);
        SDL_GL_SwapWindow(window);
        
        ui_input.checkButtons(width, height, buttonsList, cam);
    }
    //make better cleanup function if needed
    // Clean up resources
    cleanup(window, context);

    return 0;
}

void setGLConfiguration(int width, int height)
{
    glViewport(0, 0, width, height); // width and height from SDL window
    //pass the depth test if new fragment is closer
    glDepthFunc(GL_LESS);
    //dont render triangles facing away from camera
    glEnable(GL_CULL_FACE);
    //triangles vertices using counter-clockwise order is considered the front
    glFrontFace(GL_CCW);
    //discard back faces, draw front faces
    glCullFace(GL_BACK);
}

void setupScene(GLuint &program, GLuint &projLoc, GLuint &viewLoc, int width, int height, Camera &cam)
{
    projLoc = glGetUniformLocation(program, "projMtx");
    viewLoc = glGetUniformLocation(program, "viewMtx");

    setProjectionMatrix(program, projLoc, float(width), float(height));

    setViewMatrix(program, viewLoc, cam.x, cam.y, cam.z, cam.yaw, cam.pitch);
}

void processInput(bool &running, GLuint program, GLuint projLoc, int &screen_width, int &screen_height, std::vector<Button> buttonsList, UserInput &ui_input)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        float x, y;
        switch (event.type)
        {
        //top = 0.0 -> bottom = 1.0
        case SDL_FINGERDOWN:
            x = event.tfinger.x;
            y = event.tfinger.y;
            ui_input = UserInput(x, y, true);
            break;
        case SDL_FINGERUP:
            x = event.tfinger.x;
            y = event.tfinger.y;
            ui_input = UserInput(x, y, false);
            break;
        case SDL_FINGERMOTION:
            x = event.tfinger.x;
            y = event.tfinger.y;
            ui_input.currentX = x;
            ui_input.currentY = y;
            /*
            float dx = event.tfinger.dx;
            float dy = event.tfinger.dy;
                
            cam.yaw -= dx * sensitivity;
            cam.pitch += dy * sensitivity;*/
            break;
        }
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
        if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                int w = event.window.data1;
                int h = event.window.data2;
                screen_width = w;
                screen_height = h;
                glViewport(0, 0, screen_width, screen_height);
                setProjectionMatrix(program, projLoc, float(screen_width), float(screen_height));
            }
        }
    }
}