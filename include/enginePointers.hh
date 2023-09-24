#pragma once

#include "crystal.hh"
#include "components.hh"

typedef void      (*materialRegisterEntityType)(Material &m, Entity e);
typedef Material& (*newMaterialType)(char *name, u32 shader);
typedef void      (*serializeMaterialSystemType)(char *fileName);
typedef void      (*deserializeMaterialSystemType)(char *fileName);

typedef void  (*componentPoolInitType)(ComponentPool &cp, u64 size, u32 begLen, u32 ew);
typedef void* (*componentPoolAddComponentType)(ComponentPool &cp, Entity e);

typedef void   (*allocAndSetCurrentSceneType)();
typedef void   (*uninitAndFreeCurrentSceneType)();
typedef void   (*serializeCurrentSceneType)(char *fileName);
typedef void   (*initCurrentSceneType)(u32 begEntityCount);
typedef void   (*setActiveCameraToCurrentSceneType)(Entity e);
typedef Entity (*sceneNewEntityType)(char *name);
typedef Entity (*getEntityType)(char *name);
typedef void   (*removeComponentType)(Entity e, u32 componentID);
typedef void*  (*getComponentType)(Entity e, u32 componentID);

typedef Scene* (*getCurrentSceneType)();

typedef b2Body*    (*createRigidBodyType)(b2BodyDef *def, b2World *world);
typedef b2Fixture* (*createBoxColliderFixtureType)(f32 x, f32 y, f32 density, f32 friction, b2Body *body);

typedef Crystal*   (*getEngineType)();

//only for editor
typedef bool (*isKeyDownType)(ButtonCode code);
