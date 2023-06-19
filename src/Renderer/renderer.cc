#include "renderer.hh"

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
    Renderer::Object createObject(){
	Renderer::Object obj;

	//TRIANGLE
	float triangleVertices[] = {
	    -0.5f, -0.5f,
	    0.5f, -0.5f,
	    0.0f,  0.5f,
	};
	u32 tvao, tvbo;
	glGenVertexArrays(1, &tvao);	
	glBindVertexArray(tvao);
	glGenBuffers(1, &tvbo);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	obj.triangle.vao = tvao;
	obj.triangle.vbo = tvbo;
	obj.triangle.ibo = 0;

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
	u32 qvao, qvbo, qibo;
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
	obj.quad.vao = qvao;
	obj.quad.vbo = qvbo;
	obj.quad.ibo = qibo;
	

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
	u32 shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
#if(DBG)
	OpenGL::linkCheckErr(shaderProgram);
#endif
	obj.shaderProgram = shaderProgram;
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//TODO: Package should handle this
	mem::free(fragmentShaderSource);
	mem::free(vertexShaderSource);

	return obj;
    };
    void destroyObject(Renderer::Object &obj){
	glDeleteProgram(obj.shaderProgram);
	//TRIANGLE
	glDeleteBuffers(1, &obj.triangle.vbo);
	glDeleteVertexArrays(1, &obj.triangle.vao);
	//QUAD
	glDeleteBuffers(1, &obj.quad.ibo);
	glDeleteBuffers(1, &obj.triangle.vbo);
	glDeleteVertexArrays(1, &obj.triangle.vao);
    };
    void drawTriangle(Renderer::Object &obj){
	glBindVertexArray(obj.triangle.vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
    };
    void drawQuad(Renderer::Object &obj){
	glBindVertexArray(obj.quad.vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    };
    void drawWireframe(){glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);};
    void drawFill(){glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);};
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
    Object createObject(){
#if(RCONTEXT_GL)
	return OpenGL::createObject();
#endif
    };
    void destroyObject(Object &obj){
#if(RCONTEXT_GL)
	OpenGL::destroyObject(obj);
#endif
    };
    void drawTriangle(Object &obj){
#if(RCONTEXT_GL)
	OpenGL::drawTriangle(obj);
#endif
    };
    void drawQuad(Object &obj){
#if(RCONTEXT_GL)
	OpenGL::drawQuad(obj);
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

    FuncAddr CreateAndRFA(){
	FuncAddr rfa;
    
	rfa.enableDebugMode = Renderer::enableDebugMode;
	rfa.createObject = Renderer::createObject;
	rfa.destroyObject = Renderer::destroyObject;
	rfa.drawTriangle = Renderer::drawTriangle;
	rfa.drawQuad = Renderer::drawQuad;
	rfa.drawWireframe = Renderer::drawWireframe;
	rfa.drawFill = Renderer::drawFill;

	return rfa;
    };
};
