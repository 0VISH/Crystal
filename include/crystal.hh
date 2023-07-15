#pragma once

struct Crystal{
    LayerManager      lm;
    EventDispatcher   ed;
    MaterialSystem    ms;
    ShaderSystem      ss;
    FrameBuffer       fb;
    Scene            *curScene;
    u32               windowX;
    u32               windowY;
    bool              shouldClose;
    
    void init();
    void uninit();
};
