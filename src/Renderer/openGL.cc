#include "../../vendor/glad/include/glad/glad.h"
#include "renderer.hh"

//NOTE: debug stuff
namespace OpenGL{
#if(DBG)
    void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
	//https://learnopengl.com/In-Practice/Debugging
	if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

	print("------[OPENGL ERROR]---------\n");
	print("%s\n", message);

	switch (source)
	    {
	    case GL_DEBUG_SOURCE_API:             print("Source: API"); break;
	    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   print("Source: Window System"); break;
	    case GL_DEBUG_SOURCE_SHADER_COMPILER: print("Source: Shader Compile"); break;
	    case GL_DEBUG_SOURCE_THIRD_PARTY:     print("Source: Third Party"); break;
	    case GL_DEBUG_SOURCE_APPLICATION:     print("Source: Application"); break;
	    case GL_DEBUG_SOURCE_OTHER:           print("Source: Other"); break;
	    };
	switch (type)
	    {
	    case GL_DEBUG_TYPE_ERROR:               print("Type: Error"); break;
	    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: print("Type: Deprecated Behaviour"); break;
	    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  print("Type: Undefined Behaviour"); break; 
	    case GL_DEBUG_TYPE_PORTABILITY:         print("Type: Portability"); break;
	    case GL_DEBUG_TYPE_PERFORMANCE:         print("Type: Performance"); break;
	    case GL_DEBUG_TYPE_MARKER:              print("Type: Marker"); break;
	    case GL_DEBUG_TYPE_PUSH_GROUP:          print("Type: Push Group"); break;
	    case GL_DEBUG_TYPE_POP_GROUP:           print("Type: Pop Group"); break;
	    case GL_DEBUG_TYPE_OTHER:               print("Type: Other"); break;
	    };
	switch (severity)
	    {
	    case GL_DEBUG_SEVERITY_HIGH:         print("Severity: high"); break;
	    case GL_DEBUG_SEVERITY_MEDIUM:       print("Severity: medium"); break;
	    case GL_DEBUG_SEVERITY_LOW:          print("Severity: low"); break;
	    case GL_DEBUG_SEVERITY_NOTIFICATION: print("Severity: notification"); break;
	    };
    }

    void vertexCheckErr(u32 shader){
	s32  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success){
	    glGetShaderInfoLog(shader, 512, NULL, infoLog);
	    print("[VERTEX SHADER ERROR]: %s\n", infoLog);
	};
    };
    void fragmentCheckErr(u32 shader){
	s32  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success){
	    glGetShaderInfoLog(shader, 512, NULL, infoLog);
	    print("[FRAGMENT SHADER ERROR]: %s\n", infoLog);
	};
    };
    void linkCheckErr(u32 shaderProgram){
	s32  success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
	    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	    print("[SHADER LINK ERROR]: %s\n", infoLog);
	}
    };
    void enableDebugMode(){
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OpenGL::DebugCallback, nullptr);
    };
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

    void uninit(Renderer &r){
	glDeleteBuffers(1, &r.qibo);
	glDeleteBuffers(1, &r.qvbo);
	glDeleteVertexArrays(1, &r.qvao);
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
