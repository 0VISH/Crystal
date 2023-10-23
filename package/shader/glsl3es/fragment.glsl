#version 310 es
precision mediump float;

in vec4 iCol;

out vec4 oFragCol;

void main() {
    oFragCol = iCol;
};