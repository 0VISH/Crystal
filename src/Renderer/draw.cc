#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "renderer.hh"
#include "../../game/components.cc"

#include <math.h>

namespace Draw{
    void init(Renderer &r){
	r.renderBuffer = (Draw::Vertex*)mem::alloc(sizeof(glm::mat4) + sizeof(Vertex) * maxVertexCount);
	r.watermark = r.renderBuffer;
	r.bufferEmpty = true;
	r.drawCalls = 0;
#if(RCONTEXT_GL)
	OpenGL::init(r);
#endif
    };
    void uninit(Renderer &r){
	mem::free(r.renderBuffer);
#if(RCONTEXT_GL)
	OpenGL::uninit(r);
#endif
    };
    void bindShader(u32 shader){
#if(RCONTEXT_GL)
	OpenGL::useProgram(shader);
#endif
    };
    void draw(Renderer &r){
	if(r.bufferEmpty){return;};
	Draw::Vertex *x = r.renderBuffer + (u32)ceil((f64)sizeof(glm::mat4)/(f64)sizeof(Draw::Vertex));
	u32 curShader = x->pos.x;
	bindShader(curShader);
	while(x != r.watermark){
	    Draw::Vertex *info = x;
	    if(info->pos.x != curShader){
		curShader = info->pos.x;
		bindShader(curShader);
	    };
	    x += 1;
	    u32 quadVerticesCount = (u32)info->pos.y * 4;
#if(RCONTEXT_GL)
	    OpenGL::setMat4Uniform(*(glm::mat4*)r.renderBuffer, "uProjectionView", curShader);
	    OpenGL::batchAndDraw(r, x, x + quadVerticesCount);
#endif
	    x += quadVerticesCount;
	};
    };
    void clearColourBuffer(){
#if(RCONTEXT_GL)
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
};
