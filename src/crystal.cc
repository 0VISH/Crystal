#include "scene.hh"

#if(PLAT_WINDOWS)

#pragma warning(disable: 4005) //glad.h redifines APIENTRY
#include <windows.h>
#pragma warning(default: 4005)

#endif

struct Crystal{
    LayerManager      lm;
    EventDispatcher   ed;
    MaterialSystem    ms;
    ShaderSystem      ss;
    FrameBuffer       fb;
    Renderer          r;
    Scene            *curScene;
    u32               windowX;
    u32               windowY;
    u32               defaultShader;
    u32               screenShader;
    bool              shouldClose;

#if(PLAT_WINDOWS) 
    HMODULE           gameCode;
#endif
    
    void init(){
	gameCode = nullptr;
	curScene = nullptr;
	lm.init(3);
	Draw::init(r);
	materialSystemInit(&ms);
	ss.init();
	defaultShader = ss.newShaderProgram();
	Shader::createShader("package/shader/vertex.glsl", "package/shader/fragment.glsl", defaultShader);
	Shader::useShader(defaultShader);
	fb.init(windowX, windowY);
    };
    void uninit(){
	if(lm.layers != nullptr){
	    lm.uninitLayers();
	    lm.uninit();
	};
	Draw::uninit(r);
	materialSystemUninit(&ms);
	ss.uninit();
	fb.uninit();
    };
};

static Crystal *engine;

void setCurrentScene(Scene *s){
    engine->curScene = s;
};
Scene *getCurrentScene(){
    return engine->curScene;
};
Renderer *getRenderer(){
    return &engine->r;
};
MaterialSystem *getMaterialSystem(){
    return &engine->ms;
};
