void editorSignal(){
    if(engine->gameCode){
	Code::unload(engine->gameCode);
	engine->gameCode = Code::cpySrcAndLoadTemp();
	print("@RELOADED %s\n", Code::dllTemp);

	Layer *gameLayer = &engine->lm.layers[engine->lm.layerCount - 1];
	gameLayer->onRender = (LayerFunc)GetProcAddress(engine->gameCode, "render");
	gameLayer->onUninit = (LayerFunc)GetProcAddress(engine->gameCode, "uninit");
	gameLayer->onUpdate = (LayerUpdateFunc)GetProcAddress(engine->gameCode, "update");
    }else{
	print("[error] Game folder not selected");
    }
};
