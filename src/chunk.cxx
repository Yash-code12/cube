#include "chunk.h"
#include <iostream>

uint16_t Chunk::getBlock(int x, int y, int z) {
    // Check if coordinates are outside the chunk boundaries
    if (x < 0 || x >= 16 || y < 0 || y >= 256 || z < 0 || z >= 16) {
        return 0; // Treat boundaries as air (or check neighbor chunks)
    }
    return (*chunkData)[x + (z * 16) + (y * 256)];
}

/*
faceValues format:-
{x1, y1, z1}, Bottom left (BL)
...                 BR, TR
{x4, y4, z4} Top left (TL)

texCoords fornat:-
{u1, v1} BL
...           BR, TR
{u4, v4} TL

output 2 tris:-

*/
std::array<float, 30> makeQuad(
const std::array<std::array<float, 3>, 4> &faceVertices, 
const std::array<std::array<float,2>, 4> &texCoords){
    
    std::array<float, 30> face;
    
    std::array<std::array<int, 3>, 2> indices = {{
        {0,1,2},
        {0,2,3}
    }};
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            face[i*5 + j] = faceVertices[indices[0][i]][j];
            face[i*5 + j + 15] = faceVertices[ indices[1][i] ][j];
        }
        for(int j = 0; j < 2; j++){
            face[i*5 + j + 3] = texCoords[ indices[0][i] ][j];
            face[i*5 + j + 15 + 3] = texCoords[ indices[1][i] ][j];
        }
    }
    
    return face;
}

//generate the vertex, uv data for the chunk
std::vector<float> Chunk::generateData(){
    int length = sizeof(*chunkData)/sizeof((*chunkData)[0]);
    
    std::vector<float> data;
    //floats for a hollow cuboid max size chunk/2 = (floats per face * (4*faces per vertical sides + 2*faces per horizontal sides))/2 = (4*5 * (4*(16*256) + 2*(16*16)))/2 = 168960
    data.reserve(2000000);
    
    //size of 1 image in texture atlas
    static const float s = 0.0625f;//1/16
    //offset for texture to prevent weird edges (bleeding/overlapping edges)
    static const float ep = 1.0f/256.0f/1.025f;
    
    //for each id(block)
    for(int i = 0; i < length; i++){
        if((*chunkData)[i] == 0){
            continue;
        }
        
        float x = i%16;
        float y = i/256;
        float z = (i/16)%16;
        
        float X = chunkX*16 + x;
        float Z = chunkZ*16 + z;
        
        auto& registry = getBlockRegistry();
        std::array<std::array<float,2>,6> uvCoords = registry[(*chunkData)[i]].uvCoords;
        std::cout << uvCoords[0][0] << "\n";
        //chunk.X,Z point to top top left
        
        //front face
        if(getBlock(x, y, z + 1) == 0){
            float u = uvCoords[0][0];
            float v = uvCoords[0][1];
            
            std::array<float, 30> quad = makeQuad(
            std::array<std::array<float, 3>,4> {{
                {X, y-1, Z+1},
                {X+1, y-1, Z+1},
                {X+1, y, Z+1},
                {X, y, Z+1}
            }},
            std::array<std::array<float, 2>,4>{{
                {u + ep, v + ep},
                {u + s - ep, v + ep},
                {u + s - ep, v + s - ep},
                {u + ep, v + s - ep}
            }}
            );
            data.insert(data.end(), quad.begin(), quad.end());
        }
        //back face
        if(getBlock(x, y, z - 1) == 0){
            float u = uvCoords[1][0];
            float v = uvCoords[1][1];
            
            std::array<float, 30> quad = makeQuad(
            std::array<std::array<float, 3>,4> {{
                {X+1, y-1, Z},
                {X, y-1, Z},
                {X, y, Z},
                {X+1, y, Z}
            }},
            std::array<std::array<float, 2>,4>{{
                {u + ep, v + ep},
                {u + s - ep, v + ep},
                {u + s - ep, v + s - ep},
                {u + ep, v + s - ep}
            }}
            );
            data.insert(data.end(), quad.begin(), quad.end());
        }
        //top face
        if(getBlock(x, y+1, z) == 0){
            float u = uvCoords[2][0];
            float v = uvCoords[2][1];
            
            std::array<float, 30> quad = makeQuad(
            std::array<std::array<float, 3>,4> {{
                {X, y, Z+1},
                {X+1, y, Z+1},
                {X+1, y, Z},
                {X, y, Z}
            }},
            std::array<std::array<float, 2>,4>{{
                {u + ep, v + ep},
                {u + s - ep, v + ep},
                {u + s - ep, v + s - ep},
                {u + ep, v + s - ep}
            }}
            );
            data.insert(data.end(), quad.begin(), quad.end());
        }
        //bottom face
        if(getBlock(x, y-1, z) == 0){
            float u = uvCoords[3][0];
            float v = uvCoords[3][1];
            
            std::array<float, 30> quad = makeQuad(
            std::array<std::array<float, 3>,4> {{
                {X, y-1, Z},
                {X+1, y-1, Z},
                {X+1, y-1, Z+1},
                {X, y-1, Z+1}
            }},
            std::array<std::array<float, 2>,4>{{
                {u + ep, v + ep},
                {u + s - ep, v + ep},
                {u + s - ep, v + s - ep},
                {u + ep, v + s - ep}
            }}
            );
            data.insert(data.end(), quad.begin(), quad.end());
        }
        //left face
        if(getBlock(x-1, y, z) == 0){
            float u = uvCoords[4][0];
            float v = uvCoords[4][1];
            
            std::array<float, 30> quad = makeQuad(
            std::array<std::array<float, 3>,4> {{
                {X, y-1, Z},
                {X, y-1, Z+1},
                {X, y, Z+1},
                {X, y, Z}
            }},
            std::array<std::array<float, 2>,4>{{
                {u + ep, v + ep},
                {u + s - ep, v + ep},
                {u + s - ep, v + s - ep},
                {u + ep, v + s - ep}
            }}
            );
            data.insert(data.end(), quad.begin(), quad.end());
        }
        //right face
        if(getBlock(x+1, y, z) == 0){
            float u = uvCoords[5][0];
            float v = uvCoords[5][1];
            
            std::array<float, 30> quad = makeQuad(
            std::array<std::array<float, 3>,4> {{
                {X+1, y-1, Z+1},
                {X+1, y-1, Z},
                {X+1, y, Z},
                {X+1, y, Z+1}
            }},
            std::array<std::array<float, 2>,4>{{
                {u + ep, v + ep},
                {u + s - ep, v + ep},
                {u + s - ep, v + s - ep},
                {u + ep, v + s - ep}
            }}
            );
            data.insert(data.end(), quad.begin(), quad.end());
        }
    }
    for(auto i : data) std::cout << i << " ";
    std::cout << "\n";
    return data;
}

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
/*
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
/*
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
*/