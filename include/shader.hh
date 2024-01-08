#pragma once

struct ShaderInfo{
    u32 shaderId;
    u32 textureUnitOff;
};

struct ShaderSystem{
    HashmapStr shaderToOff;
    ShaderInfo *shaderInfo;
    u32 off;
    
    void init();
    void uninit();
    u32 newShader(char *vertexShaderPath, char *fragmentShaderPath, char *name);
    u32 getShaderId(char *name);
    u32 getShaderId(u32 shader);
};
