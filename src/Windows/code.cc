#include "../setupPointers.hh"

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
	print("Game code: %s", dll);
	memcpy(dllTemp, path, len);
	u32 off = len;
	while(dllTemp[off] != '.'){off -= 1;};
	char *temp = "_temp";
	u32 tempLen = (u32)strlen(temp);
	memcpy(dllTemp+off, temp, tempLen);
	char *dotDll = ".dll";
	u32 dotDllLen = (u32)strlen(dotDll);
	memcpy(dllTemp+off+tempLen, dotDll, dotDllLen+1); //+1 for null byte
	print("Temp game code: %s", dllTemp);
	engine->gameCode = cpySrcAndLoadTemp();
    };
    HMODULE load(char *path){
	HMODULE code = LoadLibraryA(path);
	if(code == nullptr){return nullptr;};
	GET_POINTERS(code);
	SET_POINTERS;
	return code;
    };
    HMODULE cpySrcAndLoadTemp(){
	BOOL b = CopyFile(dll, dllTemp, 0);
	if(!b){
	    print("[error] Copying src to temp dll file failed: %d\n", GetLastError());
	    print("[error] src: %s", dll);
	    print("[error] dst: %s", dllTemp);
	    return nullptr;
	};
	return load(dllTemp);
    };
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
