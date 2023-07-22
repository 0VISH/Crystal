#define SETUP_POINTERS(HANDLE)						\
    auto setupUtilPointer = (void(*)(logType l, getComponentUIDType gcut, setGameFolderType sgft))GetProcAddress(HANDLE, "setupUtilPointers"); \
    setupUtilPointer(print, getComponentUID, Code::setGameFolder);	\
									\
    auto setupPointers = (void(*)(materialInitType mit, materialUninitType mut, materialRegisterEntityType mret, \
				  materialSystemInitType msit, materialSystemUninitType msut, newMaterialType nmt, \
				  componentPoolInitType cpit, componentPoolNewComponentType cpnct, componentPoolRemoveComponentType cprct, componentPoolGetComponentType cpgct, \
				  allocSceneType ast, freeSceneType fst, sceneInitType sit, sceneUninitType sut, sceneNewEntityType snet, \
				  setCurrentSceneType scst, getCurrentSceneType gcst))GetProcAddress(HANDLE, "setupPointers"); \
    setupPointers(materialInit, materialUninit, materialRegisterEntity,	\
		  materialSystemInit, materialSystemUninit, newMaterial, \
		  componentPoolInit, componentPoolNewComponent, componentPoolRemoveComponent, componentPoolGetComponent, \
		  allocScene, freeScene, sceneInit, sceneUninit, sceneNewEntity, \
		  setCurrentScene, getCurrentScene);			\

namespace Code{
    char dllTemp[1000];
    char dll[1000];
    char main[1000];
    u8 x;
    u8 y;
    u32 tempOff;

    void unload(HMODULE code){
	if(code != NULL){FreeLibrary(code);};
    };
    FILETIME getLastWriteTime(){
	FILETIME lwt = {};
	WIN32_FIND_DATA data;
	HANDLE file = FindFirstFileA(dll, &data);
	if(file != INVALID_HANDLE_VALUE){
	    lwt = data.ftLastWriteTime;
	    FindClose(file);
	};
	return lwt;
    };
    HMODULE cpySrcAndLoadTemp();
    void setGameFolder(char *path){
	x = 65;
	y = 65;
	u32 off = strlen(path);
	memcpy(dllTemp, path, off);
	memcpy(dll, path, off);
	memcpy(main, path, off);
	char *dllTempPath = "\\bin\\gameWin_temp";
	memcpy(dllTemp+off, dllTempPath, strlen(dllTempPath));
	memcpy(dllTemp+off+strlen(dllTempPath)+2, ".dll", strlen(".dll"));
	tempOff = strlen(dllTempPath)+off;
	dllTemp[tempOff] = x;
	dllTemp[tempOff+1] = y;
	char *dllPath = "\\bin\\gameWin.dll";
	memcpy(dll+off, dllPath, strlen(dllPath));
	char *mainPath = "\\src\\main.cc";
	memcpy(main+off, mainPath, strlen(mainPath));

	engine->gameCode = cpySrcAndLoadTemp();
	if(engine->gameCode == NULL){
	    print("Game code not found");
	    return;
	};
	engine->lastTime = Code::getLastWriteTime();

	Layer *gameLayer = engine->lm.newLayer();
	gameLayer->onRender = (LayerFunc)GetProcAddress(engine->gameCode, "render");
	gameLayer->onUninit = (LayerFunc)GetProcAddress(engine->gameCode, "uninit");
	gameLayer->onUpdate = (LayerUpdateFunc)GetProcAddress(engine->gameCode, "update");
	auto ginit = (void(*)())GetProcAddress(engine->gameCode, "init");
	ginit();
    };
    HMODULE load(char *path){
	HMODULE code = LoadLibraryA(path);
	if(code == nullptr){return nullptr;};

	SETUP_POINTERS(code);
	return code;
    };
    HMODULE cpySrcAndLoadTemp(){
	y += 1;
	if(y == 90){
	    y = 65;
	    x += 1;
	};
	dllTemp[tempOff] = x;
	dllTemp[tempOff+1] = y;
	
	print("cpy: %s %s\n", dll, dllTemp);
	BOOL b = CopyFile(dll, dllTemp, 0);
	if(!b){
	    printf("\ncpy: %d\n", GetLastError());
	};
	return load(dllTemp);
    };
};
