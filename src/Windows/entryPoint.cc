#include "../include.hh"

Crystal *engine;

#include "include.hh"

#if(EDITOR)
#include "console.hh"

namespace Editor{
    extern void render();
    extern void uninit();
    extern void init(window::Window window, u32 *batchDrawCalls);
    extern bool update(Event e, f64 dt);
};
#endif

namespace Game{
    extern void render();
    extern void uninit();
    extern void init();
    extern bool update(Event e, f64 dt);

    extern char *gameName;
};

s32 main(){
    mem::calls = 0;
    engine = (Crystal*)mem::alloc(sizeof(Crystal));
    
    window::Window window = window::create(Game::gameName, 1280, 800);
    RenderContext::init(window);

    // Show the window
    ::ShowWindow(window, SW_SHOWDEFAULT);
    ::UpdateWindow(window);

    engine->init();
    
#if(EDITOR)
    Layer *editorLayer = engine->lm.newLayer();
    editorLayer->onUpdate = Editor::update;
    editorLayer->onRender = Editor::render;
    editorLayer->onUninit = Editor::uninit;
    Editor::init(window, &Batch::drawCalls);

    LOG("Render context: %s", Renderer::getRenderContextInfoString());
#endif

    Layer *gameLayer = engine->lm.newLayer();
    gameLayer->onRender = Game::render;
    gameLayer->onUninit = Game::uninit;
    gameLayer->onUpdate = Game::update;
    Game::init();

    LARGE_INTEGER freq, start, end;
    f64 dt  = 0;
    QueryPerformanceFrequency(&freq);
    
    while(true){
	QueryPerformanceCounter(&start);
	
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
