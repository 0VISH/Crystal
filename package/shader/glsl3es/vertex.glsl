#version 310 es

in vec3 vertexPosition;
in vec4 vertexColour;

out vec4 intermediateColour;

uniform mat4 uProjectionView;

void main(){
     intermediateColour = vertexColour;
     gl_Position = uProjectionView * vec4(vertexPosition, 1.0);
};