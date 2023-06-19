#include "../Renderer/debug.cc"

namespace game{
    u32 shaderProgram;
    u32 VAO;
    u32 vbo;
    
    void init(){
	int success;
	char infoLog[512];
	Renderer::enableDebugMode(Renderer::DebugCallback);
	
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
	    "layout (location = 0) in vec3 iPos;\n"
	    "void main()\n"
	    "{\n"
	    "   gl_Position = vec4(iPos, 1.0);\n"
	    "}\0";
	u32 vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success){
	    log("[OPENGL ERROR]: %s\n", infoLog);
	};

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
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success){
	    log("[OPENGL ERROR]: %s\n", infoLog);
	};

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
	    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	    log("[OPENGL ERROR]: %s\n", infoLog);
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
