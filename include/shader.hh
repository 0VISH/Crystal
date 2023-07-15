#pragma once

struct ShaderSystem{
    ds::DynamicArray<u32> shaderPrograms;
    
    void init();
    u32 newShaderProgram();
    void setCameraProjectionViewMatrix(glm::mat4 &mat);
    u32 getDefaultShader();
    void uninit();
};
