#pragma once

namespace Package{
     struct Pkg{
	map_int_t fileToOff;
	void *mem;
	char *content;
    };

    void loadPkg(char *packagePath);
    char *openFileFromPkgElseFile(char *fileName);
    void unloadPkg();
};
