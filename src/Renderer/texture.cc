#include "../package.hh"
#include "stb_image.hh"

void bindTextureToUnit(u32 unit, u32 textureId, u32 shader){
    u32 program = engine->ss.getShaderId(shader);
#if(GL)
    OpenGL::bindTextureToUnit(unit, textureId, program);
#endif
};

u32 wid = 0;

s32 loadTexture(char *name, u32 shaderOff){
    ShaderSystem &ss = engine->ss;
    MaterialSystem *ms = engine->ms;
    u32 off = ms->textureToOff.count;
    String textName;
    textName.mem = name;
    textName.len = (u32)strlen(name);
    if(ms->textureToOff.getValue(textName, &off)){
	return off;
    };
    ms->textureToOff.insertValue(textName, off);
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
    ms->textureIds.push(tid);
    return off;
};
void initTextures(char *shaderName){
    ShaderSystem &ss = engine->ss;
    u32 off;
    if(ss.shaderToOff.getValue({shaderName, (u32)strlen(shaderName)}, &off) == false){
	print("[error] shader with name %s does not exist. Cannot init texture samplers", shaderName);
    };
    ShaderInfo &info = ss.shaderInfo[off];
    if(wid == 0){
	char whitePixel[] = {(char)255, (char)255, (char)255, (char)255};
#if(GL)
	OpenGL::initTextureSamplers(info.shaderId);
	wid = OpenGL::loadTexture(whitePixel, 1, 1, 0);
	ASSERT(wid == 1);
#endif
    };
    info.textureUnitOff = 1;
    MaterialSystem *ms = engine->ms;
    String textureName;
    textureName.mem = "white";
    textureName.len = (u32)strlen(textureName.mem);
    ms->textureToOff.insertValue(textureName,  0);
    ms->textureIds.init();
};
