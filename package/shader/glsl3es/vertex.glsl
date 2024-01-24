precision mediump float;

attribute vec3  vPos;
attribute vec4  vCol;
attribute vec2  vTex;
attribute float vTexId;

uniform mat4 uProjectionView;

varying vec4  fCol;
varying vec2  fTex;
varying float fTexId;

void main(){
     fCol = vCol;
     fTex = vTex;
     fTexId = vTexId;
     gl_Position = uProjectionView * vec4(vPos, 1.0);
}