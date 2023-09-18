#pragma once

struct Material{
    ds::DynamicArray<Entity> registeredEntities;
    glm::vec4 col;
    char *name;
    u32 shader;
    u32 id;
};

struct MaterialSystem{
    ds::DynamicArray<Material> materials;
    //TODO: hash-map to get mat from its name
};
