#include "shader.hh"

namespace Shader{
    void useShader(u32 shader){
#if(GL)
	glUseProgram(shader);
#endif
    };
};

void ShaderSystem::init(){
    shaderToId.init();
};
u32 ShaderSystem::newShader(char *vertexShaderPath, char *fragmentShaderPath, char *name){
    String shaderName;
    shaderName.mem = name;
    shaderName.len = (u32)strlen(name);
    u32 id;
    if(shaderToId.getValue(shaderName, &id) == true){
	print("[error] shader with name %s already exists", name);
	return 0;
    };
#if(GL)
    u32 program = glCreateProgram();
    OpenGL::createShader(vertexShaderPath, fragmentShaderPath, program);
#endif
    shaderToId.insertValue(shaderName, program);
    return program;
};
u32 ShaderSystem::getShaderId(char *name){
    u32 id;
    if(shaderToId.getValue({name, (u32)strlen(name)}, &id) == false){
	print("[error] shader with name %s does not exist", name);
    };
    return id;
};
void ShaderSystem::uninit(){
    for(u32 x=0; x<shaderToId.count; x+=1){
	if(shaderToId.status[x] == true){
	    u32 shaderId = shaderToId.values[x];
#if(GL)
	    OpenGL::destroyShader(shaderId);
#endif
	};
    };
    shaderToId.uninit();
};
