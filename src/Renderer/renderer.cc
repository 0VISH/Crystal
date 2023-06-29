#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

#if(RCONTEXT_GL)
#include "../../vendor/glad/include/glad/glad.h"
#if(DBG)
#include "Renderer/debugGL.cc"
#endif

namespace OpenGL{
#if(DBG)
    void enableDebugMode(){
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OpenGL::DebugCallback, nullptr);
    };
#endif
    void init(u32 &qvao, u32 &qvbo, u32 &qibo, u32 &shaderProgram){
	//QUAD
	float quadVertices[] = {
	    0.5f,  0.5f,
	    0.5f, -0.5f,
	    -0.5f, -0.5f,
	    -0.5f,  0.5f,
	};
	u32 quadIndices[] = {
	    0, 1, 3,
	    1, 2, 3
	};
	glGenVertexArrays(1, &qvao);	
	glBindVertexArray(qvao);
	glGenBuffers(1, &qvbo);
	glBindBuffer(GL_ARRAY_BUFFER, qvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &qibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, qibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW); 

	//SHADER
	char *vertexShaderSource = Package::readTextFile("package/shader/vertex.glsl");
	char *fragmentShaderSource = Package::readTextFile("package/shader/fragment.glsl");
	u32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
#if(DBG)
	OpenGL::vertexCheckErr(vertexShader);
#endif
	u32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
#if(DBG)
	OpenGL::fragmentCheckErr(fragmentShader);
#endif
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
#if(DBG)
	OpenGL::linkCheckErr(shaderProgram);
#endif
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//TODO: Package should handle this
	mem::free(fragmentShaderSource);
	mem::free(vertexShaderSource);
    };
    void destroyShader(u32 shaderProgram){
	glDeleteProgram(shaderProgram);
    };
    void destroyQuad(u32 &vao, u32 &vbo, u32 &ibo){
	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
    };
    void drawQuad(u32 vao){
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
};
#endif

struct Renderer{
#if(DBG)
    void enableDebugMode(){
#if(RCONTEXT_GL)
	OpenGL::enableDebugMode();
#endif
    };
#endif
    void init(){
#if(RCONTEXT_GL)
	OpenGL::init(qvao, qvbo, qibo, shaderProgram);
#endif
    };
    void uninit(){
#if(RCONTEXT_GL)
	OpenGL::destroyShader(shaderProgram);
	OpenGL::destroyQuad(qvao, qvbo, qibo);
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
    void setMat4Uniform(glm::mat4 &mat, char *uniformName){
#if(RCONTEXT_GL)
	OpenGL::setMat4Uniform(mat, uniformName, shaderProgram);
#endif
    };
    void drawQuad(glm::mat4 &mat){
	setMat4Uniform(mat, "uModel");
#if(RCONTEXT_GL)
	OpenGL::drawQuad(qvao);
#endif
    };
    void setVec4Uniform(glm::vec4 &vec, char *uniformName){
#if(RCONTEXT_GL)
	OpenGL::setVec4Uniform(vec, uniformName, shaderProgram);
#endif
    };
    void useMaterial(Material &mat){
	setVec4Uniform(mat.col, "uCol");
    };

    u32 shaderProgram;
#if(RCONTEXT_GL)
    u32 qvao;
#endif
    u32 qvbo;
    u32 qibo;
};
