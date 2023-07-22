#pragma once



typedef void (*materialInitType)(Material &m, u32 s);
typedef void (*materialUninitType)(Material &m);
typedef void (*materialRegisterEntityType)(Material &m, Entity e);

typedef void (*materialSystemInitType)(MaterialSystem &ms, u32 materialCount);
typedef void (*materialSystemUninitType)(MaterialSystem &ms);
typedef Material& (*newMaterialType)(MaterialSystem &ms, u32 shader);

typedef void  (*componentPoolInitType)(ComponentPool &cp, u64 size, u32 begLen, u32 ew);
typedef void* (*componentPoolNewComponentType)(ComponentPool &cp, Entity e);
typedef void  (*componentPoolRemoveComponentType)(ComponentPool &cp, Entity e);
typedef void* (*componentPoolGetComponentType)(ComponentPool &cp, Entity e);

typedef Scene* (*allocSceneType)();
typedef void   (*freeSceneType)(Scene *s);
typedef void   (*sceneInitType)(Scene &s, u32 begEntityCount);
typedef void   (*sceneUninitType)(Scene &s);
typedef Entity (*sceneNewEntityType)(Scene &s);

typedef void   (*editorSignalType)();
typedef void   (*setCurrentSceneType)(Scene *s);
typedef Scene* (*getCurrentSceneType)();
