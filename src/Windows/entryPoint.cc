#include "../include.hh"

#if(EDITOR)
#include "../Editor/include.hh"
#endif

s32 main()
{
    EventDispatcher eventDispatcher;
    window::Window window = window::create("test", &eventDispatcher);
    RenderContext::init(window);

    // Show the window
    ::ShowWindow(window, SW_SHOWDEFAULT);
    ::UpdateWindow(window);

    Crystal engine;
    engine.init();
    
#if(EDITOR)
    Layer *editorLayer = engine.lm.newLayer();
    editorLayer->onUpdate = Editor::onUpdate;
    editorLayer->onRender = Editor::onRender;
    editorLayer->onUninit = Editor::onUninit;
    Editor::init(window);
#endif

    Layer *trialLayer = engine.lm.newLayer();
    trialLayer->onRender = game::render;
    trialLayer->onUninit = game::uninit;
    game::init();

    while (true)
    {
	window::pollEvents();
	if(window::shouldClose){break;};

	Event e = eventDispatcher.getEvent();
	
        engine.lm.updateLayers(e);
        glClear(GL_COLOR_BUFFER_BIT);
        engine.lm.renderLayers();

	RenderContext::swapBuffers();
    }

    engine.uninit();
    RenderContext::uninit(window);
    window::destroy(window);

    dlog("DONE :)\n");
    return EXIT_SUCCESS;
}

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
