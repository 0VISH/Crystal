#if(RCONTEXT_GL)
#include "../../vendor/glad/include/glad/glad.h"

namespace OpenGL{
    void enableDebugMode(void *callBack){
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback((GLDEBUGPROC)callBack, nullptr);
    };
};
#endif

namespace Renderer{
    void enableDebugMode(void *callBack){
#if(RCONTEXT_GL)
	OpenGL::enableDebugMode(callBack);
#endif
    };
};
