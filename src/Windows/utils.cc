void setScene(char *scenePath){
    //TODO: parse and get scene name
    if(engine->curScene != nullptr){
	uninitAndFreeCurrentScene();
    };
    allocAndSetCurrentScene();
    deserializeToCurrentScene(scenePath);
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
