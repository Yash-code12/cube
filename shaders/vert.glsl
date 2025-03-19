#version 100
precision mediump float;
attribute vec4 position; // Vertex position
attribute vec2 texCoord; // Texture position

uniform vec2 screensize;
uniform mat4 projMtx;

void main(){
    gl_Position = position*projMtx;
}