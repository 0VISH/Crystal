#pragma once

//TODO: write a custom hashmap
#include <unordered_map>
#include <string>

template <class T>
u32 getID(){
    static u32 componentId = getComponentUID();
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
    //TODO: maybe check??
    template<typename T>
    T *addComponent(Entity e){
	u32 componentID = getID<T>();
	if(componentID >= components.count){
	    ComponentPool &cp = components.newElem();
	    componentPoolInit(cp, sizeof(T), 5, 5);
	};
	u32 &mask = entityComponentMask[e];
	SET_BIT(mask, componentID);
	ComponentPool &cp = components[componentID];
	T* t = (T*)componentPoolNewComponent(cp, e);
	t->init();
	return t;
    };
    template<typename T>
    void removeComponent(Entity e){
	u32 componentID = getID<T>();
	u32 &mask = entityComponentMask[e];
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

    std::unordered_map<std::string, Entity> entityNameToEntity;
    ds::DynamicArray<u32> entityComponentMask;
    ds::DynamicArray<ComponentPool> components;
    Entity entityCount;
    u8 id;
};
