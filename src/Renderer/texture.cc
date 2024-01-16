#include "../package.hh"
#include "stb_image.hh"

void bindTextureToUnit(u32 unit, u32 textureId){
#if(GL)
    OpenGL::bindTextureToUnit(unit, textureId);
#endif
};

s32 loadTexture(char *name, u32 shaderOff){
    ShaderSystem &ss = engine->ss;
    MaterialSystem *ms = engine->ms;
    u32 off = engine->textures.count;
    String textName;
    textName.mem = name;
    textName.len = (u32)strlen(name);
    if(engine->textures.getValue(textName, &off)){
	return off;
    };
    s32 width;
    s32 height;
    bool fromFile;
    char *mem = openImgFileFromPkgElseFile(name, width, height, fromFile, Package::curPkg);
    if(mem == nullptr){return -1;};
    char redPixel[] = {(char)255, (char)0, (char)0, (char)255};
#if(GL)
    u32 tid = OpenGL::loadTexture(redPixel, 1, 1);
    gid = tid;
#endif
#if(GL)
    //u32 tid = OpenGL::loadTexture(mem, width, height);
#endif
    if(fromFile){stbi_image_free(mem);};
    String str;
    str.len = (u32)strlen(name) + 1;
    str.mem = (char*)mem::alloc(str.len);
    memcpy(str.mem, name, str.len);
    engine->textures.insertValue(str, engine->textures.count);
    engine->textureIds.push(tid);
    return off;
};
void initTextures(char *shaderName){
    ShaderSystem &ss = engine->ss;
    u32 id;
    if(ss.shaderToId.getValue({shaderName, (u32)strlen(shaderName)}, &id) == false){
	print("[error] shader with name %s does not exist. Cannot init texture samplers", shaderName);
	return;
    };
#if(GL)
    OpenGL::initTextureSamplers(id);
#endif
};
u32 loadWhiteTexture(){
    char whitePixel[] = {(char)255, (char)255, (char)255, (char)255};
#if(GL)
    return OpenGL::loadTexture(whitePixel, 1, 1);
#endif
};
