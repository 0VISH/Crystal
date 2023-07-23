void editorSignal(){
    Code::unload(engine->gameCode);
    engine->gameCode = Code::cpySrcAndLoadTemp();
    print("\nRELOADED\n");

    Layer *gameLayer = &engine->lm.layers[engine->lm.layerCount - 1];
    gameLayer->onRender = (LayerFunc)GetProcAddress(engine->gameCode, "render");
    gameLayer->onUninit = (LayerFunc)GetProcAddress(engine->gameCode, "uninit");
    gameLayer->onUpdate = (LayerUpdateFunc)GetProcAddress(engine->gameCode, "update");
};
