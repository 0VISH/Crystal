#pragma once

typedef void (*ShaderCreateCallback)(u32 shader);

namespace Renderer{
    struct Shape{
#if(RCONTEXT_GL)
	u32 vao;
#endif
	u32 vbo;
	u32 ibo;
    };
    struct Object{
	Shape triangle;
	Shape quad;
	u32 shaderProgram;
    };
    struct FuncAddr{
	void (*enableDebugMode)();
	Renderer::Object (*createObject)();
	void (*destroyObject)(Renderer::Object &obj);
	void (*drawTriangle)(Renderer::Object &obj);
	void (*drawQuad)(Renderer::Object &obj);
	void (*drawWireframe)();
	void (*drawFill)();
    };
    typedef void (*RFA)(Renderer::FuncAddr *fa);
};
