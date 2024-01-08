#include "shader.hh"

namespace Shader{
    void useShader(u32 shader){
	u32 program = engine->ss.getShaderId(shader);
#if(GL)
	glUseProgram(program);
#endif
    };
};

void ShaderSystem::init(){
    off = 0;
    shaderToOff.init();
    const u32 size = sizeof(ShaderInfo)*5;
    shaderInfo = (ShaderInfo*)mem::alloc(size);
};
u32 ShaderSystem::newShader(char *vertexShaderPath, char *fragmentShaderPath, char *name){
    String shaderName;
    shaderName.mem = name;
    shaderName.len = (u32)strlen(name);
    u32 offset = off;
    if(shaderToOff.getValue(shaderName, &offset) == true){
	print("[error] shader with name %s already exists", name);
	return 0;
    };
    off += 1;
#if(GL)
    u32 program = glCreateProgram();
    OpenGL::createShader(vertexShaderPath, fragmentShaderPath, program);
#endif
    ShaderInfo &info = shaderInfo[offset];
    info.shaderId = program;
    info.textureUnitOff = 0;
    shaderToOff.insertValue(shaderName, offset);
    return offset;
};
u32 ShaderSystem::getShaderId(char *name){
    u32 off;
    if(shaderToOff.getValue({name, (u32)strlen(name)}, &off) == false){
	print("[error] shader with name %s does not exist", name);
    };
    return shaderInfo[off].shaderId;
};
u32 ShaderSystem::getShaderId(u32 shader){
    return shaderInfo[shader].shaderId;
};
void ShaderSystem::uninit(){
    for(u32 x=0; x<shaderToOff.count; x+=1){
	if(shaderToOff.status[x] == true){
	    u32 shaderId = shaderInfo[shaderToOff.values[x]].shaderId;
#if(GL)
	    OpenGL::destroyShader(shaderId);
#endif
	};
    };
    shaderToOff.uninit();
    mem::free(shaderInfo);
};
