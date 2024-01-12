#pragma once

struct ShaderSystem{
    HashmapStr shaderToId;
    
    void init();
    void uninit();
    u32 newShader(char *vertexShaderPath, char *fragmentShaderPath, char *name);
    u32 getShaderId(char *name);
};
