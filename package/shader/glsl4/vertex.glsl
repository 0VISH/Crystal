#version 410 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec4 iCol;
layout (location = 2) in vec2 iTex;

uniform mat4 uProjectionView;

layout (location = 0) out vec4 oCol;
layout (location = 1) out vec2 oTex;

void main(){
     oCol = iCol;
     oTex = iTex;
     gl_Position = uProjectionView * vec4(iPos, 1.0);
};
