#pragma once

#include "../src/ds.cc"
#include "box2d/box2d.h"

typedef s32 Entity;

enum class SceneState{
    NONE,
    PLAYING,
    PAUSED,
};

struct ComponentPool{
    u64 componentSize;
    char *mem;
    u32 count;
    u32 len;
    u32 entityWatermark;
    Entity *entityToComponentOff;
};

struct Scene{
    HashmapStr        entityNameToID;
    DynamicArray<u32> entityComponentMask;
    DynamicArray<ComponentPool> components;
    b2World *physicsWorld;
    LayerFunc onInit;
    LayerFunc onUninit;
    LayerFunc onRender;
    LayerUpdateFunc onUpdate;
    Entity   activeCam;
    u32      entityCount;
    SceneState state;
    u32        id;
};
