#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include <GLES2/gl2.h>
#include <iostream>

#include "window_initializer.h"
#include "shader_compiler.h"

using namespace std;

int main(){
    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;
    int width, height;
    
    // Initialize SDL2 and create OpenGL ES 2.0 window
    if (initSDL(window, context, width, height) != 0) {
        return -1;
    }
    std::cout << "Width: " << width << ", " << "Height: " << height << "\n";
    glViewport(0, 0, width, height);  // width and height from SDL window
    
    float bgColor[4] = {0.0f,0.0f,0.0f,1.0f};
    
    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);
        
        SDL_GL_SwapWindow(window);
    }

    // Clean up resources
    cleanup(window, context);
    
    return 0;
}
>>>>>>> 22689a4 (Added glm library (unused for now). updated src and include, Working window)
