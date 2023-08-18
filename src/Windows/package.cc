#include "../package.hh"

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
	map_init(&package->fileToOff);
	package->content = (char*)mem + sizeof(tableSize) + sizeof(fileCount) +tableSize;
	
	while(tableStart != tableEnd){
	    //TODO: remove null termination and use this
	    int len = *(int*)tableStart;
	    tableStart += sizeof(int);
	    char *stringMem = tableStart;
	    tableStart += len;
	    int off = *(int*)tableStart;
	    tableStart += sizeof(int);

	    map_set(&package->fileToOff, stringMem, off);
	};
    };
    char *openFileFromPkgElseFile(char *fileName, bool &fromFile, Pkg *package){
	if(package->mem != nullptr){
	    //pkg
	    int *offPtr = map_get(&package->fileToOff, fileName);
	    if(offPtr != nullptr){
		fromFile = false;
		return package->content + (*offPtr);
	    };
	};

	//file
	FILE *f = fopen(fileName, "r");
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
	fromFile = true;
	return mem;
    };
    void unloadPkg(Pkg *package){
	if(package->mem == nullptr){return;};
	map_deinit(&package->fileToOff);
	mem::free(package->mem);
    };
};
