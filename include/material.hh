#pragma once

struct Material{
    DynamicArray<Entity>  registeredEntities;
    glm::vec4 col;
    char *name;
    u32 shader;
    u32 textureId;
    u32 id;
};

struct MaterialSystem{
    DynamicArray<Material> materials;
    HashmapStr materialToOff;
};
