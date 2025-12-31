#include "user_input.h"
#include <iostream>
#include <vector>

bool UserInput::checkButtons(int screen_width, int screen_height, std::vector<Button> buttonsList, Camera &cam){
    if(!fingerDown) return false;
    
    for(Button button : buttonsList){
       if(button.checkActivation(currentX*screen_width, currentY*screen_height)){
           //std::cout << "Button pressed: " << button.use << " button\n";
           
           if(button.use == MOVE_FORWARD){
               cam.move(FORWARD);
           } else if(button.use == MOVE_BACK){
               cam.move(BACK);
           } else if(button.use == MOVE_LEFT){
               cam.move(LEFT);
           } else if(button.use == MOVE_RIGHT){
               cam.move(RIGHT);
           } else if(button.use == MOVE_UP){
               cam.move(UP);
           } else if(button.use == MOVE_DOWN){
               cam.move(DOWN);
           }
           return true; //button pressed
       }
    }
    return false;
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