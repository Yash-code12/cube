#include "cube_generator.h"
#include <iostream>
#include <vector>
#include <GLES2/gl2.h>
using namespace std;

/*
CCW winding order

bottom left is start for all faces
look from normal direction to get correct indices

cube indices(viewed from outside):-
front:-    back:-
3 2          6 7
0 1          5 4

front face:-
3 2
0 1

tris: (0,1,2), (0,2,3)

back face:-
6 7
5 4
flipped beacuse it faces opposite direction

tris: (5,4,7), (5,7,6)
*/

//make 2 tri (face) from 4 vertices (quad)
//tri: [x,y,z,u,v]
//start is bottom left
//c-clockwise

/*
faceValues format:-
x1, y1, z1,
...
x4, y4, z4
*/
vector<GLfloat> makeQuad(vector<GLfloat>& faceValues){
    vector<GLfloat> face;
    
    //indices of 2 triangles for face
    vector<vector<int>> indices = {
        {0,1,2},
        {0,2,3}
    };
    //texture coords for the triangles
    vector<vector<vector<GLfloat>>> texCoords = {
        {{0.0f,0.0f},{1.0f,0.0f},{1.0f,1.0f}},
        {{0.0f,0.0f},{1.0f,1.0f},{0.0f,1.0f}}
    };
    
    vector<GLfloat> tri1;
    vector<GLfloat> tri2;
    
    //for every indice
    for(int i = 0; i < 3; ++i){
        
        //indices[a][i]*3 moves to the vertex's x val and k is used to get the y and z as well and a represents the indice set used
        for(int k = 0; k < 3; ++k){
            tri1.push_back(faceValues[indices[0][i]*3 + k]);
            tri2.push_back(faceValues[indices[1][i]*3 + k]);
        }
        
        //for every set of texCoords
        for(int j = 0; j < 2; ++j){
            tri1.push_back(texCoords[0][i][j]);
            tri2.push_back(texCoords[1][i][j]);
        }
    }
    
    for(auto i : tri1) face.push_back(i);
    for(auto i : tri2) face.push_back(i);
    
    return face;
}

//make faces with 4 vertices and pass them to make 2 triangles

/*
vertices format:-
x1, y1, z1,
x2, y2, z2,
...
x8, y8, z8
*/

/*
tri: [x,y,z,u,v]
total triangles = 6*2 = 12
output:
x1,y1,z1,u1,v1
...
x12,y12,z12,u12,v12
total GLfloats = 5*6*2 = 60
*/

vector<GLfloat> makeCube(vector<GLfloat> vertices){
    vector<GLfloat> cube;
    
    vector<vector<int>> indices = {
        {0,1,2,3}, //front
        {5,4,7,6}, //back
        {3,2,6,7}, //top
        {4,5,1,0}, //bottom
        {4,0,3,7}, //left
        {1,5,6,2} //right
    };
    //for every set of indices
    for(int i = 0; i < indices.size(); ++i){
        
        //add 4 vertices to make face and pass to makeQuad func
        vector<GLfloat> face;
        
        //for every indice
        for(int j = 0; j < indices[i].size(); ++j){
            
            //add the x, y, z of that vertex
            for(int k = 0; k < 3; ++k){
                
                //indices[i][j]*3 moves to the vertex's x val and k is used to get the y and z as well
                int vertex = indices[i][j]*3;
                face.push_back(vertices[vertex + k]);
            }
        }
        //append the result to cube
        face = makeQuad(face);
        for(auto i : face) cube.push_back(i);
    }
    return cube;
}

/*
make 8 vertices of cube using 1 position
position: [x, y, z], x,y,z are int
vertex: [x, y, z]
output:
x1,y1,z1
...
x8,y8,z8

x1, y1, z1 are the input position

to move in x, y dir add and subtract for z
*/

vector<GLfloat> makeVertices(float x, float y, float z){
    vector<GLfloat> vertices = {
        x,     y,      z,
        x+1, y,      z,
        x+1, y+1, z,
        x, y+1,      z,
        //repeat with z = z-1
        x,     y,      z-1,
        x+1, y,      z-1,
        x+1, y+1, z-1,
        x, y+1,      z-1
    };
    return vertices;
}