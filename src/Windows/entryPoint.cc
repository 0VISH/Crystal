#include "../include.hh"

#if(PLAT_WINDOWS)
#include "include.hh"
#endif

#if(EDITOR)
#include "../Editor/include.hh"
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
    Cry::setupGamePointers();
    
#if(EDITOR)
    Layer *editorLayer = engine->lm.newLayer();
    editorLayer->onUpdate = Editor::onUpdate;
    editorLayer->onRender = Editor::onRender;
    editorLayer->onUninit = Editor::onUninit;
    Editor::init(window);

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

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
