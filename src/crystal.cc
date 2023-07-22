#include "scene.hh"
#include<windows.h>

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

    
    HMODULE           gameCode;
    FILETIME          lastTime;
    
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
