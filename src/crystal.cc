#include "scene.hh"
#include "crystal.hh"

Crystal *engine;

void Crystal::init(){
    gameCode = nullptr;
    curScene = nullptr;
    allocMaterialSystem();
    materialSystemInit();
    ss.init();
    gameLayerOff = -1;
    lm.init(3);
};
void Crystal::initGraphics(){
    Draw::init(r);
    Package::loadPkg("package/setup.pkg", Package::curPkg);
#if(WIN)
    u32 defaultShader = ss.newShader("package/shader/glsl4/vertex.glsl", "package/shader/glsl4/fragment.glsl", "default");
#elif(AND)
    u32 defaultShader = ss.newShader("package/shader/glsl3es/vertex.glsl", "package/shader/glsl3es/fragment.glsl", "default");
#endif
    Shader::useShader(defaultShader);
    fb.init(windowX, windowY);
};
void Crystal::uninit(){
    if(lm.layers != nullptr){
	lm.uninitLayers();
	lm.uninit();
    };
    Draw::uninit(r);
    uninitAndFreeMaterialSystem();
    ss.uninit();
    fb.uninit();
};

Crystal *getEngine(){
    return engine;
};
void setActiveCameraToCurrentScene(Entity e){
    ASSERT(e > -1);
    if(e < 0){
	print("Invalid Entity ID: %d", e);
	return;
    };
    Scene *s = engine->curScene;
    s->activeCam = e;
};
