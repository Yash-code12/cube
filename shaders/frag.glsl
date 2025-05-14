#version 100
precision mediump float;

uniform vec2 screensize;
varying vec2 v_texCoord;
uniform sampler2D u_textureSampler; // The actual texture data

void main() {
    /*
    vec2 uv = gl_FragCoord.xy / screensize; // Normalize
    
    gl_FragColor = vec4(uv, 0.0, 1.0);
    */
    
    vec4 textureColor = texture2D(u_textureSampler, v_texCoord);
    gl_FragColor = textureColor;
    
}