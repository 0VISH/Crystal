#include "shader.hh"

namespace Shader{
    void useShader(u32 program){
#if(GL)
	glUseProgram(program);
#endif
    };
};

void ShaderSystem::init(){
    shaderToId.init();
};
u32 ShaderSystem::newShader(char *vertexShaderPath, char *fragmentShaderPath, char *name){
    u32 program;
    String shaderName;
    shaderName.mem = name;
    shaderName.len = (u32)strlen(name);
    if(shaderToId.getValue(shaderName, &program) == true){
	print("[error] shader with name %s already exists", name);
	return 0;
    };
#if(GL)
    program = glCreateProgram();
    OpenGL::createShader(vertexShaderPath, fragmentShaderPath, program);
#endif
    shaderToId.insertValue(shaderName, program);
    return program;
};
u32 ShaderSystem::getShader(char *name){
    u32 program = 0;
    if(shaderToId.getValue({name, (u32)strlen(name)}, &program) == false){
	print("[error] shader with name %s does not exist", name);
    };
    return program;
};
void ShaderSystem::uninit(){
    for(u32 x=0; x<shaderToId.count; x+=1){
	if(shaderToId.status[x] == true){
#if(GL)
	    OpenGL::destroyShader(shaderToId.values[x]);
#endif
	};
    };
    shaderToId.uninit();
};
