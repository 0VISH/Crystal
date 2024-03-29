#if(WIN)
#define GET_PROC GetProcAddress
#elif(AND)
#define GET_PROC dlsym
#endif

void setScene(char *scenePath){
    if(engine->curScene != nullptr){
	uninitAndFreeCurrentScene();
    };
    allocAndSetCurrentScene();
    if(deserializeToCurrentScene(scenePath) == false){
	mem::free(engine->curScene);
	engine->curScene = nullptr;
	return;
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
    Scene *s = engine->curScene;
    sceneName += 1;
    char buffer[1024];
    len = x-dotOffFromBack-1;
    memcpy(buffer, sceneName, len);
    memcpy(buffer+len, "Init", strlen("Init")+1);
    s->onInit = (LayerFunc)GET_PROC(engine->gameCode, buffer);
    memcpy(buffer+len, "Update", strlen("Update")+1);
    s->onUpdate = (LayerUpdateFunc)GET_PROC(engine->gameCode, buffer);
    memcpy(buffer+len, "Draw", strlen("Draw")+1);
    s->onRender = (LayerFunc)GET_PROC(engine->gameCode, buffer);
    memcpy(buffer+len, "Uninit", strlen("Uninit")+1);
    s->onUninit = (LayerFunc)GET_PROC(engine->gameCode, buffer);
    s->state = SceneState::PLAYING;
    print("Scene: %s\n", scenePath);
};
void setMaterialSystem(char *filePath){
    if(engine->ms != nullptr){
	uninitAndFreeMaterialSystem();
    };
    allocMaterialSystem();
    materialSystemInit();
    print("Material System: %s\n", filePath);
    deserializeMaterialSystem(filePath);
};
