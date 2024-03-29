#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hh"

namespace Package{
    void allocPackages(){
	commonPkg = (Pkg*)mem::alloc(sizeof(Pkg));
	curPkg = (Pkg*)mem::alloc(sizeof(Pkg));
    };
    void freePackages(){
	mem::free(commonPkg);
	mem::free(curPkg);
    };
    
    void loadPkg(char *packagePath, Pkg *package){
	FILE *packageFile = fopen(packagePath, "rb");
	if(packageFile == nullptr){
	    package->mem = nullptr;
	    return;
	};
	fseek(packageFile, 0, SEEK_END);
	long fsize = ftell(packageFile);
	fseek(packageFile, 0, SEEK_SET);
    
	void *mem = (char*)mem::alloc(fsize);
	fread(mem, fsize, 1, packageFile);
	fclose(packageFile);
    
	char *tableStart = (char*)mem;
	long tableSize = *(long*)tableStart;
	tableStart += sizeof(tableSize);
	//TODO: reserve the hash map with this value
	long fileCount = *(long*)tableStart;
	tableStart += sizeof(fileCount);
	char *tableEnd = tableStart + tableSize;

	package->mem = mem;
	package->fileToOff.init();
	package->content = (char*)mem + sizeof(tableSize) + sizeof(fileCount) +tableSize;
	
	while(tableStart != tableEnd){
	    //TODO: remove null termination and use this
	    int len = *(int*)tableStart;
	    tableStart += sizeof(int);
	    char *stringMem = tableStart;
	    tableStart += len;
	    u32 off = *(u32*)tableStart;
	    tableStart += sizeof(u32);

	    package->fileToOff.insertValue({stringMem, (u32)strlen(stringMem)}, off);
	};
    };
    char *openNormalFile(char *fileName){
	FILE *f = fopen(fileName, "rb");
	if(f == nullptr){
	    print("%s path does not exist", fileName);
	    return nullptr;
	};
	
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *mem = (char*)mem::calloc(fsize + 1);
	fread(mem, fsize, 1, f);
	fclose(f);

	mem[fsize] = 0;
	return mem;
    };
    char *openNormalFileFromPkgElseFile(char *fileName, bool &fromFile, Pkg *package){
	if(package != nullptr){
	    if(package->mem != nullptr){
		//pkg
	        u32 off;
		if(package->fileToOff.getValue({fileName, (u32)strlen(fileName)}, &off)){
		    fromFile = false;
		    return package->content + off;
		};
	    };
	};

	//file
	fromFile = true;
	return openNormalFile(fileName);
    };
    char *openImgFileFromPkgElseFile(char *fileName, s32 &width, s32 &height, bool &fromFile, Pkg *package){
	if(package->mem != nullptr){
	    //pkg
	    u32 off;
	    if(package->fileToOff.getValue({fileName, (u32)strlen(fileName)}, &off)){
		fromFile = false;
		s32 *mem = (s32*)(package->content + off);
		
		width = *mem;
		mem += 1;
		height = *mem;
		mem += 1;

		return (char*)mem;
	    };
	};
	s32 nrChannels;
	unsigned char *data = stbi_load(fileName, &width, &height, &nrChannels, 0);
	fromFile = true;
	return (char*)data;
    };
    void unloadPkg(Pkg *package){
	if(package->mem == nullptr){return;};
	package->fileToOff.uninit();
	mem::free(package->mem);
    };
};
