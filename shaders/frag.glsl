#version 100
precision mediump float;

uniform vec2 screensize;

void main() {
    vec2 uv = gl_FragCoord.xy / screensize; // Normalize
    
    gl_FragColor = vec4(uv, 0.0, 1.0);
}