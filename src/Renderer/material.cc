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
void materialSystemInit(u32 materialCount = 5, u32 textureCount = 5){
    MaterialSystem *ms = engine->ms;
    ms->materials.init(materialCount);
    ms->materialToOff.init(materialCount);
    ms->textureToId.init(textureCount);
};
void uninitAndFreeMaterialSystem(){
    MaterialSystem *ms = engine->ms;
    for(u32 x=0; x<ms->materials.count; x+=1){
	Material &mat = ms->materials[x];
	materialUninit(mat);
    };
    ms->materialToOff.uninit();
    ms->materials.uninit();
    ms->textureToId.uninit();
    mem::free(ms);
};
Material &newMaterial(char *name, char *shaderName){
    MaterialSystem *ms = engine->ms;
    u32 count = ms->materials.count;
    String matName;
    matName.mem = name;
    matName.len = (u32)strlen(name);
    u32 temp;
    if(ms->materialToOff.getValue(matName, &temp)){
	print("[error] material with name %s already exists", name);
	return ms->materials[0];
    };
    ms->materialToOff.insertValue(matName, count);
    Material &mat =  ms->materials.newElem();
    u32 len = (u32)strlen(name) + 1;
    char *aName = (char*)mem::alloc(len);
    memcpy(aName, name, len);
    if(engine->ss.shaderToOff.getValue({shaderName, (u32)strlen(shaderName)}, &mat.shader) == false){
	print("[error] shader with name %s does not exist", shaderName);
	mat.shader = 0;
    };
    mat.name = aName;
    mat.registeredEntities.init();
    mat.id = count;
    mat.col = glm::vec4(0.0, 0.0, 0.0, 1.0);
    mat.textureId = 0;
    return mat;
};

void serializeMaterialSystem(char *filePath){
    MaterialSystem *ms = engine->ms;
    FILE *f = fopen(filePath, "wb");
    ASSERT(f);

    fwrite(&ms->materials.count, sizeof(ms->materials.count), 1, f);
    for(u32 x=0; x<ms->materials.count; x+=1){
	Material &mat = ms->materials[x];
	serializeDynamicArray<Entity>(mat.registeredEntities, f);
	serializeString(mat.name, f);
	fwrite(&mat.col, sizeof(mat.col), 1, f);
	fwrite(&mat.shader, sizeof(mat.shader), 1, f);
	fwrite(&mat.id, sizeof(mat.id), 1, f);
    };
    fclose(f);
};
void deserializeMaterialSystem(char *filePath){
    MaterialSystem *ms = engine->ms;

    bool fromFile = true;
    void *mem = Package::openNormalFileFromPkgElseFile(filePath, fromFile, nullptr);
    char *charMem = (char*)mem;
    u32 x = 0;

    u32 count = deserialize<u32>(charMem, x);

    //TODO: alloc a block for material names
    for(u32 j=0; j<count; j+=1){
	Material mat;

	deserializeDynamicArray<Entity>(mat.registeredEntities, charMem, x);
	u32 len;
	mat.name = deserializeString(len, charMem, x);
	ms->materialToOff.insertValue({mat.name, len}, j);
	
	mat.col = deserialize<glm::vec4>(charMem, x);

	mat.shader = deserialize<u32>(charMem, x);
	
	mat.id = deserialize<u32>(charMem, x);

	ms->materials.push(mat);
    };
    if(fromFile){mem::free(mem);};
};
