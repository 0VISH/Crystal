#if(RCONTEXT_GL)
#include <GL/GL.h>

namespace ContextGL{
    HDC windowHandleToDeviceContext;
    HGLRC openGLRenderingContext;
    void init(window::Window window){
	//https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_%28WGL%29
	PIXELFORMATDESCRIPTOR pfd =
	    {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	    };

	windowHandleToDeviceContext = GetDC(window);

	int  letWindowsChooseThisPixelFormat;
	letWindowsChooseThisPixelFormat = ChoosePixelFormat(windowHandleToDeviceContext, &pfd); 
	SetPixelFormat(windowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &pfd);

	openGLRenderingContext = wglCreateContext(windowHandleToDeviceContext);
	wglMakeCurrent(windowHandleToDeviceContext, openGLRenderingContext);

	log("[RENDER CONTEXT]: OpenGL(%s)\n", (char*)glGetString(GL_VERSION));
    };
    void swapBuffers(){SwapBuffers(windowHandleToDeviceContext);};
    void uninit(window::Window window){
	wglMakeCurrent(NULL, NULL);
	ReleaseDC(window, windowHandleToDeviceContext);
	wglDeleteContext(openGLRenderingContext);
    };
};
#pragma comment(lib, "opengl32.lib")
#endif

namespace RenderContext{
    void init(window::Window window){
#if(RCONTEXT_GL)
	ContextGL::init(window);
#endif
    };
    void swapBuffers(){
#if(RCONTEXT_GL)
	ContextGL::swapBuffers();
#endif
    };
    void uninit(window::Window window){
#if(RCONTEXT_GL)
	ContextGL::uninit(window);
#endif
    };
};
