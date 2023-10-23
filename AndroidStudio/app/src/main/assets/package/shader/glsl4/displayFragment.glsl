#version 410 core

layout (location = 0) in vec2 iTextCord;

layout (location = 0) out vec4 oCol;

uniform sampler2D screenTexture;

void main(){
     oCol = texture(screenTexture, iTextCord);
};
