#include "../package.hh"
#include "stb_image.hh"

void bindTextureToUnit(u32 unit, u32 textureId, u32 shader){
#if(GL)
    OpenGL::bindTextureToUnit(unit, textureId, shader);
#endif
};
s32 loadTexture(char *name, u32 shaderOff){
    ShaderSystem &ss = engine->ss;
    MaterialSystem *ms = engine->ms;
    u32 id = ms->textureToId.count;
    String textName;
    textName.mem = name;
    textName.len = (u32)strlen(name);
    if(ms->textureToId.getValue(textName, &id)){
	return id;
    };
    ms->textureToId.insertValue(textName, id);
    s32 width;
    s32 height;
    bool fromFile;
    char *mem = openImgFileFromPkgElseFile(name, width, height, fromFile, Package::curPkg);
    if(mem == nullptr){return -1;};
#if(GL)
    u32 tid = OpenGL::loadTexture(mem, width, height, 0);
#endif
    ShaderInfo &info = ss.shaderInfo[shaderOff];
    bindTextureToUnit(info.textureUnitOff, tid, info.shaderId);
    info.textureUnitOff += 1;
    if(fromFile){stbi_image_free(mem);};
    return id;
};
void initTextures(char *shaderName){
    ShaderSystem &ss = engine->ss;
    u32 off;
    if(ss.shaderToOff.getValue({shaderName, (u32)strlen(shaderName)}, &off) == false){
	print("[error] shader with name %s does not exist. Cannot init texture samplers", shaderName);
    };
    ShaderInfo &info = ss.shaderInfo[off];
    char whitePixel[] = {(char)255, (char)255, (char)255, (char)255};
#if(GL)
    OpenGL::initTextureSamplers(info.shaderId);
    u32 wid = OpenGL::loadTexture(whitePixel, 1, 1, 0);
    ASSERT(wid == 1);
#endif
    bindTextureToUnit(0, wid, info.shaderId);
    info.textureUnitOff = 1;
};
