#version 310 es
precision mediump float;

in vec4 intermediateColour;

out vec4 fragmentColour;

void main() {
    fragmentColour = intermediateColour;
};