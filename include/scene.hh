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
    template<typename T>
    void removeComponent(Entity e){
	u32 componentID = getID<T>();
	u32 &mask = entityComponentMask[e];
	if(!IS_BIT(mask, componentID)){return;};
	CLEAR_BIT(mask, componentID);
	componentPoolRemoveComponent(components[componentID], e);
    };
    template<typename T>
    T *getComponent(Entity e){
	u32 componentID = getID<T>();
	u32 mask = entityComponentMask[e];
	if(!IS_BIT(mask, componentID)){return nullptr;};
	return (T*)componentPoolGetComponent(components[componentID], e);
    };

    b2World *physicsWorld;
    map_int_t entityNameToID;
    ds::DynamicArray<u32> entityComponentMask;
    ds::DynamicArray<ComponentPool> components;
    Entity entityCount;
    u8 id;
};

template<typename T>
T *addComponent(Scene *s, Entity e){
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
