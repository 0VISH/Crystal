#include "../Renderer/debug.cc"

namespace game{
    Renderer::Object robj;
    
    void init(){
	Renderer::enableDebugMode(Renderer::DebugCallback);
	robj = Renderer::createObject(Renderer::vertexCheckErr, Renderer::fragmentCheckErr, Renderer::linkCheckErr);
	Renderer::drawWireframe();
    };

    void render(){
	Renderer::drawTriangle(robj);
	Renderer::drawQuad(robj);
    };
    
    void uninit(){
	Renderer::destroyObject(robj);
    };
};
