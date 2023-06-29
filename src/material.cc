struct Material{
    ds::DynamicArray<Entity> registeredEntities;
    glm::vec4 col;

    void init(){
	registeredEntities.init();
    };
    void uninit(){
	registeredEntities.uninit();
    };
    void registerEntity(Entity e){
	registeredEntities.push(e);
    };
};

struct MaterialSystem{
    ds::DynamicArray<Material> materials;

    void init(u32 materialCount = 5){
	materials.init(materialCount);
    };
    void uninit(){
	for(u32 x=0; x<materials.count; x+=1){
	    Material &mat = materials[x];
	    mat.uninit();
	};
	materials.uninit();
    };
    Material &newMaterial(){
	Material &mat =  materials.newElem();
	mat.init();
	return mat;
    };
};
