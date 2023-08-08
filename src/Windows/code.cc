#define SETUP_POINTERS(HANDLE)						\
    auto setupUtilPointer = (void(*)(logType l, setGameFolderType sgft, editorSignalType est))GetProcAddress(HANDLE, "setupUtilPointers"); \
    setupUtilPointer(print, Code::setGameFolder, editorSignal); \
									\
    auto setupPointers = (void(*)(materialRegisterEntityType mret, newMaterialType nmt, \
				  componentPoolInitType cpit, componentPoolNewComponentType cpnct, componentPoolRemoveComponentType cprct, componentPoolGetComponentType cpgct, \
				  allocSceneType ast, freeSceneType fst, sceneInitType sit, sceneUninitType sut, sceneNewEntityType snet, getEntityType get, \
				  setCurrentSceneType scst, getCurrentSceneType gcst, \
				  getRendererType grt, getMaterialSystemType gmst, \
				  isKeyDownType ikdt))GetProcAddress(HANDLE, "setupPointers"); \
    setupPointers(materialRegisterEntity,  newMaterial,			\
		  componentPoolInit, componentPoolNewComponent, componentPoolRemoveComponent, componentPoolGetComponent, \
		  allocScene, freeScene, sceneInit, sceneUninit, sceneNewEntity, getEntity, \
		  setCurrentScene, getCurrentScene,			\
		  getRenderer,	getMaterialSystem,			\
		  isKeyDown);						\

namespace Code{
    char dllTemp[100];
    char dll[100];
    char main[100];

    void unload(HMODULE code){
	if(code != NULL){FreeLibrary(code);};
    };
    HMODULE cpySrcAndLoadTemp();
    void setGameFolder(char *path){
	u32 off = strlen(path);
	memcpy(dllTemp, path, off);
	memcpy(dll, path, off);
	memcpy(main, path, off);
	char *dllTempPath = "\\bin\\gameWin_temp.dll";
	memcpy(dllTemp+off, dllTempPath, strlen(dllTempPath));
	char *dllPath = "\\bin\\gameWin.dll";
	memcpy(dll+off, dllPath, strlen(dllPath));
	char *mainPath = "\\src\\main.cc";
	memcpy(main+off, mainPath, strlen(mainPath));

	engine->gameCode = cpySrcAndLoadTemp();
	if(engine->gameCode == NULL){
	    print("Game code not found");
	    return;
	};

	Layer *gameLayer = engine->lm.newLayer();
	gameLayer->onRender = (LayerFunc)GetProcAddress(engine->gameCode, "render");
	gameLayer->onUninit = (LayerFunc)GetProcAddress(engine->gameCode, "uninit");
	gameLayer->onUpdate = (LayerUpdateFunc)GetProcAddress(engine->gameCode, "update");
	auto ginit = (void(*)())GetProcAddress(engine->gameCode, "init");
	ginit();

	print("@LOADED GAME FOLDER: %s", dll);
    };
    HMODULE load(char *path){
	HMODULE code = LoadLibraryA(path);
	if(code == nullptr){return nullptr;};
	SETUP_POINTERS(code);
	return code;
    };
    HMODULE cpySrcAndLoadTemp(){
	BOOL b = CopyFile(dll, dllTemp, 0);
	if(!b){
	    printf("\ncopying src to temp dll file failed: %d\n", GetLastError());
	};
	return load(dllTemp);
    };
};
