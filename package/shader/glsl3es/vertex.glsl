#version 310 es

in vec3 iPos;
in vec4 iCol;

out vec4 oCol;

uniform mat4 uProjectionView;

void main(){
     oCol = iCol;
     gl_Position = uProjectionView * vec4(iPos, 1.0);
};