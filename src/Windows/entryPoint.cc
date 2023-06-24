#include "../include.hh"

#if(EDITOR)
#include "../Editor/include.hh"
#endif

Crystal *engine;

#include GAME_CODE_PATH

s32 main(){
    EventDispatcher eventDispatcher;
    eventDispatcher.init();
    window::Window window = window::create(Game::gameName, &eventDispatcher);
    RenderContext::init(window);

    // Show the window
    ::ShowWindow(window, SW_SHOWDEFAULT);
    ::UpdateWindow(window);

    engine = (Crystal*)mem::alloc(sizeof(Crystal));
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
	if(window::shouldClose){break;};

	Event e = eventDispatcher.getEvent();
	
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
