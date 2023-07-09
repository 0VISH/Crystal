//TODO: package all files under package

namespace Package{
    char *readTextFile(char *filePath){
	FILE *f = fopen(filePath, "r");

#if(DBG)
	if(f == nullptr){
	    log("%s path does not exist", filePath);
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
