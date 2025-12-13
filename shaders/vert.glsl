#version 100
precision mediump float;
attribute vec4 position; // Vertex position
attribute vec2 a_textureCoord; // Texture position
varying vec2 v_texCoord;

uniform float u_time;
uniform vec2 screensize;
uniform mat4 projMtx;
uniform mat4 viewMtx;
uniform mat4 rotMtx;

void main(){
    vec4 pos = position;
    gl_Position = projMtx * viewMtx* rotMtx * pos;
    v_texCoord = a_textureCoord;
}