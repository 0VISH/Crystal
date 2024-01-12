#if(WIN)
#include "../../vendor/glad/include/glad/glad.h"
#elif(ANDROID)
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#endif
#include "renderer.hh"

//NOTE: debug stuff
namespace OpenGL{
#if(WIN)
    void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
	//https://learnopengl.com/In-Practice/Debugging
	if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

	printf("------[OPENGL ERROR]---------\n");
	printf("%s\n", message);

	switch (source)
	    {
	    case GL_DEBUG_SOURCE_API:             printf("Source: API"); break;
	    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   printf("Source: Window System"); break;
	    case GL_DEBUG_SOURCE_SHADER_COMPILER: printf("Source: Shader Compile"); break;
	    case GL_DEBUG_SOURCE_THIRD_PARTY:     printf("Source: Third Party"); break;
	    case GL_DEBUG_SOURCE_APPLICATION:     printf("Source: Application"); break;
	    case GL_DEBUG_SOURCE_OTHER:           printf("Source: Other"); break;
	    };
	switch (type)
	    {
	    case GL_DEBUG_TYPE_ERROR:               printf("Type: Error"); break;
	    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: printf("Type: Deprecated Behaviour"); break;
	    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  printf("Type: Undefined Behaviour"); break; 
	    case GL_DEBUG_TYPE_PORTABILITY:         printf("Type: Portability"); break;
	    case GL_DEBUG_TYPE_PERFORMANCE:         printf("Type: Performance"); break;
	    case GL_DEBUG_TYPE_MARKER:              printf("Type: Marker"); break;
	    case GL_DEBUG_TYPE_PUSH_GROUP:          printf("Type: Push Group"); break;
	    case GL_DEBUG_TYPE_POP_GROUP:           printf("Type: Pop Group"); break;
	    case GL_DEBUG_TYPE_OTHER:               printf("Type: Other"); break;
	    };
	switch (severity)
	    {
	    case GL_DEBUG_SEVERITY_HIGH:         printf("Severity: high"); break;
	    case GL_DEBUG_SEVERITY_MEDIUM:       printf("Severity: medium"); break;
	    case GL_DEBUG_SEVERITY_LOW:          printf("Severity: low"); break;
	    case GL_DEBUG_SEVERITY_NOTIFICATION: printf("Severity: notification"); break;
	    };
	printf("\n");
    }
#endif
    bool vertexCheckErr(u32 shader){
	s32  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success){
	    glGetShaderInfoLog(shader, 512, NULL, infoLog);
	    printf("[VERTEX SHADER ERROR]: %s\n", infoLog);
	    return false;
	};
	return true;
    };
    bool fragmentCheckErr(u32 shader){
	s32  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success){
	    glGetShaderInfoLog(shader, 512, NULL, infoLog);
	    printf("[FRAGMENT SHADER ERROR]: %s\n", infoLog);
	    return false;
	};
	return true;
    };
    bool linkCheckErr(u32 shaderProgram){
	s32  success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
	    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	    printf("[SHADER LINK ERROR]: %s\n", infoLog);
	    return false;
	}
	return true;
    };
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
	if(OpenGL::vertexCheckErr(vertexShader) == false){printf("VERTEX_SHADER_PATH: %s", vertexShaderPath);};
	
	u32 fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
	if(OpenGL::fragmentCheckErr(fragmentShader) == false){printf("FRAGMENT_SHADER_PATH: %s", fragmentShaderPath);};
	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	OpenGL::linkCheckErr(shaderProgram);

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
#if(WIN)
    void enableDebugMode(){
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OpenGL::DebugCallback, nullptr);
    };
#else
    void enableDebugMode(){};
#endif
};

