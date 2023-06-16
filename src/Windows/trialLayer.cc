void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
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

namespace game{
    u32 shaderProgram;
    u32 VAO;
    u32 vbo;
    
    void init(){
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(DebugCallback, nullptr);
	
	//TODO: error check modern opengl. package the shader?
	float vertices[] = {
	    -0.5f, -0.5f, 0.0f,
	    0.5f, -0.5f, 0.0f,
	    0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, &VAO);	
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	const char *vertexShaderSource = "#version 330 core\n"
	    "layout (location = 0) in vec3 aPos;\n"
	    "void main()\n"
	    "{\n"
	    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	    "}\0";
	u32 vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	const char *fragmentShaderSource = "#version 330 core\n"
	    "layout (location = 0) out vec4 oFragCol;\n"
	    "void main()\n"
	    "{\n"
	    "   oFragCol = vec4(1.0f, 0.5f, 1.0f, 1.0);\n"
	    "}\0";
	u32 fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
	    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	    log("infoLog: %s\n", infoLog);
	}

	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);  
    };

    void render(){
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
    };
    
    void uninit(){
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &VAO);
    };
};
