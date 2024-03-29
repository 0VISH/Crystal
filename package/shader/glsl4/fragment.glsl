#version 410 core

layout (location = 0) in vec4  iCol;
layout (location = 1) in vec2  iTex;
layout (location = 2) in float iTexId;

uniform sampler2D textures[10];

layout (location = 0) out vec4 oFragCol;

void main(){
     int index = int(iTexId);
     oFragCol = iCol * texture(textures[index], iTex);
};