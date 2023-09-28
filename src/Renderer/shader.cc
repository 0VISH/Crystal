#include "shader.hh"

namespace Shader{
    u32 compileShader(char *shaderSrc, GLenum type){
	bool fromFile;
	char *src = Package::openNormalFileFromPkgElseFile(shaderSrc, fromFile, Package::curPkg);
	ASSERT(src);
	u32 shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	if(fromFile){mem::free(src);};
	return shader;
    };
    void createShader(char *vertexShaderPath, char *fragmentShaderPath, u32 shaderProgram){
	//SHADER
	u32 vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
#if(DBG)
	OpenGL::vertexCheckErr(vertexShader);
#endif
	u32 fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
#if(DBG)
	OpenGL::fragmentCheckErr(fragmentShader);
#endif
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
#if(DBG)
	OpenGL::linkCheckErr(shaderProgram);
#endif
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
    };
    void destroyShader(u32 shaderProgram){
	glDeleteProgram(shaderProgram);
    };
    void useShader(u32 shaderProgram){
	glUseProgram(shaderProgram);
    };
};

void ShaderSystem::init(){
    shaderPrograms.init();
};
u32 ShaderSystem::newShaderProgram(){
    u32 program;
#if(GL)
    program = glCreateProgram();
#endif
    shaderPrograms.push(program);
    return program;
};
u32 ShaderSystem::getDefaultShader(){
    return shaderPrograms[0];
};
void ShaderSystem::uninit(){
    for(u32 x=0; x<shaderPrograms.count; x+=1){
	Shader::destroyShader(shaderPrograms[x]);
    };
    shaderPrograms.uninit();
};
