#pragma once

typedef void (*materialRegisterEntityType)(Material &m, Entity e);
typedef Material& (*newMaterialType)(MaterialSystem *ms, u32 shader);

typedef void  (*componentPoolInitType)(ComponentPool &cp, u64 size, u32 begLen, u32 ew);
typedef void* (*componentPoolAddComponentType)(ComponentPool &cp, Entity e);
typedef void  (*componentPoolRemoveComponentType)(ComponentPool &cp, Entity e);
typedef void* (*componentPoolGetComponentType)(ComponentPool &cp, Entity e);

typedef Scene* (*allocSceneType)();
typedef void   (*freeSceneType)(Scene *s);
typedef void   (*sceneInitType)(Scene *s, u32 begEntityCount);
typedef void   (*sceneUninitType)(Scene *s);
typedef Entity (*sceneNewEntityType)(Scene *s, char *name);
typedef Entity (*getEntityType)(Scene *s, char *name);

typedef void   (*setCurrentSceneType)(Scene *s);
typedef Scene* (*getCurrentSceneType)();

typedef b2Body* (*createRigidBodyType)(b2BodyDef *def, b2World *world);
typedef b2Fixture* (*createBoxColliderFixtureType)(f32 x, f32 y, f32 density, f32 friction, b2Body *body);

typedef Renderer* (*getRendererType)();
typedef MaterialSystem* (*getMaterialSystemType)();

//only for editor
typedef bool (*isKeyDownType)(ButtonCode code);
