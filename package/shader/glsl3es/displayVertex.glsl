precision mediump float;

attribute vec2 vertexPosition;
attribute vec2 vertexTextureCordinate;

varying vec2 intermediateTextureCordinate;

void main() {
    intermediateTextureCordinate = vertexTextureCordinate;
    gl_Position = vec4(vertexPosition, 0.0, 1.0);
}