namespace OpenGL{
    ScreenQuad initScreenQuad(){
	ScreenQuad sq;
	glGenVertexArrays(1, &sq.vao);	
	glBindVertexArray(sq.vao);
	
	f32 vertices[] = {  
	   // positions   // texCoords
	   -1.0f,  1.0f,  0.0f, 1.0f,
	   -1.0f, -1.0f,  0.0f, 0.0f,
	    1.0f, -1.0f,  1.0f, 0.0f,

	   -1.0f,  1.0f,  0.0f, 1.0f,
	    1.0f, -1.0f,  1.0f, 0.0f,
	    1.0f,  1.0f,  1.0f, 1.0f
	};
	glGenBuffers(1, &sq.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, sq.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(f32), (const void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(f32), (const void*)(2*sizeof(f32)));
	glEnableVertexAttribArray(1);
	
	return sq;
    };
    void uninitScreenQuad(ScreenQuad &sq){
	glDeleteBuffers(1, &sq.vbo);
	glDeleteVertexArrays(1, &sq.vao);
    };
    void drawWireframe(){/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/};
    void drawFill(){/*glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);*/};
    void setMat4Uniform(glm::mat4 &mat, char *uniformName, u32 shaderProgram){
	s32 uLoc = glGetUniformLocation(shaderProgram, uniformName);
	glUniformMatrix4fv(uLoc, 1, GL_FALSE, glm::value_ptr(mat));
    };
    void setVec4Uniform(glm::vec4 &vec, char *uniformName, u32 shaderProgram){
	s32 uLoc = glGetUniformLocation(shaderProgram, uniformName);
	glUniform4f(uLoc, vec[0], vec[1], vec[2], vec[3]);
    };
    void clearColourBuffer(){glClear(GL_COLOR_BUFFER_BIT);};
    u32 loadTexture(char *data, u32 width, u32 height, u32 textureUnit){
	u32 id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTextureUnit(textureUnit, id); 
	return id;
    };
    
    void init(Renderer &r){
	glGenVertexArrays(1, &r.qvao);	
	glBindVertexArray(r.qvao);
	glGenBuffers(1, &r.qvbo);
	glBindBuffer(GL_ARRAY_BUFFER, r.qvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Draw::Vertex) * Draw::maxVertexCount, nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Draw::Vertex), (const void*)offsetof(Draw::Vertex, pos));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Draw::Vertex), (const void*)offsetof(Draw::Vertex, col));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Draw::Vertex), (const void*)offsetof(Draw::Vertex, textPos));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, sizeof(Draw::Vertex), (const void*)offsetof(Draw::Vertex, textID));
	glEnableVertexAttribArray(3);

	//fill up our entire index buffer
	u32 *indices = (u32*)mem::alloc(sizeof(u32) * Draw::maxIndexCount);
	u32 offset = 0;
	for(u32 i=0; i<Draw::maxIndexCount; i+=6){
	    indices[i + 0] = 0 + offset;
	    indices[i + 1] = 1 + offset;
	    indices[i + 2] = 3 + offset;
	    indices[i + 3] = 1 + offset;
	    indices[i + 4] = 2 + offset;
	    indices[i + 5] = 3 + offset;

	    offset += 4;
	};
	glGenBuffers(1, &r.qibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r.qibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * Draw::maxIndexCount, indices, GL_STATIC_DRAW);
	mem::free(indices);
    };
    void initTextureSamplers(u32 shader){
	glUseProgram(shader);
	u32 loc = glGetUniformLocation(shader, "textures");
	s32 samplers[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	glUniform1iv(loc, 10, samplers);
    };

    void uninit(Renderer &r){
	glDeleteBuffers(1, &r.qibo);
	glDeleteBuffers(1, &r.qvbo);
	glDeleteVertexArrays(1, &r.qvao);
    };
    void bindTextureToUnit(u32 unit, u32 textureId, u32 shader){
	glUseProgram(shader);
	glBindTextureUnit(unit, textureId);
    };
    void batchAndDraw(Renderer &r, void *begin, void *end){
	u32 size = (char*)end - (char*)begin;
	
	glBindBuffer(GL_ARRAY_BUFFER, r.qvbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, begin);
	
	glBindVertexArray(r.qvao);
	glDrawElements(GL_TRIANGLES, r.indexCount, GL_UNSIGNED_INT, 0);

	r.drawCalls += 1;
	r.indexCount = 0;
    };
};
