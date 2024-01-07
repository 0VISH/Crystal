#version 410 core

layout (location = 0) in vec4 iCol;
layout (location = 1) in vec2 iTex;

layout (location = 0) out vec4 oFragCol;

uniform sampler2D text;

void main(){
     oFragCol = iCol * texture(text, iTex);
};