#if(RCONTEXT_GL)
#include "../../vendor/glad/include/glad/glad.h"
#if(DBG)
#include "debugGL.cc"
#endif
#endif

enum class ShaderType{
    VERTEX,
    FRAGMENT,
};

namespace Shader{
    u32 compileShader(char *shaderSrc, ShaderType type){
	char *src = Package::readTextFile(shaderSrc);
	GLenum shaderType;
	switch(type){
	case ShaderType::VERTEX: shaderType = GL_VERTEX_SHADER; break;
	case ShaderType::FRAGMENT: shaderType = GL_FRAGMENT_SHADER; break;
	};
	u32 shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);
	//TODO: Package should handle this
	mem::free(src);
	return shader;
    };
    void attachShaderToProgram(u32 shader, u32 program){
	glAttachShader(program, shader);
    };
    void linkProgram(u32 program){
	glLinkProgram(program);
    };
    void useProgram(u32 program){
	glUseProgram(program);
    };
    void deleteShader(u32 shader){
	glDeleteShader(shader);
    };
};
