#pragma once

#include "basic.hh"
#include "ds.cc"

namespace Package{
     struct Pkg{
	HashmapStr fileToOff;
	void *mem;
	char *content;
    };

    void loadPkg(char *packagePath, Pkg *package);
    char *openNormalFile(char *fileName);
    char *openNormalFileFromPkgElseFile(char *fileName, bool &fromFile, Pkg *package);
    void unloadPkg(Pkg *package);

    Pkg *commonPkg;
    Pkg *curPkg;
};
