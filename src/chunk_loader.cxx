#include "chunk_loader.h"
#include "cube_generator.h"
#include <vector>
#include <GLES2/gl2.h>
using namespace std;

/*
takes start position of first cube and no. of cubes to make in x, y and z direction
start position is same as makeVertices start position

return vector of floats of all the cubes in order

to move in x, y dir add and subtract for z

CubeCount = cubesTowardX*cubesTowardY*cubesTowardZ
no. of floats in a cube = 5*2*6
total floats = CubeCount*60
*/

vector<GLfloat> makeChunk(float x, float y, float z, int cubesTowardX, int cubesTowardY, int cubesTowardZ){
    
    vector<GLfloat> allCubes;
    //reserve space for all the cubes
    allCubes.reserve(cubesTowardX * cubesTowardY * cubesTowardZ * 60);
    
    //finish Y dir for all X, repeat for all Z
    for(int cubesInZ = 0; cubesInZ < cubesTowardZ; ++cubesInZ){
        
        for(int cubesInX = 0; cubesInX < cubesTowardX; ++cubesInX){
            
            for(int cubesInY = 0; cubesInY < cubesTowardY; ++cubesInY){
                vector<GLfloat> vertices = makeVertices(x+cubesInX, y-cubesInY, z-cubesInZ);
                
                //vector<GLfloat> vertices = makeVertices(x, y, z);
                
                vector<GLfloat> cube = makeCube(vertices);
                allCubes.insert(allCubes.end(), cube.begin(), cube.end());
            }
        }
    }
    return allCubes;
}