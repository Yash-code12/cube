#version 100
precision mediump float;
attribute vec4 position; // Vertex position
attribute vec2 a_textureCoord; // Texture position
varying vec2 v_texCoord;

uniform float u_time;
uniform vec2 screensize;
uniform mat4 projMtx;

void main(){
    vec4 pos = position;
    pos.x += cos(u_time);
    pos.y += sin(u_time);

    gl_Position = pos * projMtx;
    v_texCoord = a_textureCoord;
}