#define SETUP_POINTERS(HANDLE)						\
    auto setupUtilPointer = (void(*)(logType l,				\
				     setGameCodeType sgct, setSceneType sct, \
				     editorSignalType est))GetProcAddress(HANDLE, "setupUtilPointers"); \
    setupUtilPointer(print, Code::setGameCode, setScene, editorSignal);	\
									\
    auto setupPointers = (void(*)(materialRegisterEntityType mret, newMaterialType nmt, \
				  componentPoolInitType cpit, componentPoolAddComponentType cpact, \
				  allocAndSetCurrentSceneType ascst, uninitAndFreeCurrentSceneType ufcst, \
				  initCurrentSceneType icst, setActiveCameraToCurrentSceneType sacct, \
				  serializeCurrentSceneType secst, deserializeToCurrentSceneType dcst, \
				  sceneNewEntityType snet, getEntityType get, \
				  removeComponentType rct, getComponentType gct, \
				  createRigidBodyType crbt, createBoxColliderFixtureType cbcft, \
				  getEngineType gent,			\
				  isKeyDownType ikdt))GetProcAddress(HANDLE, "setupPointers"); \
    setupPointers(materialRegisterEntity,  newMaterial,			\
		  componentPoolInit, componentPoolAddComponent,		\
		  allocAndSetCurrentScene, uninitAndFreeCurrentScene,	\
		  initCurrentScene, setActiveCameraToCurrentScene,	\
		  serializeCurrentScene, deserializeToCurrentScene,	\
		  sceneNewEntity, getEntity,				\
		  removeComponent, getComponent,			\
		  createRigidBody, createBoxColliderFixture,		\
		  getEngine,						\
		  isKeyDown);						\

namespace Code{
    char dllTemp[300];
    char dll[300];

    void unload(HMODULE code){
	if(code != NULL){FreeLibrary(code);};
    };
    HMODULE cpySrcAndLoadTemp();
    void setGameCode(char *path){
	u32 len = strlen(path)+1;
	memcpy(dll, path, len);
	memcpy(dllTemp, path, len);
	u32 off = len;
	while(dllTemp[off] != '.'){off -= 1;};
	char *temp = "_temp";
	u32 tempLen = (u32)strlen(temp);
	memcpy(dllTemp+off, temp, tempLen);
	char *dotDll = ".dll";
	u32 dotDllLen = (u32)strlen(dotDll);
	memcpy(dllTemp+off+tempLen, dotDll, dotDllLen+1); //+1 for null byte

	print("Game code: %s", dll);
	print("Temp game code: %s", dllTemp);
	
	engine->gameCode = cpySrcAndLoadTemp();
	/*
	  Layer *gameLayer = engine->lm.newLayer();
	  gameLayer->onRender = (LayerFunc)GetProcAddress(engine->gameCode, "render");
	  gameLayer->onUninit = (LayerFunc)GetProcAddress(engine->gameCode, "uninit");
	  gameLayer->onUpdate = (LayerUpdateFunc)GetProcAddress(engine->gameCode, "update");
	  auto ginit = (void(*)())GetProcAddress(engine->gameCode, "init");
	  ginit();
	*/
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
	    print("[error] Copying src to temp dll file failed: %d\n", GetLastError());
	    return nullptr;
	};
	return load(dllTemp);
    };
};
