//TODO: package all files under package

namespace Package{
    struct Pkg{
	map_int_t fileToOff;
	void *mem;
	char *content;
    };
    
    Pkg loadPackage(char *packagePath){
	FILE *packageFile = fopen(packagePath, "rb");
	fseek(packageFile, 0, SEEK_END);
	long fsize = ftell(packageFile);
	fseek(packageFile, 0, SEEK_SET);
    
	void *mem = (char*)malloc(fsize);
	fread(mem, fsize, 1, packageFile);
	fclose(packageFile);
    
	char *tableStart = (char*)mem;
	long tableSize = *(long*)tableStart;
	tableStart += sizeof(tableSize);
	//TODO: reserve the hash map with this value
	long fileCount = *(long*)tableStart;
	tableStart += sizeof(fileCount);
	char *tableEnd = tableStart + tableSize;

	Pkg package;
	package.mem = mem;
	map_init(&package.fileToOff);
	package.content = (char*)mem + sizeof(tableSize) + sizeof(fileCount) +tableSize;
	
	while(tableStart != tableEnd){
	    //TODO: remove null termination and use this
	    int len = *(int*)tableStart;
	    tableStart += sizeof(int);
	    char *stringMem = tableStart;
	    printf("%s\n", stringMem);
	    tableStart += len;
	    int off = *(int*)tableStart;
	    tableStart += sizeof(int);

	    map_set(&package.fileToOff, stringMem, off);
	};

	return package;
    };
    char *openFileFromPkg(char *fileName, Pkg &pkg){
	int *offPtr = map_get(&pkg.fileToOff, fileName);
	if(offPtr == nullptr){return nullptr;};
	return pkg.content + (*offPtr);
    };
    
    char *readTextFile(char *filePath){
	FILE *f = fopen(filePath, "r");

#if(DBG)
	if(f == nullptr){
	    print("%s path does not exist", filePath);
	    return nullptr;
	};
#endif
	
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *mem = (char*)mem::calloc(fsize + 1);
	fread(mem, fsize, 1, f);
	fclose(f);

	mem[fsize] = 0;
	return mem;
    };
};
