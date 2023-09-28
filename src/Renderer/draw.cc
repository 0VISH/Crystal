#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "renderer.hh"

#include <math.h>

namespace Draw{
    void init(Renderer &r){
	r.renderBuffer = (Draw::Vertex*)mem::alloc(sizeof(glm::mat4) + sizeof(Vertex) * maxVertexCount);
	r.watermark = r.renderBuffer;
	r.bufferEmpty = true;
	r.drawCalls = 0;
#if(GL)
	OpenGL::init(r);
#if(DBG)
	OpenGL::enableDebugMode();
#endif

#endif
    };
    void uninit(Renderer &r){
	mem::free(r.renderBuffer);
#if(GL)
	OpenGL::uninit(r);
#endif
    };
    void draw(Renderer &r){
	if(r.bufferEmpty){return;};
	Draw::Vertex *x = r.renderBuffer + (u32)ceil((f64)sizeof(glm::mat4)/(f64)sizeof(Draw::Vertex));
	u32 curShader = x->pos.x;
	Shader::useShader(curShader);
	while(x != r.watermark){
	    Draw::Vertex *info = x;
	    if(info->pos.x != curShader){
		curShader = info->pos.x;
		Shader::useShader(curShader);
	    };
	    x += 1;
	    u32 quadVerticesCount = (u32)info->pos.y * 4;
#if(GL)
	    OpenGL::setMat4Uniform(*(glm::mat4*)r.renderBuffer, "uProjectionView", curShader);
	    OpenGL::batchAndDraw(r, x, x + quadVerticesCount);
#endif
	    x += quadVerticesCount;
	};
    };
    void clearColourBuffer(){
#if(GL)
	OpenGL::clearColourBuffer();
#endif
    };
    void beginFrame(Renderer &r, FrameBuffer &fb){
	r.drawCalls = 0;
	fb.bind();
	Draw::clearColourBuffer();
    };
    void endFrame(Renderer &r, FrameBuffer &fb){
	fb.unbind();
	r.bufferEmpty = true;
	r.watermark = r.renderBuffer;
    };
    void drawWireframe(){
#if(GL)
	OpenGL::drawWireframe();
#endif
    };
    void drawFill(){
#if(GL)
	OpenGL::drawFill();
#endif
    };
    void setMat4Uniform(glm::mat4 &mat, char *uniformName, u32 shader){
#if(GL)
	OpenGL::setMat4Uniform(mat, uniformName, shader);
#endif
    };
    void setVec4Uniform(glm::vec4 &vec, char *uniformName, u32 shader){
#if(GL)
	OpenGL::setVec4Uniform(vec, uniformName, shader);
#endif
    };
    ScreenQuad initScreenQuad(){
#if(GL)
	return OpenGL::initScreenQuad();
#endif
    };
    void uninitScreenQuad(ScreenQuad &sq){
#if(GL)
	OpenGL::uninitScreenQuad(sq);
#endif
    };
    char *getRenderContextInfoString(){
#if(GL)
	return (char*)glGetString(GL_VERSION);
#endif
	return nullptr;
    };
};
