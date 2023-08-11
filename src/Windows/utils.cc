void editorSignal(){
    if(engine->gameCode){
	Code::unload(engine->gameCode);
	engine->gameCode = Code::cpySrcAndLoadTemp();

	Layer *gameLayer = &engine->lm.layers[engine->lm.layerCount - 1];
	gameLayer->onRender = (LayerFunc)GetProcAddress(engine->gameCode, "render");
	gameLayer->onUninit = (LayerFunc)GetProcAddress(engine->gameCode, "uninit");
	gameLayer->onUpdate = (LayerUpdateFunc)GetProcAddress(engine->gameCode, "update");
	auto *onReload = (void(*)())GetProcAddress(engine->gameCode, "reload");
	onReload();
	print("@RELOADED %s\n", Code::dllTemp);
    }else{
	print("[error] Game folder not selected");
    }
};
