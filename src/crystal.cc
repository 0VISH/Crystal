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
    Scene            *curScene;
    u32               windowX;
    u32               windowY;
    bool              shouldClose;

#if(PLAT_WINDOWS) 
    HMODULE           gameCode;
    FILETIME          lastTime;
#endif
    
    void init(){
	lastTime = {};
	gameCode = nullptr;
	curScene = nullptr;
	lm.init(3);
	materialSystemInit(ms);
	ss.init();
	u32 defaultShader = ss.newShaderProgram();
	Renderer::createDefaultShader(defaultShader);
	fb.init(windowX, windowY);
	Batch::init();
    };
    void uninit(){
	if(lm.layers != nullptr){
	    lm.uninitLayers();
	    lm.uninit();
	};
	materialSystemUninit(ms);
	ss.uninit();
	fb.uninit();
	Batch::uninit();
    };
};

static Crystal *engine;

void setCurrentScene(Scene *s){
    engine->curScene = s;
};
Scene *getCurrentScene(){
    return engine->curScene;
};
