#include "buttons.h"
#include <iostream>

//inputs in pixels
Button::Button(int screen_width, int screen_height, float x_i, float y_i, float width_i, float height_i, BtnValue use) : use(use){
    /*
    x = (x_i/screen_width)*2 - 1;
    y = 1 - (y_i/screen_height)*2;
    width = (width_i/screen_width);
    height = (height_i/screen_height);
    */
    x = x_i;
    y = y_i;
    width = width_i;
    height = height_i;
    //y gets flipped in shader so y = 1-y so y = 1.0f moves coord lower +y -> lower
    data = {
        //CCW, BL, BR, TR
        0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        
        //BL, TR, TL
        0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    mesh =  ButtonMesh(data);
    
    /*
    data = {
        //CCW, BL, BR, TR
        x,               y + height, 0.0f, 0.0f,
        x + width, y + height, 1.0f, 0.0f,
        x + width, y,                 1.0f, 1.0f,
        
        //BL, TR, TL
        x,               y + height, 0.0f, 0.0f,
        x + width, y,                 1.0f, 1.0f,
        x,               y,                 0.0f, 1.0f
    };
    */
    /*
    data = {
        100, 400, 0, 0,
        400, 400, 1, 0,
        400, 100, 1, 1,
        
        100, 400, 0, 0,
        400, 100, 1, 1,
        100, 100, 0, 1,
    };*/
    //for(auto i : data) std::cout << i << " ";
}

//args will be passed in pixels and y should be flipped if needed (Not for sdl2)
bool Button::checkActivation(int pressedX, int pressedY){
    int leftEdge = x;
    int rightEdge = x + width;
    int upEdge = y;
    int downEdge = y + height;
    
    if(pressedX > leftEdge && 
    pressedX < rightEdge && 
    pressedY > upEdge && 
    pressedY < downEdge){
        return true;
    }
    return false;
}