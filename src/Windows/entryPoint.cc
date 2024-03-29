#define ENGINE true

#include "basic.hh"
#include "utils.hh"
logType print;
#include "../include.hh"
#include "include.hh"

#if(DBG)
s32 main(){
#else
//no console
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow){
#endif
    mem::init();
    engine = (Crystal*)mem::alloc(sizeof(Crystal));
    
    HWND window = window::create("Crystal", 1280, 800);
    RenderContext::init(window);

    // Show the window
    ::ShowWindow(window, SW_SHOWDEFAULT);
    ::UpdateWindow(window);

    Package::allocPackages();
    engine->init();
    engine->initGraphics();

    ScreenQuad sq;
    sq.vao = 69;
    HMODULE editorCode = nullptr;
    engine->gameCode = Code::load("gamewin.dll");
    u32 screenShader;
    if(engine->gameCode == NULL){
	editorCode = Code::load("bin/win/dbg/editor.dll");
	ASSERT(editorCode);

	Layer *editorLayer = engine->lm.newLayer();
	editorLayer->onRender = (LayerFunc)GetProcAddress(editorCode, "render");
	editorLayer->onUninit = (LayerFunc)GetProcAddress(editorCode, "uninit");
	editorLayer->onUpdate = (LayerUpdateFunc)GetProcAddress(editorCode, "update");
	auto einit = (void(*)(HWND window))GetProcAddress(editorCode, "init");
	einit(window);

	print = (logType)GetProcAddress(editorCode, "addLog");
	auto setGameTextureAdd = (void(*)(u32* tAdd))GetProcAddress(editorCode, "setGameTextureAdd");
	setGameTextureAdd(&engine->fb.texture);
    }else{
	initLogOutputFile("info.log");
	print = _log;

	print("Loaded game code\n");

	sq = Draw::initScreenQuad();
	screenShader = engine->ss.newShader("package/shader/glsl4/displayVertex.glsl", "package/shader/glsl4/displayFragment.glsl", "display");
	auto gameInit = (void(*)())GetProcAddress(engine->gameCode, "init");
	if(gameInit == nullptr){
	    print("Game code doesnt have init function. Oops!");
	}else{
	    gameInit();
	};
    };
    engine->gameLayerOff = engine->lm.layerCount;
    engine->lm.newLayer();
    Layer *gameLayer = &engine->lm.layers[engine->gameLayerOff];
    gameLayer->onUpdate = GameLayer::onUpdate;
    gameLayer->onRender = GameLayer::onRender;
    gameLayer->onUninit = GameLayer::onUninit;
    
    Package::unloadPkg(Package::curPkg);  //setup.pkg loaded by engine->init();
    
    print("Render context: %s\n", Draw::getRenderContextInfoString());
    
    LARGE_INTEGER freq, start, end;
    f64 dt  = 0;
    QueryPerformanceFrequency(&freq);

    while(true){
	QueryPerformanceCounter(&start);
	
	window::pollEvents();
	if(engine->windowX == 0){break;};

	Event e = engine->ed.getEvent();
	
        engine->lm.updateLayers(e, dt);
        engine->lm.renderLayers();

	Draw::beginFrame(engine->r, engine->fb);
	Draw::draw(engine->r);
	Draw::endFrame(engine->r, engine->fb);
	
	if(editorCode == nullptr){
	    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	    glClear(GL_COLOR_BUFFER_BIT);
  
	    Shader::useShader(screenShader);
	    glBindVertexArray(sq.vao);
	    glBindTexture(GL_TEXTURE_2D, engine->fb.texture);
	    glDrawArrays(GL_TRIANGLES, 0, 6);
	};

	RenderContext::swapBuffers();
	
	QueryPerformanceCounter(&end);
	dt = (end.QuadPart - start.QuadPart);
	dt /= freq.QuadPart;
    }

    if(sq.vao != 69){
	Draw::uninitScreenQuad(sq);
    };
    engine->uninit();
    Package::freePackages();
    Code::unload(engine->gameCode);
    Code::unload(editorCode);
    RenderContext::uninit(window);
    window::destroy(window);

    mem::free(engine);
    dlog("ALLOC_COUNT: %d\n", mem::allocCount);
    if(logOutputFile != nullptr){uninitLogOutputFile();};
    mem::uninit();
    return EXIT_SUCCESS;
}

//@ignore
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
static_assert(sizeof(u8) == 1, "u8 is not 1 byte");
static_assert(sizeof(u16) == 2, "u16 is not 2 byte");
static_assert(sizeof(u32) == 4, "u32 is not 4 byte");
static_assert(sizeof(u64) == 8, "u64 is not 8 byte");
static_assert(sizeof(s8) == 1, "s8 is not 1 byte");
static_assert(sizeof(s16) == 2, "s16 is not 2 byte");
static_assert(sizeof(s32) == 4, "s32 is not 4 byte");
static_assert(sizeof(s64) == 8, "s64 is not 8 byte");
static_assert(sizeof(b8) == 1, "b8 is not 1 byte");
static_assert(sizeof(b16) == 2, "b16 is not 2 byte");
static_assert(sizeof(b32) == 4, "b32 is not 4 byte");
static_assert(sizeof(b64) == 8, "b64 is not 8 byte");
static_assert(sizeof(f32) == 4, "f32 is not 4 byte");
static_assert(sizeof(f64) == 8, "f64 is not 8 byte");
