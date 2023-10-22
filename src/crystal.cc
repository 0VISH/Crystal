#include "scene.hh"
#include "crystal.hh"

Crystal *engine;

void Crystal::init(){
    gameCode = nullptr;
    curScene = nullptr;
    gameLayerOff = -1;
    lm.init(3);
};
void Crystal::initGraphics(){
    Draw::init(r);
    allocMaterialSystem();
    materialSystemInit();
    ss.init();
    Package::loadPkg("package/setup.pkg", Package::curPkg);
    u32 defaultShader = ss.newShader("package/shader/vertex.glsl", "package/shader/fragment.glsl");
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
