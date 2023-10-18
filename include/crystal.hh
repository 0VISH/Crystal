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
    s32               gameLayerOff;
    u32               windowX; //if set to 0, engine exits
    u32               windowY;

#if(WIN) 
    HMODULE           gameCode;
#elif(ANDROID)
    void             *gameCode;
#endif

    void init();
    void uninit();
};

extern Crystal *engine;
