#include "../include.hh"

#if(EDITOR)
#include "../Editor/include.hh"
#endif

char* gameName     = "Sandbox";
char* gameCodePath = "sandbox/bin/sandbox.dll";

s32 main(){
    EventDispatcher eventDispatcher;
    eventDispatcher.init();
    window::Window window = window::create(gameName, &eventDispatcher);
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

    HMODULE gameCodeDLL = LoadLibraryA(gameCodePath);
    if(gameCodeDLL == NULL){
	log("Could not load game code %s\n", gameCodePath);
	return EXIT_SUCCESS;
    };
    Renderer::RFA RFAInGameCode = (Renderer::RFA)GetProcAddress(gameCodeDLL, "rendererRFA");
    Renderer::FuncAddr fa = Renderer::CreateAndRFA();
    RFAInGameCode(&fa);

    Layer *gameLayer = engine.lm.newLayer();
    gameLayer->onRender = (LayerFunc)GetProcAddress(gameCodeDLL, "render");
    gameLayer->onUninit = (LayerFunc)GetProcAddress(gameCodeDLL, "uninit");
    gameLayer->onUpdate = (LayerUpdateFunc)GetProcAddress(gameCodeDLL, "update");
    LayerFunc gameInit = (LayerFunc)GetProcAddress(gameCodeDLL, "init");
    gameInit();

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
    FreeLibrary(gameCodeDLL);
    RenderContext::uninit(window);
    window::destroy(window);

    dlog("DONE :)\n");
    return EXIT_SUCCESS;
}

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
