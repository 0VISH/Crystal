#pragma once

typedef void (*materialRegisterEntityType)(Material &m, Entity e);
typedef Material& (*newMaterialType)(MaterialSystem *ms, u32 shader);

typedef void  (*componentPoolInitType)(ComponentPool &cp, u64 size, u32 begLen, u32 ew);
typedef void* (*componentPoolNewComponentType)(ComponentPool &cp, Entity e);
typedef void  (*componentPoolRemoveComponentType)(ComponentPool &cp, Entity e);
typedef void* (*componentPoolGetComponentType)(ComponentPool &cp, Entity e);

typedef Scene* (*allocSceneType)();
typedef void   (*freeSceneType)(Scene *s);
typedef void   (*sceneInitType)(Scene *s, u32 begEntityCount);
typedef void   (*sceneUninitType)(Scene *s);
typedef Entity (*sceneNewEntityType)(Scene *s);

typedef void   (*setCurrentSceneType)(Scene *s);
typedef Scene* (*getCurrentSceneType)();

typedef Renderer* (*getRendererType)();
typedef MaterialSystem* (*getMaterialSystemType)();

//only for editor
typedef bool (*isKeyDownType)(ButtonCode code);
