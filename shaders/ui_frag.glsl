#version 100
precision mediump float;

varying vec2 v_texCoord;
uniform sampler2D u_ui_textureSampler; // The actual texture data

void main() {
    vec4 textureColor = texture2D(u_ui_textureSampler, v_texCoord);
    gl_FragColor = textureColor;
    //gl_FragColor = vec4(v_texCoord.x, v_texCoord.y, 0.0, 1.0);
    //gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}