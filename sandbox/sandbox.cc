#include "config.hh"
#include "crystal.hh"
#include "Renderer/renderer.hh"
#include <stdio.h>
Renderer::FuncAddr renderer;
Renderer::Object robj;

EXPORT void rendererRFA(Renderer::FuncAddr *fa){
    renderer = *fa;
};

EXPORT void init(){
    renderer.enableDebugMode();
    robj = renderer.createObject();
    renderer.drawWireframe();
};
EXPORT void render(){
    renderer.drawTriangle(robj);
    renderer.drawQuad(robj);
};
EXPORT void uninit(){
    renderer.destroyObject(robj);
};
