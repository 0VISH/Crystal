#pragma once

#if(PLAT_WINDOWS)

#pragma warning(disable: 4005) //glad.h redifines APIENTRY
#include <windows.h>
#pragma warning(default: 4005)

#endif

#include "material.hh"
#include "renderer.hh"
#include "shader.hh"
#include "framebuffer.hh"

struct Crystal{
    LayerManager      lm;
    EventDispatcher   ed;
    MaterialSystem    ms;
    ShaderSystem      ss;
    FrameBuffer       fb;
    Renderer          r;
    Scene            *curScene;
    u32               windowX;
    u32               windowY;
    u32               defaultShader;
    u32               screenShader;
    bool              shouldClose;

#if(PLAT_WINDOWS) 
    HMODULE           gameCode;
#endif

    void init();
    void uninit();
};

extern Crystal *engine;
