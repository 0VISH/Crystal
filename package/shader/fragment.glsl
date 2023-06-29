#version 330 core

layout (location = 0) out vec4 oFragCol;

uniform vec4 uCol;

void main(){
     oFragCol = uCol;
};