#pragma once

//TODO: write a custom hashmap
#include <unordered_map>
#include <string>

template <class T>
u32 getID();

struct ComponentPool{
    void init(u64 size, u32 begLen = 5, u32 ew = 5);
    void uninit();
    void *newComponent(Entity e);
    void removeComponent(Entity e);
    void *getComponent(Entity e);
#if(DBG)
    void dumpStat();
#endif

    u64 componentSize;
    char *mem;
    u32 count;
    u32 len;
    Entity *entityToComponentOff;
    Entity entityWatermark;
};

struct Scene{
    void init(u32 begEntityCount = 5);
    void uninit();
    Entity newEntity(char *name);
    Entity getEntity(char *name);

    //TODO: maybe check??
    template<typename T>
    T *addComponent(Entity e){
	u32 componentID = getID<T>();
	if(componentID >= components.count){
	    ComponentPool &cp = components.newElem();
	    cp.init(sizeof(T));
	};
	u32 &mask = entityComponentMask[e];
	SET_BIT(mask, componentID);
	ComponentPool &cp = components[componentID];
	T* t = (T*)cp.newComponent(e);
	t->init();
	return t;
    };
    template<typename T>
    void removeComponent(Entity e){
	u32 componentID = getID<T>();
	u32 &mask = entityComponentMask[e];
	CLEAR_BIT(mask, componentID);
	components[componentID].removeComponent(e);
    };
    template<typename T>
    T *getComponent(Entity e){
	u32 componentID = getID<T>();
	u32 mask = entityComponentMask[e];
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
