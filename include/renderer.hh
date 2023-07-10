#pragma once

namespace Renderer{
#if(DBG)
    void enableDebugMode();
#endif
    void createDefaultShader(u32 &shaderProgram);
    void drawWireframe();
    void drawFill();
    void setMat4Uniform(glm::mat4 &mat, char *uniformName, u32 shader);
    void setVec4Uniform(glm::vec4 &vec, char *uniformName, u32 shader);
    char *getRenderContextInfoString();
    void clearColourBuffer();
};
