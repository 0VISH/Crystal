#pragma once

//TODO: write a custom hashmap
#include <unordered_map>
#include <string>

template <class T>
u32 getID();

struct ComponentPool{
    void init(u64 size, u32 begLen = 5, u32 ec = 5);
    void uninit();
    void *newComponent(Entity e);
    void *getComponent(Entity e);
#if(DBG)
    void dumpStat();
#endif

    u64 componentSize;
    Entity *entityToComponentOff;
    char *mem;
    u32 count;
    u32 len;
    Entity entityCount;
};

struct Scene{
    void init(u32 begEntityCount = 5);
    void uninit();
    Entity newEntity(char *name);
    Entity getEntity(char *name);
    template<typename T>
    T *addComponent(Entity e){
	u32 componentID = getID<T>();
	if(componentID >= components.count){
	    ComponentPool &cp = components.newElem();
	    cp.init(sizeof(T));
	};
	u32 &mask = entityComponentMask[componentID];
	SET_BIT(mask, componentID);
	ComponentPool &cp = components[componentID];
	T* t = (T*)cp.newComponent(e);
	t->init();
    return t;
    };
    template<typename T>
    T *getComponent(Entity e){
	u32 componentID = getID<T>();
	u32 mask = entityComponentMask[componentID];
	if(!IS_BIT(mask, componentID)){return nullptr;};
	return (T*)components[componentID].getComponent(e);
    };
    void render(MaterialSystem &ms, FrameBuffer &fb);

    std::unordered_map<std::string, Entity> entityNameToEntity;
    ds::DynamicArray<u32> entityComponentMask;
    ds::DynamicArray<ComponentPool> components;
    Entity entityCount;
    u8 id;
};
