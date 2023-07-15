#include "scene.hh"

u32 componentCounter = 0;

template <class T>
u32 getID(){
    static int componentId = componentCounter++;
    return componentId;
}

void ComponentPool::init(u64 size, u32 begLen, u32 ew){
    count = 0;
    entityWatermark = ew;
    componentSize = size;
    len = begLen;
    mem = (char*)mem::calloc(componentSize * len);
    entityToComponentOff = (Entity*)mem::alloc(entityWatermark);
};
void ComponentPool::uninit(){
    mem::free(mem);
    mem::free(entityToComponentOff);
};
/*
  NOTE: DO NOT DO THIS:

  u32 *f = (u32*)cp.newComponent((Entity)1);
  u32 *s = (u32*)cp.newComponent((Entity)2);
  *f = 69;
      
  THIS MIGHT NOT WORK SINCE THE SECOND CALL MIGHT REALLOC MEM AND 
  POINTER 'f' MIGHT BE INVALIDATED!!!!!
*/
void *ComponentPool::newComponent(Entity e){
    if(e > entityWatermark){
	void *newMem = mem::alloc(sizeof(Entity) * e);
	memcpy(newMem, entityToComponentOff, sizeof(Entity)*entityWatermark);
	mem::free(mem);
	entityToComponentOff = (Entity*)newMem;
	entityWatermark = e;
    };
    entityToComponentOff[e] = count;
    if(count == len){
	u32 newCap = len + len / 2 + 1;
	void *newMem = mem::calloc(componentSize * newCap);
	memcpy(newMem, mem, componentSize * len);
	mem::free(mem);
	mem = (char*)newMem;
	len = newCap;
    };
    count += 1;
    return &mem[componentSize*(count-1)];
};
void ComponentPool::removeComponent(Entity e){
    u32 off = count - 1;
    void *lastComponent = mem + (componentSize * off);
    void *curComponent  = &mem[componentSize*entityToComponentOff[e]];
    if(lastComponent != curComponent){
	memcpy(curComponent, lastComponent, componentSize);
    };
    entityToComponentOff[off] = entityToComponentOff[e];
};
void *ComponentPool::getComponent(Entity e){
#if(DBG)
    if(e >= entityWatermark){
	dlog("e >= entityWatermark");
	return nullptr;
    };
#endif
    u32 off = entityToComponentOff[e];
    return &mem[componentSize*(off)];
};
#if(DBG)
void ComponentPool::dumpStat(){
    log("size: %lld\nmem: %p\ncount: %d\nlen: %d\nentityToComponentOff: %p\nentityWatermark: %d\n", componentSize, mem, count, len, entityToComponentOff, entityWatermark);
};
#endif

static u8 sceneID = 0;

void Scene::init(u32 begEntityCount){
    id = sceneID;
    sceneID += 1;
    entityCount = 0;
    entityComponentMask.init(begEntityCount);
    components.init();
};
void Scene::uninit(){
    entityComponentMask.uninit();
    for(u32 x=0; x<components.count; x+=1){
	ComponentPool &cp = components[x];
	cp.uninit();
    };
    components.uninit();
};
Entity Scene::newEntity(char *name){
    Entity e = entityCount;
    std::string nameStr(name, strlen(name));
    entityNameToEntity[nameStr] = e;
    entityCount += 1;
    entityComponentMask.push(0);
    return e;
};
Entity Scene::getEntity(char *name){
    std::string nameStr(name);
    return entityNameToEntity[nameStr];
};
void Scene::render(MaterialSystem &ms, FrameBuffer &fb){
    fb.bind();
    Renderer::clearColourBuffer();
    Batch::beginBatch();
    for(u32 x=0; x<ms.materials.count; x+=1){
	Material &mat = ms.materials[x];
	Batch::useMaterial(&mat);
	for(u32 i=0; i<mat.registeredEntities.count; i+=1){
	    Entity ent = mat.registeredEntities[i];
	    Component::Transform *t = getComponent<Component::Transform>(ent);
	    if(t != nullptr){Batch::submitQuad(t->genMatrix());};
	};
    };
    Batch::endBatch();
    Batch::flush();
    fb.unbind();
};
