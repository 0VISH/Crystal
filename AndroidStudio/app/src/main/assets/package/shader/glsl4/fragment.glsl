#version 410 core

layout (location = 0) in vec4 iCol;

layout (location = 0) out vec4 oFragCol;

void main(){
     oFragCol = iCol;
};