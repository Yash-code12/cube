cmake_minimum_required(VERSION 3.10)
project(Cube)

# Find SDL2
find_package(SDL2 REQUIRED)

# Add include directories
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(include)
include_directories(shaders)

# Create executable
add_executable(run 
src/main.cxx 
src/window_initializer.cxx 
src/shader_compiler.cxx 
src/world_matrices.cxx 
src/cube_generator.cxx 
src/image_loader.cxx 
src/chunk_generator.cxx 
src/camera.cxx 
src/matrix_math.cxx 
src/buttons.cxx 
src/user_input.cxx
src/program_file.cxx
src/mesh_file.cxx 
src/draw_functions.cxx
src/block.cxx
src/chunk.cxx
)

# Link libraries
target_link_libraries(run 
    ${SDL2_LIBRARIES}
)

#For android only
if(ANDROID)
    target_link_libraries(run GLESv2)
endif()