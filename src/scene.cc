#include "scene.hh"
#include "crystal.hh"
#include "components.hh"

void componentPoolInit(ComponentPool &cp, u64 size, u32 begLen, u32 ew=1){
    cp.count = 0;
    cp.entityWatermark = ew;
    cp.componentSize = size;
    cp.len = begLen;
    cp.mem = (char*)mem::calloc(cp.componentSize * cp.len);
    cp.entityToComponentOff = (Entity*)mem::alloc(sizeof(Entity)*cp.entityWatermark);
    memset(cp.entityToComponentOff, -1, sizeof(Entity)*cp.entityWatermark);
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
	memset(newMem, -1, sizeof(Entity)*e);
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

typedef u64 (*SerializeComponent)(FILE *f, void *mem, u32 count);
typedef void* (*DeserializeComponent)(char *mem, u32 count);

const u64 camSize = sizeof(Component::PCamera::pos) + sizeof(Component::PCamera::zoomLevel) + sizeof(Component::PCamera::aspectRatio) + sizeof(Component::PCamera::fieldOfView);
const u64 transSize = sizeof(Component::Transform::position) + sizeof(Component::Transform::rotation) + sizeof(Component::Transform::scale);

u64 serializePCamera(FILE *f, void *mem, u32 count){
    Component::PCamera *cmem = (Component::PCamera*)mem;
    for(u32 x=0; x<count; x+=1){
	Component::PCamera &cc = cmem[x];
	fwrite(&cc.pos, sizeof(cc.pos), 1, f);
	fwrite(&cc.zoomLevel, sizeof(cc.zoomLevel), 1, f);
	fwrite(&cc.aspectRatio, sizeof(cc.aspectRatio), 1, f);
	fwrite(&cc.fieldOfView, sizeof(cc.fieldOfView), 1, f);
    };
    return camSize;
};
void *deserializePCamera(char *mem, u32 count){
    Component::PCamera *cmem = (Component::PCamera*)mem::alloc(count * sizeof(Component::PCamera));
    for(u32 x=0; x<count; x+=1){
	Component::PCamera &cam = cmem[x];
	cam.pos = *(glm::vec3*)mem;
	mem += sizeof(cam.pos);
	cam.zoomLevel = *(f32*)mem;
	mem += sizeof(cam.zoomLevel);
	cam.aspectRatio = *(f32*)mem;
	mem += sizeof(cam.aspectRatio);
	cam.fieldOfView = *(f32*)mem;
	mem += sizeof(cam.fieldOfView);
	cam.initPerspective(cam.fieldOfView, cam.aspectRatio, cam.pos);
    };
    return cmem;
};
u64 serializeTransform(FILE *f, void *mem, u32 count){
    Component::Transform *tmem = (Component::Transform*)mem;
    for(u32 x=0; x<count; x+=1){
	Component::Transform &ct = tmem[x];
	fwrite(&ct.position, sizeof(ct.position), 1, f);
	fwrite(&ct.rotation, sizeof(ct.rotation), 1, f);
	fwrite(&ct.scale,    sizeof(ct.scale), 1, f);
    };
    return transSize;
};
void *deserializeTransform(char *mem, u32 count){
    Component::Transform *tmem = (Component::Transform*)mem::alloc(count * sizeof(Component::Transform));
    for(u32 x=0; x<count; x+=1){
	Component::Transform &tra = tmem[x];
	tra.position = *(glm::vec3*)mem;
	mem += sizeof(tra.position);
	tra.rotation = *(glm::vec3*)mem;
	mem += sizeof(tra.rotation);
	tra.scale = *(glm::vec3*)mem;
	mem += sizeof(tra.scale);
    };
    return tmem;
};

SerializeComponent serializeComponent[] = {
    serializePCamera,
    serializeTransform,
};
DeserializeComponent deserializeComponent[] = {
    deserializePCamera,
    deserializeTransform,
};
u64 serializedComponentSize[] = {
    camSize,
    transSize,
};

const u32 magicNumber1 = 6969;
const u32 magicNumber2 = 420420;

void serializeCurrentScene(char *fileName){
};
void deserializeToCurrentScene(char *fileName){
};
Entity newEntity(char *name){
    Scene *s = engine->curScene;
    u32 count = (u32)strlen(name)+1;
    char *nameMem = (char*)mem::alloc(count);
    memcpy(nameMem, name, count);
    Entity e = s->entityCount;
    s->entityCount += 1;
    s->entityComponentMask.push(0);
    String nameStr;
    nameStr.mem = nameMem;
    nameStr.len = count-1;
    u32 temp;
    if(s->entityNameToID.getValue({nameStr}, &temp)){
	print("[error] Entity with name %s already exists", name);
	return -1;
    };
    s->entityNameToID.insertValue(nameStr, (u32)e);
    return e;
};
Entity getEntity(char *name){
    Scene *s = engine->curScene;
    String nameStr;
    nameStr.mem = name;
    nameStr.len = (u32)strlen(name);
    u32 e;
    if(s->entityNameToID.getValue({nameStr}, &e) == false){
	print("[error] Entity with name %s does not exist", name);
	return -1;
    };
    return (Entity)e;
};
void removeComponent(Entity e, u32 componentID){
    if(e < 0){
	print("Invalid Entity ID: %d", e);
	return;
    };
    Scene *s = engine->curScene;
    u32 &mask = s->entityComponentMask[e];
    if(!IS_BIT(mask, componentID)){return;};
    CLEAR_BIT(mask, componentID);
    componentPoolRemoveComponent(s->components[componentID], e);
};
void *getComponent(Entity e, u32 componentID){
    if(e < 0){
	print("Invalid Entity ID: %d", e);
	return nullptr;
    };
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
    s->onInit   = nullptr;
    s->onUpdate = nullptr;
    s->onRender = nullptr;
    s->onUninit = nullptr;
    s->entityNameToID.init();
    s->state = SceneState::PLAYING;
    s->physicsWorld = new b2World({0.0, -9.8});
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
    s->entityNameToID.uninit(mem::free);
    delete s->physicsWorld;
    mem::free(s);
};
