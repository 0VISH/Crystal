#include "../package.hh"
#include "stb_image.hh"

s32 loadTexture(char *name){
    s32 width;
    s32 height;
    bool fromFile;
    char *mem = openImgFileFromPkgElseFile(name, width, height, fromFile, Package::curPkg);
    if(mem == nullptr){return -1;};
#if(GL)
    u32 id = OpenGL::loadTexture(mem, width, height);
#endif
    if(fromFile){stbi_image_free(mem);};
    return id;
};
