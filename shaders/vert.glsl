#version 100
attribute vec4 position; // Vertex position
attribute vec2 texCoord; // Texture position

void main(){
    gl_Position = position;
}