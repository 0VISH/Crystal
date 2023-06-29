#if(RCONTEXT_GL)
namespace ContextGL{
    HDC windowHandleToDeviceContext;
    HGLRC openGLRenderingContext;
    void init(window::Window window){
	HDC hDc = ::GetDC(window);
	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	const int pf = ::ChoosePixelFormat(hDc, &pfd);
        ::SetPixelFormat(hDc, pf, &pfd);
	::ReleaseDC(window, hDc);
        windowHandleToDeviceContext = ::GetDC(window);
	openGLRenderingContext = wglCreateContext(windowHandleToDeviceContext);
	wglMakeCurrent(windowHandleToDeviceContext, openGLRenderingContext);
	gladLoadGL();
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
