#version 100
precision mediump float;

varying vec2 v_texCoord;
uniform sampler2D u_textureSampler; // The actual texture data

void main() {
    
    vec4 textureColor = texture2D(u_textureSampler, v_texCoord);
    gl_FragColor = textureColor;
}