#pragma once

struct ShaderSystem{
    ds::DynamicArray<u32> shaderPrograms;
    
    void init();
    void uninit();
    u32 newShaderProgram();
    u32 getDefaultShader();
};
