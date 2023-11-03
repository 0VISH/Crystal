#version 310 es

in vec2 vertexPosition;
in vec2 vertexTextureCordinate;

out vec2 intermediateTextureCordinate;

void main() {
    intermediateTextureCordinate = vertexTextureCordinate;
    gl_Position = vec4(vertexPosition, 0.0, 1.0);
};