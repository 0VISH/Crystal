#include "../../vendor/glad/include/glad/glad.h"

//NOTE: debug stuff
namespace OpenGL{
#if(DBG)
    void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
	//https://learnopengl.com/In-Practice/Debugging
	if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

	log("------[OPENGL ERROR]---------\n");
	log("%s\n", message);

	switch (source)
	    {
	    case GL_DEBUG_SOURCE_API:             log("Source: API"); break;
	    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   log("Source: Window System"); break;
	    case GL_DEBUG_SOURCE_SHADER_COMPILER: log("Source: Shader Compile"); break;
	    case GL_DEBUG_SOURCE_THIRD_PARTY:     log("Source: Third Party"); break;
	    case GL_DEBUG_SOURCE_APPLICATION:     log("Source: Application"); break;
	    case GL_DEBUG_SOURCE_OTHER:           log("Source: Other"); break;
	    };
	log("\n");
	switch (type)
	    {
	    case GL_DEBUG_TYPE_ERROR:               log("Type: Error"); break;
	    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: log("Type: Deprecated Behaviour"); break;
	    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  log("Type: Undefined Behaviour"); break; 
	    case GL_DEBUG_TYPE_PORTABILITY:         log("Type: Portability"); break;
	    case GL_DEBUG_TYPE_PERFORMANCE:         log("Type: Performance"); break;
	    case GL_DEBUG_TYPE_MARKER:              log("Type: Marker"); break;
	    case GL_DEBUG_TYPE_PUSH_GROUP:          log("Type: Push Group"); break;
	    case GL_DEBUG_TYPE_POP_GROUP:           log("Type: Pop Group"); break;
	    case GL_DEBUG_TYPE_OTHER:               log("Type: Other"); break;
	    };
	log("\n");
	switch (severity)
	    {
	    case GL_DEBUG_SEVERITY_HIGH:         log("Severity: high"); break;
	    case GL_DEBUG_SEVERITY_MEDIUM:       log("Severity: medium"); break;
	    case GL_DEBUG_SEVERITY_LOW:          log("Severity: low"); break;
	    case GL_DEBUG_SEVERITY_NOTIFICATION: log("Severity: notification"); break;
	    };
	log("\n");
    }

    void vertexCheckErr(u32 shader){
	s32  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success){
	    glGetShaderInfoLog(shader, 512, NULL, infoLog);
	    log("[VERTEX SHADER ERROR]: %s\n", infoLog);
	};
    };
    void fragmentCheckErr(u32 shader){
	s32  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success){
	    glGetShaderInfoLog(shader, 512, NULL, infoLog);
	    log("[FRAGMENT SHADER ERROR]: %s\n", infoLog);
	};
    };
    void linkCheckErr(u32 shaderProgram){
	s32  success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
	    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	    log("[SHADER LINK ERROR]: %s\n", infoLog);
	}
    };
    void enableDebugMode(){
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OpenGL::DebugCallback, nullptr);
    };
#endif
};

namespace OpenGL{
    u32 compileShader(char *shaderSrc, GLenum type){
	char *src = Package::readTextFile(shaderSrc);
	u32 shader = glCreateShader(type);
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
    void createDefaultShader(u32 &shaderProgram){
	//SHADER
	u32 vertexShader = OpenGL::compileShader("package/shader/vertex.glsl", GL_VERTEX_SHADER);
#if(DBG)
	OpenGL::vertexCheckErr(vertexShader);
#endif
	u32 fragmentShader = OpenGL::compileShader("package/shader/fragment.glsl", GL_FRAGMENT_SHADER);
#if(DBG)
	OpenGL::fragmentCheckErr(fragmentShader);
#endif
	OpenGL::attachShaderToProgram(vertexShader, shaderProgram);
	OpenGL::attachShaderToProgram(fragmentShader, shaderProgram);
	OpenGL::linkProgram(shaderProgram);
#if(DBG)
	OpenGL::linkCheckErr(shaderProgram);
#endif
	OpenGL::useProgram(shaderProgram);
	OpenGL::deleteShader(vertexShader);
	OpenGL::deleteShader(fragmentShader);
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
