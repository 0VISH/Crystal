#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <unordered_map>

char *vertexShader   = "package/shader/vertex.glsl";
char *fragmentShader = "package/shader/fragment.glsl";
char *displayVertexShader   = "package/shader/displayVertex.glsl";
char *displayFragmentShader = "package/shader/displayFragment.glsl";

struct File{
    int   size;
    char *name;
    void *content;
};
struct TableEntry{
    char *name;
    int   off;
};
struct PackageBuilder{
    std::vector<File> files;
    int   errorCount = 0;

    void addFile(char *filePath){
	FILE *f = fopen(filePath, "rb");
	if(f == nullptr){
	    printf("Invalid filepath: %s\n", filePath);
	    errorCount += 1;
	    return;
	};

	File file;
    
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f, 0, SEEK_SET);

	void *mem = malloc(size);
	fread(mem, size, 1, f);
	fclose(f);

	file.name = filePath;
	file.content = mem;
	file.size = size;
	files.push_back(file);
	
	printf("%s\n", filePath);
    };
    void createPackage(char *packagePath){
	if(errorCount != 0){
	    printf("\nerrorCount: %d\n", errorCount);
	    return;
	};

	FILE *f = fopen(packagePath, "wb");
	long bytes = 0;
	long tableSize = 0;

	for(const auto &file : files){
	    tableSize += sizeof(int) + strlen(file.name) + sizeof(long);
	};
	fwrite(&tableSize, sizeof(tableSize), 1, f);
	
	for(const auto &file : files){
	    int len = strlen(file.name);
	    fwrite(&len, sizeof(len), 1, f);
	    fwrite(file.name, len, 1, f);
	    fwrite(&bytes, sizeof(bytes), 1, f);
	    bytes += file.size;
	};
	
	for(const auto &file : files){
	    fwrite(file.content, file.size, 1, f);
	};

	printf("-----Dumped to %s with a table of size %d-----\n", packagePath, tableSize);
	fclose(f);
    };
};

void loadPackage(char *packagePath){
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
    char *tableEnd = tableStart + tableSize;

    while(tableStart != tableEnd){
	int len = *(int*)tableStart;
	tableStart += sizeof(int);
	char *stringMem = tableStart;
	tableStart += len;
	int off = *(int*)tableStart;
	tableStart += sizeof(int);

	printf("%.*s: %d\n", len, stringMem, off);
    };

    free(mem);
};

int main(){
    PackageBuilder setup;
    
    setup.addFile(vertexShader);
    setup.addFile(fragmentShader);
    setup.addFile(displayVertexShader);
    setup.addFile(displayFragmentShader);

    setup.createPackage("package/setup.pkg");

    loadPackage("package/setup.pkg");

    printf("\nDONE :)\n");
    return EXIT_SUCCESS;
};
