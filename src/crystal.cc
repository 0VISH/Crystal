#include "scene.hh"
#include "crystal.hh"

void Crystal::init(){
    curScene = nullptr;
    lm.init(3);
    ms.init();
    ss.init();
    u32 defaultShader = ss.newShaderProgram();
    Renderer::createDefaultShader(defaultShader);
    fb.init(windowX, windowY);
    Batch::init();
};
void Crystal::uninit(){
    if(lm.layers != nullptr){
	lm.uninitLayers();
	lm.uninit();
    };
    ms.uninit();
    ss.uninit();
    fb.uninit();
    Batch::uninit();
};
