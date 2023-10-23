#version 310 es

in vec2 iPos;
in vec2 iTextCord;

out vec2 oTextCord;

void main() {
    oTextCord = iTextCord;
    gl_Position = vec4(iPos, 0.0, 1.0);
};