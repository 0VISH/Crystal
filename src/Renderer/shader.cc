#include "renderer.hh"
#include "shader.hh"

enum class ShaderType{
    VERTEX,
    FRAGMENT,
};

namespace Shader{
    u32 compileShader(char *shaderSrc, ShaderType type){
#if(RCONTEXT_GL)
	GLenum shaderType;
	switch(type){
	case ShaderType::VERTEX: shaderType = GL_VERTEX_SHADER; break;
	case ShaderType::FRAGMENT: shaderType = GL_FRAGMENT_SHADER; break;
	};
	return OpenGL::compileShader(shaderSrc, shaderType);
#endif
    };
    void attachShaderToProgram(u32 shader, u32 program){
#if(RCONTEXT_GL)
	OpenGL::attachShaderToProgram(shader, program);
#endif
    };
    void linkProgram(u32 program){
#if(RCONTEXT_GL)
	OpenGL::linkProgram(program);
#endif
    };
    void useProgram(u32 program){
#if(RCONTEXT_GL)
	OpenGL::useProgram(program);
#endif
    };
    void deleteShader(u32 shader){
#if(RCONTEXT_GL)
	OpenGL::deleteShader(shader);
#endif
    };
};

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
