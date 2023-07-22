#define SETUP_POINTERS(HANDLE)						\
    auto setupUtilPointer = (void(*)(logType l, getComponentUIDType gcut, setGameFolderType sgft))GetProcAddress(HANDLE, "setupUtilPointers"); \
    setupUtilPointer(print, getComponentUID, Code::setGameFolder);	\
									\
    auto setupPointers = (void(*)(materialInitType mit, materialUninitType mut, materialRegisterEntityType mret, \
				  materialSystemInitType msit, materialSystemUninitType msut, newMaterialType nmt, \
				  componentPoolInitType cpit, componentPoolNewComponentType cpnct, componentPoolRemoveComponentType cprct, componentPoolGetComponentType cpgct, \
				  sceneInitType sit, sceneUninitType sut, sceneNewEntityType snet, sceneGetEntityType sget, \
				  setCurrentSceneType scst, getCurrentSceneType gcst))GetProcAddress(HANDLE, "setupPointers"); \
    setupPointers(materialInit, materialUninit, materialRegisterEntity,	\
		  materialSystemInit, materialSystemUninit, newMaterial, \
		  componentPoolInit, componentPoolNewComponent, componentPoolRemoveComponent, componentPoolGetComponent, \
		  sceneInit, sceneUninit, sceneNewEntity, sceneGetEntity, \
		  setCurrentScene, getCurrentScene);			\

namespace Code{
    char buff[1024];
    
    void setGameFolder(char *path){
	u32 off = strlen(path);
	memcpy(buff, path, off);
	char *dll = "\\bin\\gameWin.dll";
	memcpy(buff+off, dll, strlen(dll));

	HMODULE gameCode = LoadLibraryA(buff);
	if(gameCode == nullptr){
	    print("Game code not found");
	    return;
	};

	SETUP_POINTERS(gameCode);

	Layer *gameLayer = engine->lm.newLayer();
	gameLayer->onRender = (LayerFunc)GetProcAddress(gameCode, "render");
	gameLayer->onUninit = (LayerFunc)GetProcAddress(gameCode, "uninit");
	gameLayer->onUpdate = (LayerUpdateFunc)GetProcAddress(gameCode, "update");
	auto ginit = (void(*)())GetProcAddress(gameCode, "init");
	ginit();
    };
};
