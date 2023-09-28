void setScene(char *scenePath){
    if(engine->curScene != nullptr){
	uninitAndFreeCurrentScene();
    };
    u32 len = strlen(scenePath);
    char *sceneName = scenePath + len - 1;
    while(*sceneName != '/'){sceneName -= 1;};
    sceneName += 1;
    if(engine->gameLayerOff == -1){
	
    };
    print("Scene: %s\n", scenePath);
    allocAndSetCurrentScene();
    deserializeToCurrentScene(scenePath);
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
