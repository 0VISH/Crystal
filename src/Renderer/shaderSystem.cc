struct ShaderSystem{
    ds::DynamicArray<u32> shaderPrograms;

    void init(){
	shaderPrograms.init();
    };
    u32 newShaderProgram(){
	u32 program = glCreateProgram();
	shaderPrograms.push(program);
	return program;
    };
    void setCameraProjectionViewMatrix(glm::mat4 &mat){
	for(u32 x=0; x<shaderPrograms.count; x+=1){
	    u32 shaderProgram = shaderPrograms[x];
	    Renderer::setMat4Uniform(mat, "uProjectionView", shaderProgram);
	};
    };
    u32 getDefaultShader(){
	return shaderPrograms[0];
    };
    void uninit(){
	for(u32 x=0; x<shaderPrograms.count; x+=1){
	    Shader::deleteShader(shaderPrograms[x]);
	};
	shaderPrograms.uninit();
    };
};
