#include "../include.hh"

Crystal *engine;

void setCurrentScene(Scene *s){
    engine->curScene = s;
};
Scene *getCurrentScene(){
    return engine->curScene;
};

#include "include.hh"

#include "utils.hh"
#include "gamee.hh"
#include "code.cc"

s32 main(){
    mem::calls = 0;
    engine = (Crystal*)mem::alloc(sizeof(Crystal));
    
    window::Window window = window::create("TODO: CLEANUP", 1280, 800);
    RenderContext::init(window);

    // Show the window
    ::ShowWindow(window, SW_SHOWDEFAULT);
    ::UpdateWindow(window);

    engine->init();

    HMODULE editorCode = nullptr;
    engine->gameCode = Code::load("gameWin.dll");
    if(engine->gameCode == NULL){
	editorCode = Code::load("bin/win/dbg/editor.dll");

	Layer *editorLayer = engine->lm.newLayer();
	editorLayer->onRender = (LayerFunc)GetProcAddress(editorCode, "render");
	editorLayer->onUninit = (LayerFunc)GetProcAddress(editorCode, "uninit");
	editorLayer->onUpdate = (LayerUpdateFunc)GetProcAddress(editorCode, "update");
	auto einit = (void(*)(HWND window, u32 *batchDrawCall))GetProcAddress(editorCode, "init");
	einit(window, &Batch::drawCalls);
    }else{
	//TODO: 
    };

    LARGE_INTEGER freq, start, end;
    f64 dt  = 0;
    QueryPerformanceFrequency(&freq);
    
    
    while(true){
	QueryPerformanceCounter(&start);

	if(editorCode != NULL && engine->gameCode != NULL){
	    FILETIME curTime = Code::getLastWriteTime();
	    
	    if(CompareFileTime(&curTime, &engine->lastTime) != 0){
		Code::unload(engine->gameCode);
		engine->gameCode = Code::cpySrcAndLoadTemp();
		engine->lastTime = curTime;
		print("\nRELOADED\n");

		Layer *gameLayer = &engine->lm.layers[engine->lm.layerCount - 1];
		gameLayer->onRender = (LayerFunc)GetProcAddress(engine->gameCode, "render");
		gameLayer->onUninit = (LayerFunc)GetProcAddress(engine->gameCode, "uninit");
		gameLayer->onUpdate = (LayerUpdateFunc)GetProcAddress(engine->gameCode, "update");
	    };
	};
	
	window::pollEvents();
	if(engine->shouldClose){break;};

	Event e = engine->ed.getEvent();
	
        engine->lm.updateLayers(e, dt);
        engine->lm.renderLayers();

	RenderContext::swapBuffers();

	QueryPerformanceCounter(&end);
	dt = (end.QuadPart - start.QuadPart);
	dt /= freq.QuadPart;
    }
    
    engine->uninit();
    Code::unload(engine->gameCode);
    Code::unload(editorCode);
    RenderContext::uninit(window);
    window::destroy(window);

    mem::free(engine);

    dlog("CALLS: %d\nNOT_FREED: %lld\n", mem::calls, mem::notFreed);
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
