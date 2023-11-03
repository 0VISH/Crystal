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
    Scene *s = engine->curScene;
    FILE *f = fopen(fileName, "wb");
    map_iter_t iter = map_iter(&s->entityNameToID);
    fwrite(&s->id, sizeof(s->id), 1, f);
    fwrite(&s->entityCount, sizeof(s->entityCount), 1, f);
    char *key = (char*)map_next(&s->entityNameToID, &iter);
    while(key){
	u32 len = strlen(key) + 1;  //+1 for null byte
	fwrite(&len, sizeof(len), 1, f);
	fwrite(key, len, 1, f);
	Entity e = *map_get(&s->entityNameToID, key);
	fwrite(&e, sizeof(e), 1, f);
	key = (char*)map_next(&s->entityNameToID, &iter);
    };
    fwrite(&magicNumber1, sizeof(magicNumber1), 1, f);
    fwrite(&s->entityComponentMask.count, sizeof(s->entityComponentMask.count), 1, f);
    fwrite(s->entityComponentMask.mem, s->entityComponentMask.count * sizeof(u32), 1, f);
    fwrite(&s->components.count, sizeof(s->components.count), 1, f);
    for(u32 x=0; x<s->components.count; x+=1){
	ComponentPool &cp = s->components[x];
	fwrite(&cp.count, sizeof(cp.count), 1, f);
	fwrite(&cp.componentSize, sizeof(cp.componentSize), 1, f);
	if(cp.count == 0){continue;};
	fwrite(&cp.entityWatermark, sizeof(cp.entityWatermark), 1, f);
	fwrite(cp.entityToComponentOff, sizeof(Entity)*cp.entityWatermark, 1, f);
	serializeComponent[x](f, cp.mem, cp.count);
    };
    fwrite(&magicNumber2, sizeof(magicNumber2), 1, f);
    fwrite(&s->activeCam, sizeof(s->activeCam), 1, f);
    fclose(f);
};
void deserializeToCurrentScene(char *fileName){
    Scene *s = engine->curScene;
    s->state = SceneState::PLAYING;
    map_init(&s->entityNameToID);

    bool fromFile = true;
    char *mem = Package::openNormalFileFromPkgElseFile(fileName, fromFile, Package::curPkg);
    char *charMem = mem;

    s->id = *(u8*)charMem;
    charMem += sizeof(s->id);
    Entity entityCount = *(Entity*)charMem;
    charMem += sizeof(entityCount);
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
    u32 magicNumberRead = *(u32*)charMem;
    charMem += sizeof(magicNumber1);
    if(magicNumberRead != magicNumber1){
	print("magic number 1 in %s is %d", fileName, magicNumberRead);
	if(fromFile){mem::free(mem);};
	s->id = -1;
	return;
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
	    cp.count = *(u32*)charMem;
	    charMem += sizeof(cp.count);
	    cp.componentSize = *(u64*)charMem;
	    charMem += sizeof(cp.componentSize);
	    if(cp.count == 0){
		componentPoolInit(cp, cp.componentSize, 5);
		continue;
	    };
	    cp.len = cp.count;	    
	    cp.entityWatermark = *(Entity*)charMem;
	    charMem += sizeof(cp.entityWatermark);
	    u64 entityToComponentSize = cp.entityWatermark*sizeof(Entity);
	    cp.entityToComponentOff = (Entity*)mem::alloc(entityToComponentSize);
	    memcpy(cp.entityToComponentOff, charMem, entityToComponentSize);
	    charMem += entityToComponentSize;
	    cp.mem = (char*)deserializeComponent[x](charMem, cp.count);
	    charMem += serializedComponentSize[x]*cp.count;
	};
    };
    magicNumberRead = *(u32*)charMem;
    charMem += sizeof(magicNumber2);
    if(magicNumberRead != magicNumber2){
	print("magic number 2 in %s is %d", fileName, magicNumberRead);
	if(fromFile){mem::free(mem);};
	s->id = -1;
	return;
    };
    s->activeCam = *(Entity*)charMem;
    s->physicsWorld = new b2World({0.0, -9.8});
    if(fromFile){mem::free(mem);};
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
    if(e == nullptr){return -1;};
    return *e;
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
    map_init(&s->entityNameToID);
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
    map_deinit(&s->entityNameToID);
    delete s->physicsWorld;
    mem::free(s);
};
