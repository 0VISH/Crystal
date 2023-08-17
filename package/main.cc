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
	char *charMem = (char*)mem;
	charMem[size] = 0;  //NOTE: we are padding all bin files with a null byte

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
	long fileCount = 0;

	for(const auto &file : files){
	    //TODO: remove null byte
	    tableSize += sizeof(int) + strlen(file.name)+1 + sizeof(long);
	    fileCount += 1;
	};
	fwrite(&tableSize, sizeof(tableSize), 1, f);
	fwrite(&fileCount, sizeof(fileCount), 1, f);
	
	for(const auto &file : files){
	    //TODO: remove null byte
	    int len = strlen(file.name)+1;
	    fwrite(&len, sizeof(len), 1, f);
	    fwrite(file.name, len, 1, f);
	    fwrite(&bytes, sizeof(bytes), 1, f);
	    bytes += file.size + 1;
	};
	
	for(const auto &file : files){
	    //NOTE: +1 as all files are padded with a null byte
	    fwrite(file.content, file.size+1, 1, f);
	};

	printf("-----Dumped to %s with a table of size %d-----\n", packagePath, tableSize);
	fclose(f);
    };
};

int main(){
    PackageBuilder setup;
    
    setup.addFile(vertexShader);
    setup.addFile(fragmentShader);
    setup.addFile(displayVertexShader);
    setup.addFile(displayFragmentShader);

    setup.createPackage("package/setup.pkg");

    printf("\nDONE :)\n");
    return EXIT_SUCCESS;
};
