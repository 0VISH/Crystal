#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

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
