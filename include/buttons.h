#ifndef BUTTONS_H
#define BUTTONS_H

#include <SDL2/SDL.h>
#include <vector>
#include "mesh_file.h"

enum BtnValue{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

class Button{
public:
    //all are in pixels
    float x, y, width, height;
    BtnValue use; //what the button is used for movement, etc
    std::vector<float> data;
    ButtonMesh mesh;
    
    //values in pixels
    Button(int screen_width, int screen_height, float x_i, float y_i, float width_i, float height_i, BtnValue use);
    
    bool checkActivation(int pressedX, int pressedY);
};

#endif //BUTTONS_H