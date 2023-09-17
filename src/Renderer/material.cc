#include "material.hh"
#include "crystal.hh"

void materialInit(Material &m, u32 s){
    m.shader = s;
    m.registeredEntities.init();
};
void materialUninit(Material &m){
    m.registeredEntities.uninit();
};
void materialRegisterEntity(Material &m, Entity e){
    m.registeredEntities.push(e);
};

void materialSystemInit(u32 materialCount = 5){
    engine->ms.materials.init(materialCount);
};
void materialSystemUninit(){
    MaterialSystem &ms = engine->ms;
    for(u32 x=0; x<ms.materials.count; x+=1){
	Material &mat = ms.materials[x];
	materialUninit(mat);
    };
    ms.materials.uninit();
};
Material &newMaterial(u32 shader){
    Material &mat =  engine->ms.materials.newElem();
    materialInit(mat, shader);
    return mat;
};

void serializeMaterialSystem(char *filePath){
    MaterialSystem &ms = engine->ms;
    FILE *f = fopen(filePath, "wb");
    fwrite(&ms.materials.count, sizeof(ms.materials.count), 1, f);
    for(u32 x=0; x<ms.materials.count; x+=1){
	Material &mat = ms.materials[x];
	fwrite(&mat.registeredEntities.count, sizeof(mat.registeredEntities.count), 1, f);
	fwrite(mat.registeredEntities.mem, sizeof(Entity) * mat.registeredEntities.count, 1, f);
	fwrite(&mat.col, sizeof(mat.col), 1, f);
	fwrite(&mat.shader, sizeof(mat.shader), 1, f);
    };
    fclose(f);
};
void deserializeMaterialSystem(char *filePath){
    MaterialSystem &ms = engine->ms;
    
    FILE *f = fopen(filePath, "rb");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    void *mem = mem::alloc(size);
    fread(mem, size, 1, f);
    fclose(f);
    char *charMem = (char*)mem;

    u32 count = *(u32*)charMem;
    ms.materials.init(count);
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

	mat.col = *(glm::vec4*)charMem;
	charMem += sizeof(mat.col);

	mat.shader = *(u32*)charMem;
	charMem += sizeof(mat.shader);

	ms.materials.push(mat);
    };
    
    mem::free(mem);
    fclose(f);
};
