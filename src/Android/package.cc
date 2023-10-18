namespace Package{
    void allocPackages(){};
    void freePackages(){};
    void loadPkg(char *packagePath, Pkg *package){};
    char *openNormalFileFromPkgElseFile(char *fileName, bool &fromFile, Pkg *package){return "TODO:";};
    char *openImgFileFromPkgElseFile(char *fileName, s32 &width, s32 &height, s32 &nrChannels, bool &fromFile, Pkg *package){return "TODO:";};
    void unloadPkg(Pkg *package){};
};
