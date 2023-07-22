#include "scene.hh"

u32 componentCounter = 0;

u32 getComponentUID(){
    u32 id = componentCounter;
    componentCounter += 1;
    return id;
};

void componentPoolInit(ComponentPool &cp, u64 size, u32 begLen, u32 ew){
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
void *componentPoolNewComponent(ComponentPool &cp, Entity e){
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
    if(e >= cp.entityWatermark){
	print("e >= entityWatermark");
	return nullptr;
    };
#endif
    u32 off = cp.entityToComponentOff[e];
    return &cp.mem[cp.componentSize*(off)];
};

static u8 sceneID = 0;

void sceneInit(Scene &s, u32 begEntityCount){
    s.id = sceneID;
    sceneID += 1;
    s.entityCount = 0;
    s.entityComponentMask.init(begEntityCount);
    s.components.init();
};
void sceneUninit(Scene &s){
    s.entityComponentMask.uninit();
    for(u32 x=0; x<s.components.count; x+=1){
	ComponentPool &cp = s.components[x];
	componentPoolUninit(cp);
    };
    s.components.uninit();
};
Entity sceneNewEntity(Scene &s, char *name){
    Entity e = s.entityCount;
    std::string nameStr(name, strlen(name));
    s.entityNameToEntity[nameStr] = e;
    s.entityCount += 1;
    s.entityComponentMask.push(0);
    return e;
};
Entity sceneGetEntity(Scene &s, char *name){
    std::string nameStr(name);
    return s.entityNameToEntity[nameStr];
};
