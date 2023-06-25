#include "../include.hh"

Crystal *engine;

#if(PLAT_WINDOWS)
#include "include.hh"
#endif

#if(EDITOR)
#include "../Editor/include.hh"
#endif

#include GAME_CODE_PATH

s32 main(){
    engine = (Crystal*)mem::alloc(sizeof(Crystal));
    
    window::Window window = window::create(Game::gameName, 1280, 800);
    RenderContext::init(window);

    // Show the window
    ::ShowWindow(window, SW_SHOWDEFAULT);
    ::UpdateWindow(window);

    engine->init();
    
#if(EDITOR)
    Layer *editorLayer = engine->lm.newLayer();
    editorLayer->onUpdate = Editor::onUpdate;
    editorLayer->onRender = Editor::onRender;
    editorLayer->onUninit = Editor::onUninit;
    Editor::init(window);
#endif

    Layer *gameLayer = engine->lm.newLayer();
    gameLayer->onRender = Game::render;
    gameLayer->onUninit = Game::uninit;
    gameLayer->onUpdate = Game::update;
    Game::init();

    while (true)
    {	
	window::pollEvents();
	if(engine->shouldClose){break;};

	Event e = engine->ed.getEvent();
	
        engine->lm.updateLayers(e);
        glClear(GL_COLOR_BUFFER_BIT);
        engine->lm.renderLayers();

	RenderContext::swapBuffers();
    }

    engine->uninit();
    RenderContext::uninit(window);
    window::destroy(window);

    mem::free(engine);

    dlog("DONE :)\n");
    return EXIT_SUCCESS;
}

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
