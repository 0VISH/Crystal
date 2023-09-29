#pragma once

#include "box2d/box2d.h"

typedef s32 Entity;

//TODO: write a custom hashmap

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
    Entity *entityToComponentOff;
    Entity entityWatermark;
};

struct Scene{
    map_int_t             entityNameToID;
    ds::DynamicArray<u32> entityComponentMask;
    ds::DynamicArray<ComponentPool> components;
    b2World *physicsWorld;
    LayerFunc onInit;
    LayerFunc onUninit;
    LayerFunc onRender;
    LayerUpdateFunc onUpdate;
    Entity   activeCam;
    Entity   entityCount;
    SceneState state;
    u8       id;
};
