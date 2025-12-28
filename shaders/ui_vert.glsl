#version 100
precision mediump float;
attribute vec2 a_ui_position; // Vertex position
attribute vec2 a_ui_textureCoord; // Texture position
varying vec2 v_texCoord;

uniform vec2 screensize;
uniform mat4 u_model;

void main(){
    vec4 screenPos = u_model * vec4(a_ui_position, 0.0, 1.0);
    //vec4 screenPos = vec4(a_ui_position, 0.0, 1.0) * u_model;
    
    vec2 ndcPos;
    ndcPos.x = (screenPos.x/screensize.x*2.0) - 1.0;
    ndcPos.y = 1.0 - (screenPos.y/screensize.y*2.0);
    
    gl_Position = vec4(ndcPos.x, ndcPos.y, 0, 1);
    v_texCoord = a_ui_textureCoord;
}
/*
void main(){
    // Extract the 2x2 rotation/scale part and the translation part manually
    mat2 scaleRotate = mat2(u_model[0].xy, u_model[1].xy);
    vec2 translation = u_model[3].xy; // Column 3 (the 4th column)

    // Calculate pixel position manually
    vec2 screenPos = (scaleRotate * a_ui_position) + translation;
    
    vec2 ndcPos;
    ndcPos.x = (screenPos.x / screensize.x * 2.0) - 1.0;
    ndcPos.y = 1.0 - (screenPos.y / screensize.y * 2.0);
    
    gl_Position = vec4(ndcPos, 0.0, 1.0);
    v_texCoord = a_ui_textureCoord;
}
*/