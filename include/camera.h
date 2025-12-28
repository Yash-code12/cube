#ifndef CAMERA_H
#define CAMERA_H

class Camera{
public:
    float x, y, z;
    float yaw, pitch;
    float sensitivity;
    float walkSpeed;
    
    Camera(){
        x = 0.0f; y = 0.0f; z = 0.0f; yaw = 0.0f; pitch = 0.0f; sensitivity = 5.0f; walkSpeed = 0.1f;
    };
    
    Camera(float x, float y, float z, float yaw = 0.0f, float pitch = 0.0f, float sensitivity = 5.0f, float walkSpeed = 0.1f) : x(x), y(y), z(z), yaw(yaw), pitch(pitch), sensitivity(sensitivity), walkSpeed(walkSpeed) {};
};

#endif //CAMERA_H