#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

namespace Package{
    AAssetManager* assetManager;
    
    void allocPackages(){};
    void freePackages(){};
    void loadPkg(char *packagePath, Pkg *package){};
    char *openNormalFileFromPkgElseFile(char *fileName, bool &fromFile, Pkg *package){
	fromFile = true;
	AAsset* assetFile = AAssetManager_open(assetManager, fileName, AASSET_MODE_BUFFER);
	if (assetFile != nullptr) {
	    off_t length = AAsset_getLength(assetFile);
	    char* fileContent = (char*)mem::alloc(length + 1);
	    AAsset_read(assetFile, fileContent, length);
	    AAsset_close(assetFile);
	    fileContent[length] = '\0';
	    return fileContent;
	};
	return nullptr;
    };
    char *openImgFileFromPkgElseFile(char *fileName, s32 &width, s32 &height, s32 &nrChannels, bool &fromFile, Pkg *package){return "TODO:";};
    void unloadPkg(Pkg *package){};
};
