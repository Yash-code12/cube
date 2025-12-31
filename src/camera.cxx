#include "camera.h"
#include <cmath>
//empty for now
//make move forward, back, etc which move relative to direction of camera not world
void Camera::move(Direction direction){
    //direction to move along xz plane (no change in y)
    float dirX = -sin(yaw);
    float dirZ = -cos(yaw);
    
    if (direction == FORWARD) {
        x += dirX * walkSpeed;
        z += dirZ * walkSpeed;
    }
    if (direction == BACK) {
        x -= dirX * walkSpeed;
        z -= dirZ * walkSpeed;
    }
    
    //direction components of right vector
    float rightX = cos(yaw);
    float rightZ = -sin(yaw);
    
    if (direction == LEFT) {
        x -= rightX * walkSpeed;
        z -= rightZ * walkSpeed;
    }
    if (direction == RIGHT) {
        x += rightX * walkSpeed;
        z += rightZ * walkSpeed;
    }
    
    if(direction == UP){
        y += walkSpeed;
    }
    if(direction == DOWN){
        y -= walkSpeed;
    }
}