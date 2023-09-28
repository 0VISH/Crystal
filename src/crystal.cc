#include "scene.hh"
#include "crystal.hh"

static Crystal *engine;

void Crystal::init(){
    gameCode = nullptr;
    curScene = nullptr;
    gameLayerOff = -1;
    lm.init(3);
    Draw::init(r);
    allocMaterialSystem();
    materialSystemInit();
    ss.init();
    u32 defaultShader = ss.newShaderProgram();

    Package::loadPkg("package/setup.pkg", Package::curPkg);
	
    Shader::createShader("package/shader/vertex.glsl", "package/shader/fragment.glsl", defaultShader);
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
    Scene *s = engine->curScene;
    s->activeCam = e;
};
