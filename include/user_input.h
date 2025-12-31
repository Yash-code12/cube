#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "buttons.h"
#include "camera.h"
#include <vector>

enum FingerUse{
    None = 0,
    clickButtons = 1,
    rotateCamera = 2
};

class UserInput{
public:
    uint id;
    FingerUse use;
    float currentX, currentY;
    bool fingerDown;
    
    UserInput(){
        id = -1;
        use = None;
        currentX = -100;
        currentY = -100;
        fingerDown = false;
    }
    
    UserInput(uint id, FingerUse use, float currentX, float currentY, bool fingerDown) : id(id), use(use), currentX(currentX), currentY(currentY), fingerDown(fingerDown) {}
    
    bool checkButtons(int screen_width, int screen_height, std::vector<Button> buttonsList, Camera &cam);
};

void screenPressed(float x, float y, int screen_width, int screen_height, std::vector<Button> buttonsList);

#endif //USER_INPUT_H