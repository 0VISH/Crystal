#version 410 core

layout (location = 0) in vec2 iTextCord;

layout (location = 0) out vec4 oCol;

uniform sampler2D screenTexture;

void main(){
     oCol = vec4(4.0, 0.3, 0.3, 1.0);//texture(screenTexture, iTextCord);
};
