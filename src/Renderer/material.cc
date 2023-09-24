#include "material.hh"
#include "crystal.hh"

void materialUninit(Material &m){
    mem::free(m.name);
    m.registeredEntities.uninit();
};
void materialRegisterEntity(Material &m, Entity e){
    m.registeredEntities.push(e);
};

void allocMaterialSystem(){
    engine->ms = (MaterialSystem*)mem::alloc(sizeof(MaterialSystem));
};
void materialSystemInit(u32 materialCount = 5){
    MaterialSystem *ms = engine->ms;
    ms->materials.init(materialCount);
};
void uninitAndFreeMaterialSystem(){
    MaterialSystem *ms = engine->ms;
    for(u32 x=0; x<ms->materials.count; x+=1){
	Material &mat = ms->materials[x];
	materialUninit(mat);
    };
    ms->materials.uninit();
    mem::free(ms);
};
Material &newMaterial(char *name, u32 shader){
    MaterialSystem *ms = engine->ms;
    u32 count = ms->materials.count;
    Material &mat =  ms->materials.newElem();
    u32 len = (u32)strlen(name) + 1;
    char *aName = (char*)mem::alloc(len);
    memcpy(aName, name, len);
    mat.shader = shader;
    mat.name = aName;
    mat.registeredEntities.init();
    mat.id = count;
    return mat;
};

void serializeMaterialSystem(char *filePath){
    MaterialSystem *ms = engine->ms;
    FILE *f = fopen(filePath, "wb");
    ASSERT(f);
    fwrite(&ms->materials.count, sizeof(ms->materials.count), 1, f);
    for(u32 x=0; x<ms->materials.count; x+=1){
	Material &mat = ms->materials[x];
	fwrite(&mat.registeredEntities.count, sizeof(mat.registeredEntities.count), 1, f);
	fwrite(mat.registeredEntities.mem, sizeof(Entity) * mat.registeredEntities.count, 1, f);
	u32 nameLen = strlen(mat.name) + 1;  //+1 for null byte
	fwrite(&nameLen, sizeof(nameLen), 1, f);
	fwrite(mat.name, nameLen, 1, f);
	fwrite(&mat.col, sizeof(mat.col), 1, f);
	fwrite(&mat.shader, sizeof(mat.shader), 1, f);
	fwrite(&mat.id, sizeof(mat.id), 1, f);
    };
    fclose(f);
};
void deserializeMaterialSystem(char *filePath){
    MaterialSystem *ms = engine->ms;
    
    FILE *f = fopen(filePath, "rb");
    ASSERT(f);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    void *mem = mem::alloc(size);
    fread(mem, size, 1, f);
    fclose(f);
    char *charMem = (char*)mem;

    u32 count = *(u32*)charMem;
    ms->materials.init(count);
    charMem += sizeof(count);

    for(u32 x=0; x<count; x+=1){
	Material mat;
	
	u32 entCount = *(u32*)charMem;
	charMem += sizeof(count);
	Entity *regEnt = (Entity*)charMem;
	charMem += entCount * sizeof(Entity);
	
	mat.registeredEntities.init(entCount);
	for(u32 y=0; y<entCount; y+=1){
	    mat.registeredEntities.push(regEnt[x]);
	};

	u32 nameLen = *(u32*)charMem;
	charMem += sizeof(nameLen);

	char *name = (char*)mem::alloc(nameLen);
	memcpy(name, charMem, nameLen);
	charMem += nameLen;
	mat.name = name;
	
	mat.col = *(glm::vec4*)charMem;
	charMem += sizeof(mat.col);

	mat.shader = *(u32*)charMem;
	charMem += sizeof(mat.shader);

	mat.id = *(u32*)charMem;

	ms->materials.push(mat);
    };
    
    mem::free(mem);
    fclose(f);
};
