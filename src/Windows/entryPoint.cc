#include "../include.hh"

#if(EDITOR)
#include "../Editor/include.hh"
#endif

s32 main(){
    Crystal engine;
    EventDispatcher eventDispatcher;
    window::Window window = window::create("crytal test", &eventDispatcher);
    if(window == NULL){
	log("Could not open a window");
	return EXIT_SUCCESS;
    };
    RenderContext::init(window);
    engine.init();
#if(EDITOR)
    Layer *editorLayer = engine.lm.newLayer();
    editorLayer->onUpdate = Editor::onUpdate;
    editorLayer->onRender = Editor::onRender;
    editorLayer->onUninit = Editor::onUninit;
    Editor::init(window);
#endif

    while(true){
	window::pollEvents();
	if(window::shouldClose){break;};

	glClear(GL_COLOR_BUFFER_BIT);

	engine.lm.updateLayers(eventDispatcher.event);
	engine.lm.renderLayers();
	
	RenderContext::swapBuffers();

	eventDispatcher.clearEvent();
    };

    engine.uninit();
    RenderContext::uninit(window);
    window::destroy(window);
    dlog("DONE :)\n");
    return EXIT_SUCCESS;
}

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
