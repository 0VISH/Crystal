#version 410 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec4 iCol;

uniform mat4 uProjectionView;

layout (location = 0) out vec4 oCol;

void main(){
     oCol = iCol;
     gl_Position = uProjectionView * vec4(iPos, 1.0);
};
