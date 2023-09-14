#pragma once

#include "box2d/box2d.h"

typedef u32 Entity;

//TODO: write a custom hashmap

static u32 componentUID = 0;
template <class T>
u32 getID(){
    static u32 componentId = componentUID;
    componentUID += 1;
    return componentId;
}

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

template<typename T>
T *addComponent(Entity e){
    Scene *s = getEngine()->curScene;
    u32 componentID = getID<T>();
    if(componentID >= s->components.count){
	ComponentPool &cp = s->components.newElem();
	componentPoolInit(cp, sizeof(T), 5, 5);
    };
    u32 &mask = s->entityComponentMask[e];
    if(IS_BIT(mask, componentID)){return nullptr;};
    SET_BIT(mask, componentID);
    ComponentPool &cp = s->components[componentID];
    T* t = (T*)componentPoolAddComponent(cp, e);
    t->init(s, e);
    return t;
};
