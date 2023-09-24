void setScene(char *scenePath){
    //TODO: parse and get scene name
    if(engine->curScene != nullptr){
	uninitAndFreeCurrentScene();
    };
    print("Scene: %s", scenePath);
    allocAndSetCurrentScene();
    deserializeToCurrentScene(scenePath);
};
void setMaterialSystem(char *filePath){
    if(engine->ms != nullptr){
	uninitAndFreeMaterialSystem();
    };
    print("Material System: %s", filePath);
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
