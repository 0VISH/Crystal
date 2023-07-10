#include "material.hh"

void Material::init(u32 s){
    shader = s;
    registeredEntities.init();
};
void Material::uninit(){
    registeredEntities.uninit();
};
void Material::registerEntity(Entity e){
    registeredEntities.push(e);
};

void MaterialSystem::init(u32 materialCount){
    materials.init(materialCount);
};
void MaterialSystem::uninit(){
    for(u32 x=0; x<materials.count; x+=1){
	Material &mat = materials[x];
	mat.uninit();
    };
    materials.uninit();
};
Material &MaterialSystem::newMaterial(u32 shader){
    Material &mat =  materials.newElem();
    mat.init(shader);
    return mat;
};
