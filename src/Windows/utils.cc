LayerFunc setScene(char *scenePath){
    if(engine->curScene != nullptr){
	uninitAndFreeCurrentScene();
    };
    u32 len = strlen(scenePath);
    u32 dotOffFromBack;
    u32 x = 0;
    char *sceneName = scenePath + len - 1;
    while(*sceneName != '\\' && *sceneName != '/'){
	if(*sceneName == '.'){dotOffFromBack=x;};
	sceneName -= 1;
	x += 1;
    };
    sceneName += 1;
    char buffer[1024];
    len = x-dotOffFromBack-1;
    memcpy(buffer, sceneName, len);
    Layer *gameLayer;
    if(engine->gameLayerOff == -1){
	engine->gameLayerOff = engine->lm.layerCount;
	gameLayer = engine->lm.newLayer();
    }else{
	gameLayer = &engine->lm.layers[engine->gameLayerOff];
    };
    memcpy(buffer+len, "Init", strlen("Init")+1);
    //TODO: save this somewhere?
    auto ginit = (LayerFunc)GetProcAddress(engine->gameCode, buffer);
    memcpy(buffer+len, "Update", strlen("Update")+1);
    gameLayer->onUpdate = (LayerUpdateFunc)GetProcAddress(engine->gameCode, buffer);
    memcpy(buffer+len, "Draw", strlen("Draw")+1);
    gameLayer->onRender = (LayerFunc)GetProcAddress(engine->gameCode, buffer);
    memcpy(buffer+len, "Uninit", strlen("Uninit")+1);
    gameLayer->onUninit = (LayerFunc)GetProcAddress(engine->gameCode, buffer);
    print("Scene: %s\n", scenePath);
    allocAndSetCurrentScene();
    deserializeToCurrentScene(scenePath);
    return ginit;
};
void setMaterialSystem(char *filePath){
    if(engine->ms != nullptr){
	uninitAndFreeMaterialSystem();
    };
    print("Material System: %s\n", filePath);
    allocMaterialSystem();
    deserializeMaterialSystem(filePath);
};
void editorSignal(){
    if(engine->gameCode){
	Code::unload(engine->gameCode);
	engine->gameCode = Code::cpySrcAndLoadTemp();

	print("Reloaded: %s\n", Code::dllTemp);
    }else{
	print("[error] Game folder not selected");
    }
};
