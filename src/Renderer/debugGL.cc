namespace OpenGL{
#if(RCONTEXT_GL)
    void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
	//https://learnopengl.com/In-Practice/Debugging
	if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

	log("------[OPENGL ERROR]---------\n");
	log("%s\n", message);

	switch (source)
	    {
	    case GL_DEBUG_SOURCE_API:             log("Source: API"); break;
	    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   log("Source: Window System"); break;
	    case GL_DEBUG_SOURCE_SHADER_COMPILER: log("Source: Shader Compile"); break;
	    case GL_DEBUG_SOURCE_THIRD_PARTY:     log("Source: Third Party"); break;
	    case GL_DEBUG_SOURCE_APPLICATION:     log("Source: Application"); break;
	    case GL_DEBUG_SOURCE_OTHER:           log("Source: Other"); break;
	    };
	log("\n");
	switch (type)
	    {
	    case GL_DEBUG_TYPE_ERROR:               log("Type: Error"); break;
	    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: log("Type: Deprecated Behaviour"); break;
	    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  log("Type: Undefined Behaviour"); break; 
	    case GL_DEBUG_TYPE_PORTABILITY:         log("Type: Portability"); break;
	    case GL_DEBUG_TYPE_PERFORMANCE:         log("Type: Performance"); break;
	    case GL_DEBUG_TYPE_MARKER:              log("Type: Marker"); break;
	    case GL_DEBUG_TYPE_PUSH_GROUP:          log("Type: Push Group"); break;
	    case GL_DEBUG_TYPE_POP_GROUP:           log("Type: Pop Group"); break;
	    case GL_DEBUG_TYPE_OTHER:               log("Type: Other"); break;
	    };
	log("\n");
	switch (severity)
	    {
	    case GL_DEBUG_SEVERITY_HIGH:         log("Severity: high"); break;
	    case GL_DEBUG_SEVERITY_MEDIUM:       log("Severity: medium"); break;
	    case GL_DEBUG_SEVERITY_LOW:          log("Severity: low"); break;
	    case GL_DEBUG_SEVERITY_NOTIFICATION: log("Severity: notification"); break;
	    };
	log("\n");
    }

    void vertexCheckErr(u32 shader){
	s32  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success){
	    glGetShaderInfoLog(shader, 512, NULL, infoLog);
	    log("[VERTEX SHADER ERROR]: %s\n", infoLog);
	};
    };
    void fragmentCheckErr(u32 shader){
	s32  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success){
	    glGetShaderInfoLog(shader, 512, NULL, infoLog);
	    log("[FRAGMENT SHADER ERROR]: %s\n", infoLog);
	};
    };
    void linkCheckErr(u32 shaderProgram){
	s32  success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
	    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	    log("[SHADER LINK ERROR]: %s\n", infoLog);
	}
    };
#endif
};
