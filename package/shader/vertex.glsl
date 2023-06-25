#version 330 core

layout (location = 0) in vec2 iPos;

uniform mat4 uModel;
uniform mat4 uProjectionView;

void main(){
     gl_Position = uProjectionView * uModel * vec4(iPos, 0.0, 1.0);
};