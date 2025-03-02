#include "window_initializer.h"
#include <iostream>

void getUsableBound(int& WIDTH, int& HEIGHT){
    SDL_Rect usableBounds;
    if (SDL_GetDisplayUsableBounds(0, &usableBounds) == 0) {
        WIDTH = usableBounds.w;
        HEIGHT = usableBounds.h;
    } else {
        std::cerr << "Could not get usable bounds! SDL_Error: " << SDL_GetError() << std::endl;
        WIDTH = 800;  // Default width
        HEIGHT = 600; // Default height
    }
}

// Function to initialize SDL2 and create an OpenGL ES 2.0 window
int initSDL(SDL_Window*& window, SDL_GLContext& context, int& width, int& height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Set OpenGL ES 2.0 context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    getUsableBound(width, height);

    // Create SDL window with OpenGL context
    window = SDL_CreateWindow("OpenGL ES 2.0 with SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create OpenGL context
    context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    return 0;
}

// Function to clean up SDL2 resources
void cleanup(SDL_Window* window, SDL_GLContext context) {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}