#include "quad.h"
#include <iostream>
#include <vector>
#include <GLES2/gl2.h>
using namespace std;
//make 2 tri (face) from 4 vertices
//vertex ex:- [x,y,z]
//start is bottom left
//c-clockwise
vector<GLfloat> makeQuad(vector<GLfloat> v){
    vector<vector<int>> a = {
        {0,1,3}, //Tri1 vertices BL, BR, TL
        {2,1,3} //Tri2 vertices TR, BR, TL
    };
    vector<vector<vector<GLfloat>>> b = {
        {{0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f}},
        {{1.0f,1.0f},{1.0f,0.0f},{0.0f,1.0f}}
    };
    vector<GLfloat> tri1;
    vector<GLfloat> tri2;
    vector<GLfloat> face;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            //vertices for tri1
            tri1.push_back(v[ a[0][i]*3 + j]);
            //vertices for tri2
            tri2.push_back(v[ a[1][i]*3 + j]);
        }
        //tex coords for tri1
        tri1.push_back(b[0][i][0]);
        tri1.push_back(b[0][i][1]);
        //tex coords for tri2
        tri2.push_back(b[1][i][0]);
        tri2.push_back(b[1][i][1]);
    }
    
    for(auto i : tri1) face.push_back(i);
    for(auto i : tri2) face.push_back(i);
    return face;
}
//8 vertices for cube
//makes left, bottom and front face, then uses those to faces to make other faces
vector<GLfloat> makeCube(vector<GLfloat> v){
    vector<vector<int>> indices = {
        {0,1,2,3}, //front
        {0,1,5,4}, //bottom
        {4,5,6,7}, //back
        {3,2,6,7}, //top
        {4,0,3,7}, //left
        {1,5,6,2} //right
    };
    vector<GLfloat> cube;
    //sets of faces
    vector<vector<GLfloat>> vertices;
    for(int i = 0; i < indices.size();++i){
        //face
        vector<GLfloat> face;
        for(int j = 0; j < indices[i].size();++j){
            for(int k = 0; k < 3;++k){
                face.push_back(
                v[indices[i][j]*3 + k]);
            }
        }
        
        vertices.push_back(face);
    }
    
    for(vector<GLfloat>& face : vertices){
        for(auto& p : makeQuad(face)){
            cube.push_back(p);
        }
    }
    
    return cube;
}