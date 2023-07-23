#include "material.hh"

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

void materialSystemInit(MaterialSystem *ms, u32 materialCount = 5){
    ms->materials.init(materialCount);
};
void materialSystemUninit(MaterialSystem *ms){
    for(u32 x=0; x<ms->materials.count; x+=1){
	Material &mat = ms->materials[x];
	materialUninit(mat);
    };
    ms->materials.uninit();
};
Material &newMaterial(MaterialSystem *ms, u32 shader){
    Material &mat =  ms->materials.newElem();
    materialInit(mat, shader);
    return mat;
};
