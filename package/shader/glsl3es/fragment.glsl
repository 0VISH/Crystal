precision mediump float;

varying vec4  fCol;
varying vec2  fTex;
varying float fTexId;

uniform sampler2D textures[10];

void main() {
     int index = int(fTexId);
//     gl_FragColor = fCol * texture2D(textures[index], fTex);
       gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}