#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

#if(RCONTEXT_GL)
namespace OpenGL{
#if(DBG)
    void enableDebugMode(){
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OpenGL::DebugCallback, nullptr);
    };
#endif
    void createDefaultShader(u32 &shaderProgram){
	//SHADER
	u32 vertexShader = Shader::compileShader("package/shader/vertex.glsl", ShaderType::VERTEX);
#if(DBG)
	OpenGL::vertexCheckErr(vertexShader);
#endif
	u32 fragmentShader = Shader::compileShader("package/shader/fragment.glsl", ShaderType::FRAGMENT);
#if(DBG)
	OpenGL::fragmentCheckErr(fragmentShader);
#endif
	Shader::attachShaderToProgram(vertexShader, shaderProgram);
	Shader::attachShaderToProgram(fragmentShader, shaderProgram);
	Shader::linkProgram(shaderProgram);
#if(DBG)
	OpenGL::linkCheckErr(shaderProgram);
#endif
	Shader::useProgram(shaderProgram);
	Shader::deleteShader(vertexShader);
	Shader::deleteShader(fragmentShader);
    };
    void drawWireframe(){glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);};
    void drawFill(){glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);};
    void setMat4Uniform(glm::mat4 &mat, char *uniformName, u32 shaderProgram){
	s32 uLoc = glGetUniformLocation(shaderProgram, uniformName);
	glUniformMatrix4fv(uLoc, 1, GL_FALSE, glm::value_ptr(mat));
    };
    void setVec4Uniform(glm::vec4 &vec, char *uniformName, u32 shaderProgram){
	s32 uLoc = glGetUniformLocation(shaderProgram, uniformName);
	glUniform4f(uLoc, vec[0], vec[1], vec[2], vec[3]);
    };
    void clearColourBuffer(){glClear(GL_COLOR_BUFFER_BIT);};
};
#endif

namespace Renderer{
#if(DBG)
    void enableDebugMode(){
#if(RCONTEXT_GL)
	OpenGL::enableDebugMode();
#endif
    };
#endif
    void createDefaultShader(u32 &shaderProgram){
#if(RCONTEXT_GL)
	OpenGL::createDefaultShader(shaderProgram);
#endif
    };
    void drawWireframe(){
#if(RCONTEXT_GL)
	OpenGL::drawWireframe();
#endif
    };
    void drawFill(){
#if(RCONTEXT_GL)
	OpenGL::drawFill();
#endif
    };
    void setMat4Uniform(glm::mat4 &mat, char *uniformName, u32 shader){
#if(RCONTEXT_GL)
	OpenGL::setMat4Uniform(mat, uniformName, shader);
#endif
    };
    void setVec4Uniform(glm::vec4 &vec, char *uniformName, u32 shader){
#if(RCONTEXT_GL)
	OpenGL::setVec4Uniform(vec, uniformName, shader);
#endif
    };
    char *getRenderContextInfoString(){
#if(RCONTEXT_GL)
	return (char*)glGetString(GL_VERSION);
#endif
    };
    void clearColourBuffer(){
#if(RCONTEXT_GL)
	OpenGL::clearColourBuffer();
#endif
    };
};
