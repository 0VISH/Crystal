#pragma once

struct ShaderSystem{
    ds::DynamicArray<u32> shaderPrograms;
    //TODO: hash-map shader name to id
    
    void init();
    void uninit();
    u32 newShaderProgram();
    u32 getDefaultShader();
};
