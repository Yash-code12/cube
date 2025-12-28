#version 100
precision mediump float;

attribute vec4 a_position; // Vertex position
attribute vec2 a_textureCoord; // Texture position
varying vec2 v_texCoord;

uniform mat4 projMtx;
uniform mat4 viewMtx;

void main(){
    vec4 pos = a_position;
    gl_Position = projMtx * viewMtx * pos;
    v_texCoord = a_textureCoord;
}