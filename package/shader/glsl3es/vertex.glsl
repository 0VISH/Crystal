precision mediump float;

attribute vec3 vertexPosition;
attribute vec4 vertexColour;

varying vec4 intermediateColour;

uniform mat4 uProjectionView;

void main(){
     intermediateColour = vertexColour;
     gl_Position = uProjectionView * vec4(vertexPosition, 1.0);
}