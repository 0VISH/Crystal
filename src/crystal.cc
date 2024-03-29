#include "scene.hh"
#include "crystal.hh"

Crystal *engine;

void Crystal::init(){
    gameCode = nullptr;
    curScene = nullptr;
    allocMaterialSystem();
    materialSystemInit();
    textures.init();
    textureIds.init();
    ss.init();
    gameLayerOff = -1;
    lm.init(3);
};
void Crystal::initGraphics(){    
    Draw::init(r);
    Package::loadPkg("package/setup.pkg", Package::curPkg);
#if(WIN)
    ss.newShader("package/shader/glsl4/vertex.glsl", "package/shader/glsl4/fragment.glsl", "default");
#elif(AND)
    ss.newShader("package/shader/glsl3es/vertex.glsl", "package/shader/glsl3es/fragment.glsl", "default");
#endif
    initTextures("default");
    u32 id = loadWhiteTexture();
    char *white = "white";
    textures.insertValue({white, (u32)strlen(white)}, id);
    textureIds.push(id);
    fb.init(windowX, windowY);
};
void Crystal::uninit(){
    textureIds.uninit();
    textures.uninit(mem::free);
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
    if(e < 0){
	print("Invalid Entity ID: %d. Cannot set active cammera", e);
	return;
    };
    Scene *s = engine->curScene;
    s->activeCam = e;
};
