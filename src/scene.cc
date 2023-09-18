#include "scene.hh"
#include "crystal.hh"
#include "components.hh"

void componentPoolInit(ComponentPool &cp, u64 size, u32 begLen, u32 ew=1){
    cp.count = 0;
    cp.entityWatermark = ew;
    cp.componentSize = size;
    cp.len = begLen;
    cp.mem = (char*)mem::calloc(cp.componentSize * cp.len);
    cp.entityToComponentOff = (Entity*)mem::alloc(cp.entityWatermark);
};
void componentPoolUninit(ComponentPool &cp){
    mem::free(cp.mem);
    mem::free(cp.entityToComponentOff);
};
/*
  NOTE: DO NOT DO THIS:

  u32 *f = (u32*)cp.newComponent((Entity)1);
  u32 *s = (u32*)cp.newComponent((Entity)2);
  *f = 69;
      
  THIS MIGHT NOT WORK SINCE THE SECOND CALL MIGHT REALLOC MEM AND 
  POINTER 'f' MIGHT BE INVALIDATED!!!!!
*/
void *componentPoolAddComponent(ComponentPool &cp, Entity e){
    if(e > cp.entityWatermark){
	void *newMem = mem::alloc(sizeof(Entity) * e);
	memcpy(newMem, cp.entityToComponentOff, sizeof(Entity)*cp.entityWatermark);
	mem::free(cp.mem);
	cp.entityToComponentOff = (Entity*)newMem;
	cp.entityWatermark = e;
    };
    cp.entityToComponentOff[e] = cp.count;
    if(cp.count == cp.len){
	u32 newCap = cp.len + cp.len / 2 + 1;
	void *newMem = mem::calloc(cp.componentSize * newCap);
	memcpy(newMem, cp.mem, cp.componentSize * cp.len);
	mem::free(cp.mem);
	cp.mem = (char*)newMem;
	cp.len = newCap;
    };
    cp.count += 1;
    return &cp.mem[cp.componentSize*(cp.count-1)];
};
void componentPoolRemoveComponent(ComponentPool &cp, Entity e){
    u32 off = cp.count - 1;
    void *lastComponent = cp.mem + (cp.componentSize * off);
    void *curComponent  = &cp.mem[cp.componentSize*cp.entityToComponentOff[e]];
    if(lastComponent != curComponent){
	memcpy(curComponent, lastComponent, cp.componentSize);
    };
    cp.entityToComponentOff[off] = cp.entityToComponentOff[e];
};
void *componentPoolGetComponent(ComponentPool &cp, Entity e){
#if(DBG)
    if(e > cp.entityWatermark){
	print("e(%d) > cp.entityWatermark(%d)", e, cp.entityWatermark);
	return nullptr;
    };
#endif
    u32 off = cp.entityToComponentOff[e];
    return &cp.mem[cp.componentSize*(off)];
};

static u8 sceneID = 0;

