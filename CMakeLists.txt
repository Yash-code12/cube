cmake_minimum_required(VERSION 3.10)
project(Cube)

# Find SDL2
find_package(SDL2 REQUIRED)

# Add include directories
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(include)
#include_directories(shaders)
include_directories(glm-master)
>>>>>>> 22689a4 (Added glm library (unused for now). updated src and include, Working window)

# Create executable
add_executable(run 
src/main.cxx 
<<<<<<< HEAD
=======
src/window_initializer.cxx 
src/shader_compiler.cxx 
>>>>>>> 22689a4 (Added glm library (unused for now). updated src and include, Working window)
)

# Link libraries
target_link_libraries(run 
    ${SDL2_LIBRARIES}
<<<<<<< HEAD
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
=======
>>>>>>> 22689a4 (Added glm library (unused for now). updated src and include, Working window)
)

#For android only
if(ANDROID)
    target_link_libraries(run GLESv2)
endif()
