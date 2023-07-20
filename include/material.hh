#pragma once

struct Material{
    ds::DynamicArray<Entity> registeredEntities;
    glm::vec4 col;
    u32 shader;
};

struct MaterialSystem{
    ds::DynamicArray<Material> materials;
};
