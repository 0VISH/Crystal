#include "shaderSystem.hh"

void ShaderSystem::init(){
    shaderPrograms.init();
};
u32 ShaderSystem::newShaderProgram(){
    u32 program = glCreateProgram();
    shaderPrograms.push(program);
    return program;
};
void ShaderSystem::setCameraProjectionViewMatrix(glm::mat4 &mat){
    for(u32 x=0; x<shaderPrograms.count; x+=1){
	u32 shaderProgram = shaderPrograms[x];
	Renderer::setMat4Uniform(mat, "uProjectionView", shaderProgram);
    };
};
u32 ShaderSystem::getDefaultShader(){
    return shaderPrograms[0];
};
void ShaderSystem::uninit(){
    for(u32 x=0; x<shaderPrograms.count; x+=1){
	Shader::deleteShader(shaderPrograms[x]);
    };
    shaderPrograms.uninit();
};