void serializeCurrentScene(char *fileName){
    Scene *s = engine->curScene;
    FILE *f = fopen(fileName, "wb");
    const char *key;
    map_iter_t iter = map_iter(&s->entityNameToID);
    fwrite(&s->id, sizeof(s->id), 1, f);
    fwrite(&s->entityCount, sizeof(s->entityCount), 1, f);
    while(key = map_next(&s->entityNameToID, &iter)){
	u32 len = strlen(key) + 1;  //+1 for null byte
	fwrite(&len, sizeof(len), 1, f);
	fwrite(key, len, 1, f);
	Entity e = *map_get(&s->entityNameToID, key);
	fwrite(&e, sizeof(e), 1, f);
    };
    fwrite(&s->entityComponentMask.count, sizeof(s->entityComponentMask.count), 1, f);
    fwrite(s->entityComponentMask.mem, s->entityComponentMask.count * sizeof(u32), 1, f);
    fwrite(&s->components.count, sizeof(s->components.count), 1, f);
    for(u32 x=0; x<s->components.count; x+=1){
	ComponentPool &cp = s->components[x];
	fwrite(&cp.componentSize, sizeof(cp.componentSize), 1, f);
	fwrite(&cp.count, sizeof(cp.count), 1, f);
	fwrite(&cp.entityWatermark, sizeof(cp.entityWatermark), 1, f);
	fwrite(cp.mem, cp.componentSize*cp.count, 1, f);
	fwrite(cp.entityToComponentOff, sizeof(Entity)*cp.entityWatermark, 1, f);
    };
    fwrite(&s->activeCam, sizeof(s->activeCam), 1, f);
    fclose(f);
};
void deserializeToCurrentScene(char *fileName){
    Scene *s = engine->curScene;
    map_init(&s->entityNameToID);
    
    FILE *f = fopen(fileName, "rb");
    if(f == nullptr){
	print("[error] Could not open scene file: %s", fileName);
	mem::free(s);
	engine->curScene = nullptr;
	return;
    };
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    void *mem = mem::alloc(size);
    fread(mem, size, 1, f);
    fclose(f);
    char *charMem = (char*)mem;

    u8 id = *(u8*)charMem;
    charMem += sizeof(id);
    s->entityCount = id;
    Entity entityCount = *(Entity*)charMem;
    charMem += sizeof(entityCount);
    if(entityCount != 0){
	s->entityCount = entityCount;
	while(entityCount != 0){
	    u32 len = *(u32*)charMem;
	    charMem += sizeof(len);
	    char *str = charMem;
	    charMem += len;
	    Entity e = *(Entity*)charMem;
	    charMem += sizeof(e);
	    map_set(&s->entityNameToID, str, e);
	    entityCount -= 1;
	};
    };
    u32 maskCount = *(u32*)charMem;
    charMem += sizeof(maskCount);
    u32 *maskMem = (u32*)charMem;
    charMem += maskCount * sizeof(u32);
    if(maskCount != 0){
	s->entityComponentMask.init(maskCount);
	for(u32 x=0; x<maskCount; x+=1){
	    s->entityComponentMask.push(maskMem[x]);
	};
    };
    u32 cpCount = *(u32*)charMem;
    charMem += sizeof(cpCount);
    if(cpCount == 0){s->components.init(5);}
    else{
	s->components.init(cpCount);
	for(u32 x=0; x<cpCount; x+=1){
	    ComponentPool &cp = s->components.newElem();
	    cp.componentSize = *(u64*)charMem;
	    charMem += sizeof(cp.componentSize);
	    cp.count = *(u32*)charMem;
	    cp.len = cp.count;
	    charMem += sizeof(cp.count);
	    cp.entityWatermark = *(Entity*)charMem;
	    charMem += sizeof(cp.entityWatermark);
	    u64 componentMemSize = cp.componentSize * cp.count;
	    cp.mem = (char*)mem::alloc(componentMemSize);
	    memcpy(cp.mem, charMem, componentMemSize);
	    charMem += componentMemSize;
	    u64 entityToComponentSize = cp.entityWatermark*sizeof(Entity);
	    cp.entityToComponentOff = (Entity*)mem::alloc(entityToComponentSize);
	    memcpy(cp.entityToComponentOff, charMem, entityToComponentSize);
	    charMem += entityToComponentSize;
	};
    };
    s->activeCam = *(Entity*)charMem;
    mem::free(mem);
    fclose(f);
};
Entity sceneNewEntity(char *name){
    Scene *s = engine->curScene;
    Entity e = s->entityCount;
    s->entityCount += 1;
    s->entityComponentMask.push(0);
    map_set(&s->entityNameToID, name, e);
    return e;
};
Entity getEntity(char *name){
    Scene *s = engine->curScene;
    Entity *e = (Entity*)map_get(&s->entityNameToID, name);
    if(e == nullptr){return 0;};
    return *e;
};
void removeComponent(Entity e, u32 componentID){
    ASSERT(e > -1);
    Scene *s = engine->curScene;
    u32 &mask = s->entityComponentMask[e];
    if(!IS_BIT(mask, componentID)){return;};
    CLEAR_BIT(mask, componentID);
    componentPoolRemoveComponent(s->components[componentID], e);
};
void *getComponent(Entity e, u32 componentID){
    ASSERT(e > -1);
    Scene *s = engine->curScene;
    u32 mask = s->entityComponentMask[e];
    if(!IS_BIT(mask, componentID)){return nullptr;};
    return componentPoolGetComponent(s->components[componentID], e);
};
void allocAndSetCurrentScene(){
    Scene *s = (Scene*)mem::alloc(sizeof(Scene));
    engine->curScene = s;
};
void initCurrentScene(u32 begEntityCount){
    Scene *s = engine->curScene;
    map_init(&s->entityNameToID);
    s->physicsWorld = new b2World({0.0, 9.8});
    s->id = sceneID;
    s->activeCam = -1;
    sceneID += 1;
    s->entityCount = 0;
    s->entityComponentMask.init(begEntityCount);
    s->components.init();
};
void uninitAndFreeCurrentScene(){
    Scene *s = engine->curScene;
    s->entityComponentMask.uninit();
    for(u32 x=0; x<s->components.count; x+=1){
	ComponentPool &cp = s->components[x];
	componentPoolUninit(cp);
    };
    s->components.uninit();
    map_deinit(&s->entityNameToID);
    delete s->physicsWorld;
    mem::free(s);
};
