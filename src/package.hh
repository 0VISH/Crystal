#pragma once

namespace Package{
     struct Pkg{
	map_int_t fileToOff;
	void *mem;
	char *content;
    };

    void loadPkg(char *packagePath, Pkg *package);
    char *openNormalFileFromPkgElseFile(char *fileName, bool &fromFile, Pkg *package);
    void unloadPkg(Pkg *package);

    Pkg *commonPkg;
    Pkg *curPkg;
};
