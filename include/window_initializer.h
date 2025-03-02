#ifndef WINDOW_INITIALIZER_H
#define WINDOW_INITIALIZER_H

#include <SDL2/SDL.h>
#include <GLES2/gl2.h>

int initSDL(SDL_Window*& window, SDL_GLContext& context, int& width, int& height);
void cleanup(SDL_Window* window, SDL_GLContext context);

#endif // WINDOW_INITIALIZER_H