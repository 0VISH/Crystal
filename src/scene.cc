u32 componentCounter = 0;

template <class T>
u32 getID(){
    static int componentId = componentCounter++;
    return componentId;
}
struct ComponentPool{
    void init(u64 size, u32 begLen = 5, u32 ec = 5){
	count = 0;
	entityCount = ec;
	componentSize = size;
	len = begLen;
	mem = (char*)mem::calloc(componentSize * len);
	entityToComponentOff = (Entity*)mem::alloc(entityCount);
    };
    void uninit(){
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
    void *newComponent(Entity e){
	if(e > entityCount){
	    void *newMem = mem::alloc(sizeof(Entity) * e);
	    memcpy(newMem, entityToComponentOff, sizeof(Entity)*entityCount);
	    mem::free(mem);
	    entityToComponentOff = (Entity*)newMem;
	    entityCount = e;
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
    void *getComponent(Entity e){
#if(DBG)
	if(e >= entityCount){
	    dlog("e >= entityCount");
	    return nullptr;
	};
#endif
	u32 off = entityToComponentOff[e];
	return &mem[componentSize*(off)];
    };
#if(DBG)
    void dumpStat(){
	log("size: %lld\nmem: %p\ncount: %d\nlen: %d\nentityToComponentOff: %p\nentityCount: %d\n", componentSize, mem, count, len, entityToComponentOff, entityCount);
    };
#endif

    u64 componentSize;
    Entity *entityToComponentOff;
    char *mem;
    u32 count;
    u32 len;
    Entity entityCount;
};

struct Scene{
    void init(u32 begEntityCount = 5){
	entityCount = 0;
	entityComponentMask.init(begEntityCount);
	components.init();
    };
    void uninit(){
	entityComponentMask.uninit();
	for(u32 x=0; x<components.count; x+=1){
	    ComponentPool &cp = components[x];
	    cp.uninit();
	};
	components.uninit();
    };
    Entity newEntity(){
	Entity e = entityCount;
	entityCount += 1;
	entityComponentMask.push(0);
	return e;
    };
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
	if(!IS_BIT(mask, componentID)){
	    dlog("entity doesn not have component: %d\n", componentID);
	    return nullptr;
	};
	return (T*)components[componentID].getComponent(e);
    };
    void render(MaterialSystem &ms, Batch::Batcher &br){
	br.beginBatch();
	for(u32 x=0; x<ms.materials.count; x+=1){
	    Material &mat = ms.materials[x];
	    br.useMaterial(&mat);
	    for(u32 i=0; i<mat.registeredEntities.count; i+=1){
		Entity ent = mat.registeredEntities[i];
		Component::Transform *t = getComponent<Component::Transform>(ent);
		br.submitQuad(t->mat);
	    };
	};
	br.endBatch();
	br.flush();
    };

    ds::DynamicArray<u32> entityComponentMask;
    ds::DynamicArray<ComponentPool> components;
    Entity entityCount;
};
