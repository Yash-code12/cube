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

void createMovementButtons( std::vector<Button> &buttonsList, int screen_width, int screen_height, int x, int y, int buttonSize);

void setGLConfiguration(int width, int height);

void setupScene(GLuint &program, GLuint &projLoc, GLuint &viewLoc, int width, int height, Camera &cam);

void processInput(
bool &running, 
ProgramClass worldProgram, 
ProgramClass uiProgram,
GLuint projLoc, GLuint screensizeLoc, 
int &screen_width, int &screen_height, 
Camera &cam, std::vector<Button> &buttonsList, 
std::vector<UserInput> &fingers);

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
    int upButtonX = 300;
    int upButtonY = height - 3 * buttonSize;
    
    vector<Button> buttonsList; //= {
        //upBtn, downBtn, leftBtn, rightBtn};
        
    createMovementButtons(buttonsList, width, height, upButtonX, upButtonY, buttonSize);

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
    UserInput finger1;
    vector<UserInput> fingers;
    
    auto start_time = chrono::high_resolution_clock::now();
    while (running)
    {
        processInput(running, 
        worldProgram, uiProgram,
        projLoc, screensizeLoc, 
        width, height, cam, 
        buttonsList, fingers);

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
        
        for(UserInput finger : fingers){
            if(finger.use == clickButtons){
                finger.checkButtons(width, height, buttonsList, cam);
            }
        }
    }
    //make better cleanup function if needed
    // Clean up resources
    cleanup(window, context);

    return 0;
}

void createMovementButtons( std::vector<Button> &buttonsList, int screen_width, int screen_height, int x, int y, int buttonSize){
    Button forwardBtn(
    screen_width, screen_height, 
    x, y, buttonSize, buttonSize, 
    MOVE_FORWARD);

    Button backBtn(
    screen_width, screen_height, 
    forwardBtn.x, forwardBtn.y + 1.5 * 
    buttonSize, buttonSize, buttonSize, 
    MOVE_BACK);

    Button leftBtn(
    screen_width, screen_height, 
    forwardBtn.x - buttonSize, 
    forwardBtn.y + 0.75 * buttonSize, 
    buttonSize, buttonSize, 
    MOVE_LEFT);

    Button rightBtn(
    screen_width, screen_height, 
    forwardBtn.x + buttonSize, 
    forwardBtn.y + 0.75 * buttonSize, 
    buttonSize, buttonSize, 
    MOVE_RIGHT);
    
    Button upBtn(
    screen_width, screen_height, 
    screen_width - buttonSize*1.5f, 
    forwardBtn.y + 0.2f*buttonSize,
    buttonSize, buttonSize, 
    MOVE_UP);
    
    Button downBtn(
    screen_width, screen_height, 
    upBtn.x, 
    upBtn.y + 1.2f*buttonSize,
    buttonSize, buttonSize, 
    MOVE_DOWN);
    
    buttonsList = {
        forwardBtn, backBtn, leftBtn, rightBtn,
        upBtn, downBtn
    };
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

void processInput(
bool &running, 
ProgramClass worldProgram, 
ProgramClass uiProgram,
GLuint projLoc, GLuint screensizeLoc, 
int &screen_width, int &screen_height, 
Camera &cam, std::vector<Button> &buttonsList, 
std::vector<UserInput> &fingers)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        float x, y;
        SDL_FingerID id;
        switch (event.type)
        {
            //top = 0.0 -> bottom = 1.0
            case SDL_FINGERDOWN:
            {
                x = event.tfinger.x;
                y = event.tfinger.y;
                id = event.tfinger.fingerId;
                
                UserInput finger(id, None, x, y, true);
                
                //if button is clicked
                if(finger.checkButtons(screen_width, screen_height, buttonsList, cam)){
                    //this finger can only be used for clicking buttons
                    finger.use = clickButtons;
                } else {
                    finger.use = rotateCamera;
                }
                
                fingers.push_back(finger);
                break;
            }
            case SDL_FINGERUP:
            {
                x = event.tfinger.x;
                y = event.tfinger.y;
                id = event.tfinger.fingerId;
                
                for(int i = 0; i < fingers.size(); i++){
                    if(fingers[i].id == id){
                        fingers.erase(fingers.begin() + i);
                    }
                }
                break;
            }
            case SDL_FINGERMOTION:
            {
                x = event.tfinger.x;
                y = event.tfinger.y;
                id = event.tfinger.fingerId;
                for(int i = 0; i < fingers.size(); i++){
                    if(fingers[i].id == id){
                        fingers[i].currentX = x;
                        fingers[i].currentY = y;
                    
                        if(fingers[i].use == rotateCamera){
                            float dx = event.tfinger.dx;
                            float dy = event.tfinger.dy;
                        
                            cam.yaw -= dx * cam.sensitivity;
                            cam.pitch += dy * cam.sensitivity;
                        }
                    }
                }
                
                break;
            }
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
                
                glUseProgram(worldProgram.program);
                setProjectionMatrix(worldProgram.program, projLoc, (float)screen_width, (float)screen_height);
                
                glUseProgram(uiProgram.program);
                glUniform2f(screensizeLoc, (float)screen_width, (float)screen_height);
                
                float buttonSize, upButtonX, upButtonY;
                //landscape
                if(screen_width > screen_height){
                    buttonSize = screen_height * 0.15f; 
    
                    // Anchor to bottom-left: 10% from left, 40% from bottom
                    upButtonX = screen_width * 0.15f; 
                    upButtonY = screen_height * 0.60f;
                } else { //potrait
                    buttonSize = screen_height*0.08f;
                    upButtonX = screen_width * 0.2f;
                    upButtonY = screen_height - 3*buttonSize;
                }
                createMovementButtons( buttonsList, screen_width, screen_height, upButtonX, upButtonY, buttonSize);
            }
        }
    }
}