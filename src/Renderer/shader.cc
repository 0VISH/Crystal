#include "shader.hh"

namespace Shader{
    void useShader(u32 program){
#if(GL)
	glUseProgram(program);
#endif
    };
};

void ShaderSystem::init(){
    shaderPrograms.init();
};
u32 ShaderSystem::newShader(char *vertexShaderPath, char *fragmentShaderPath){
    u32 program;
#if(GL)
    program = glCreateProgram();
    OpenGL::createShader(vertexShaderPath, fragmentShaderPath, program);
#endif
    shaderPrograms.push(program);
    return program;
};
u32 ShaderSystem::getDefaultShader(){
    return shaderPrograms[0];
};
void ShaderSystem::uninit(){
    for(u32 x=0; x<shaderPrograms.count; x+=1){
#if(GL)
	OpenGL::destroyShader(shaderPrograms[x]);
#endif
    };
    shaderPrograms.uninit();
};
