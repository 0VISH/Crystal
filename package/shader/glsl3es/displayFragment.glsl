#version 310 es
precision mediump float;

in vec2 intermediateTextureCordinate;

out vec4 fragmentColour;

uniform sampler2D screenTexture;

void main(){
     fragmentColour = texture(screenTexture, intermediateTextureCordinate);
};