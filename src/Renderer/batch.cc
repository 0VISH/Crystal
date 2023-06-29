namespace Batch{
    const u32 maxQuadCount   = 1000;
    const u32 maxVertexCount = maxQuadCount * 4;
    const u32 maxIndexCount  = maxQuadCount * 6;

    struct Vertex{
	glm::vec3 pos;
	glm::vec4 col;
    };

    struct Batcher{
	Vertex   *vertices;
	Vertex   *watermark;
	u32      *indices;
	Material *material;
	u32 shaderProgram;
	u32 qvbo;
	u32 qvao;
	u32 qibo;
	u32 indexCount;

	void init(u32 shader){
	    shaderProgram = shader;
	    vertices = (Vertex*)mem::alloc(sizeof(Vertex) * maxVertexCount);

	    glGenVertexArrays(1, &qvao);	
	    glBindVertexArray(qvao);
	    glGenBuffers(1, &qvbo);
	    glBindBuffer(GL_ARRAY_BUFFER, qvbo);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * maxVertexCount, nullptr, GL_DYNAMIC_DRAW);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, pos));
	    glEnableVertexAttribArray(0);
	    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, col));
	    glEnableVertexAttribArray(1);

	    //fill up our entire index buffer
	    indices = (u32*)mem::alloc(sizeof(u32) * maxIndexCount);
	    u32 offset = 0;
	    for(u32 i=0; i<maxIndexCount; i+=6){
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 3 + offset;
		indices[i + 3] = 1 + offset;
		indices[i + 4] = 2 + offset;
		indices[i + 5] = 3 + offset;

		offset += 4;
	    };
	    glGenBuffers(1, &qibo);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, qibo);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * maxIndexCount, indices, GL_STATIC_DRAW);
	    mem::free(indices);
	};
	void beginBatch(){
	    watermark = vertices;
	    indexCount = 0;
	    s32 uLoc = glGetUniformLocation(shaderProgram, "uModel");
	    glUniformMatrix4fv(uLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));
	    uLoc = glGetUniformLocation(shaderProgram, "uCol");
	    glUniform4f(uLoc, 0, 0, 0, 0);
	};
	void endBatch(){
	    u32 size = (char*)watermark - (char*)vertices;
	    glBindBuffer(GL_ARRAY_BUFFER, qvbo);
	    glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
	};
	void flush(){
	    glBindVertexArray(qvao);
	    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	};
	void setMaterial(Material *m){
	    material = m;
	};
	void submitQuad(glm::mat4 &mat){
	    if(indexCount >= maxIndexCount){
		endBatch();
		flush();
		beginBatch();
	    };
	    float quadVertices[] = {
		0.5f,  0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f,
		-0.5f,  0.5f,
	    };
	    Vertex &v1 = *watermark;
	    v1.pos = mat * glm::vec4(quadVertices[0], quadVertices[1], 0.0, 1.0);
	    v1.col = material->col;
	    watermark += 1;

	    Vertex &v2 = *watermark;
	    v2.pos = mat * glm::vec4(quadVertices[2], quadVertices[3], 0.0, 1.0);
	    v2.col = material->col;
	    watermark += 1;

	    Vertex &v3 = *watermark;
	    v3.pos = mat * glm::vec4(quadVertices[4], quadVertices[5], 0.0, 1.0);
	    v3.col = material->col;
	    watermark += 1;

	    Vertex &v4 = *watermark;
	    v4.pos = mat * glm::vec4(quadVertices[6], quadVertices[7], 0.0, 1.0);
	    v4.col = material->col;
	    watermark += 1;
	    
	    indexCount += 6;
	};
	void uninit(){
	    mem::free(vertices);
	    glDeleteBuffers(1, &qibo);
	    glDeleteBuffers(1, &qvbo);
	    glDeleteVertexArrays(1, &qvao);
	};
    };
};
