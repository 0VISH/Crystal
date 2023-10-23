#version 310 es
precision mediump float;

in vec2 iTextCord;

out vec4 oCol;

uniform sampler2D screenTexture;

void main(){
     oCol = texture(screenTexture, iTextCord);
};