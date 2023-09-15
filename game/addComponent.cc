#include "componentID.hh"

template<typename T>
T *addComponent(Entity e, ComponentID id){
    Scene *s = getEngine()->curScene;
    u32 componentID = (u32)id;
    while(componentID >= s->components.count){
	ComponentPool &cp = s->components.newElem();
	componentPoolInit(cp, sizeof(T), 5, 5);
    };
    u32 &mask = s->entityComponentMask[e];
    if(IS_BIT(mask, componentID)){return nullptr;};
    SET_BIT(mask, componentID);
    ComponentPool &cp = s->components[componentID];
    T *t = (T*)componentPoolAddComponent(cp, e);
    t->init(s, e);
    return t;
};
