#version 410 core

layout (location = 0) in vec2 iPos;
layout (location = 1) in vec2 iTextCord;

layout (location = 0) out vec2 oTextCord;

void main(){
     oTextCord = iTextCord;
     gl_Position = vec4(iPos, 0.0, 1.0);
};
