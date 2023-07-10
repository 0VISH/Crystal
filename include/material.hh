#pragma once

struct Material{
    ds::DynamicArray<Entity> registeredEntities;
    glm::vec4 col;
    u32 shader;

    void init(u32 s);
    void uninit();
    void registerEntity(Entity e);
};

struct MaterialSystem{
    void init(u32 materialCount = 5);
    void uninit();
    Material &newMaterial(u32 shader);

    ds::DynamicArray<Material> materials;
};
