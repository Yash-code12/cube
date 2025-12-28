#include "user_input.h"
#include <iostream>
#include <vector>

void UserInput::checkButtons(int screen_width, int screen_height, std::vector<Button> buttonsList, Camera &cam){
    if(!fingerDown) return;
    
    for(Button button : buttonsList){
       if(button.checkActivation(currentX*screen_width, currentY*screen_height)){
           //std::cout << "Button pressed: " << button.use << " button\n";
           if(button.use == UP){
               cam.z -= cam.walkSpeed;
           } else if(button.use == DOWN){
               cam.z += cam.walkSpeed;
           } else if(button.use == LEFT){
               cam.x -= cam.walkSpeed;
           } else if(button.use == RIGHT){
               cam.x += cam.walkSpeed;
           }
       }
    }
}

void screenPressed(float x, float y, int screen_width, int screen_height, std::vector<Button> buttonsList){
    for(int i = 0; i < buttonsList.size(); i++){
       Button button = buttonsList[i];
       if(button.checkActivation(x*screen_width, y*screen_height)){
           std::cout << "Button pressed: " << button.use << " button\n";
       }
    }
    return;
}