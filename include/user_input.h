#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "buttons.h"
#include "camera.h"
#include <vector>

class UserInput{
public:
    float currentX, currentY;
    bool fingerDown;
    
    UserInput(){
        currentX = -100;
        currentY = -100;
        fingerDown = false;
    }
    UserInput(float currentX, float currentY, bool fingerDown) : currentX(currentX), currentY(currentY), fingerDown(fingerDown) {}
    
    void checkButtons(int screen_width, int screen_height, std::vector<Button> buttonsList, Camera &cam);
};

void screenPressed(float x, float y, int screen_width, int screen_height, std::vector<Button> buttonsList);

#endif //USER_INPUT_H