#include "scene.hh"
#include "crystal.hh"

static Crystal *engine;

void Crystal::init(){
    gameCode = nullptr;
    curScene = nullptr;
    lm.init(3);
    Draw::init(r);
    materialSystemInit(&ms);
    ss.init();
    defaultShader = ss.newShaderProgram();

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
    materialSystemUninit(&ms);
    ss.uninit();
    fb.uninit();
};

Crystal *getEngine(){
    return engine;
};
void setActiveCameraToCurrentScene(Component::Camera *cam){
    Scene *s = engine->curScene;
    s->activeCam = cam;
};
