#version 410 core

layout (location = 0) in vec4 iCol;

uniform vec4 uCol;

layout (location = 0) out vec4 oFragCol;

void main(){
     oFragCol = iCol + uCol;
};