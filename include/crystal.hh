#pragma once

#if(WIN)

#pragma warning(disable: 4005) //glad.h redifines APIENTRY
#include <windows.h>
#pragma warning(default: 4005)

#endif

#include "material.hh"
#include "renderer.hh"
#include "shader.hh"
#include "framebuffer.hh"
#include "event.hh"
#include "layer.hh"

struct Crystal{
    LayerManager      lm;
    EventDispatcher   ed;
    ShaderSystem      ss;
    FrameBuffer       fb;
    Renderer          r;
    MaterialSystem   *ms;
    Scene            *curScene;
    u32               windowX;
    u32               windowY;
    u32               defaultShader;
    u32               screenShader;
    bool              shouldClose;

#if(WIN) 
    HMODULE           gameCode;
#endif

    void init();
    void uninit();
};

extern Crystal *engine;
