#pragma once

#include "box2d/box2d.h"

typedef u32 Entity;

//TODO: write a custom hashmap

struct ComponentPool{
    u64 componentSize;
    char *mem;
    u32 count;
    u32 len;
    Entity *entityToComponentOff;
    Entity entityWatermark;
};

struct Scene{
    map_int_t entityNameToID;
    ds::DynamicArray<u32> entityComponentMask;
    ds::DynamicArray<ComponentPool> components;
    b2World *physicsWorld;
    void    *activeCam;
    Entity entityCount;
    u8 id;
};
