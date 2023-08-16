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
	std::unordered_map<char*, long> table;
	
	for(const auto &file : files){
	    table[file.name] = ftell(f);
	    fwrite(file.content, file.size, 1, f);
	};

	long tableOff = ftell(f);
	for(const auto &pair : table){
	    int len = strlen(pair.first);
	    fwrite(&len, sizeof(len), 1, f);
	    fwrite(pair.first, len, 1, f);
	    fwrite(&pair.second, sizeof(pair.second), 1, f);
	};
	
	printf("-----Dumped to %s-----\n", packagePath);
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
    
    return EXIT_SUCCESS;
};
