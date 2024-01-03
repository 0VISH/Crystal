#pragma once

//@ignore
#if(__clang__)
#pragma clang diagnostic ignored "-Wwritable-strings"
#pragma clang diagnostic ignored "-Wswitch"
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

#if(WIN)
#define EXPORT extern "C" __declspec(dllexport)
#elif(AND)
#define EXPORT extern "C"
#else
#define EXPORT
#endif

#define GAME true

#include "basic.hh"

#include "utils.hh"
logType print;
setGameCodeType  setGameCode;
setSceneType     setScene;
setMaterialSystemType setMaterialSystem;
editorSignalType editorSignal;

EXPORT void setupUtilPointers(logType l, setGameCodeType sgct, setSceneType sct, setMaterialSystemType smst,  editorSignalType est){
    print = l;
    setGameCode = sgct;
    setScene = sct;
    setMaterialSystem = smst;

    editorSignal = est;
};

#include "../src/mem.cc"
#include "event.hh"
#include "layer.hh"
#include "scene.hh"
#include "material.hh"
#include "event.hh"
#include "renderer.hh"
#include "componentID.hh"

#include "enginePointers.hh"
materialRegisterEntityType materialRegisterEntity;
newMaterialType newMaterial;
serializeMaterialSystemType serializeMaterialSystem;
deserializeMaterialSystemType deserializeMaterialSystem;

componentPoolInitType         componentPoolInit;
componentPoolAddComponentType componentPoolAddComponent;

allocAndSetCurrentSceneType allocAndSetCurrentScene;
uninitAndFreeCurrentSceneType uninitAndFreeCurrentScene;
serializeCurrentSceneType serializeCurrentScene;
initCurrentSceneType initCurrentScene;
setActiveCameraToCurrentSceneType setActiveCameraToCurrentScene;
newEntityType newEntity;
getEntityType getEntity;
removeComponentType removeComponent;
getComponentType getComponent;

createRigidBodyType createRigidBody;
createBoxColliderFixtureType createBoxColliderFixture;

getEngineType getEngine;

isKeyDownType    isKeyDown;

EXPORT void setupPointers(materialRegisterEntityType mret, newMaterialType nmt, serializeMaterialSystemType smst, deserializeMaterialSystemType dmst,
			  componentPoolInitType cpit, componentPoolAddComponentType cpact,
			  allocAndSetCurrentSceneType ascst, uninitAndFreeCurrentSceneType ufcst,
			  initCurrentSceneType icst, setActiveCameraToCurrentSceneType sacct,
			  serializeCurrentSceneType secst,
			  newEntityType net, getEntityType get,
			  removeComponentType rct, getComponentType gct,
			  createRigidBodyType crbt, createBoxColliderFixtureType cbcft,
			  getEngineType gent,
			  isKeyDownType ikdt){
    
    materialRegisterEntity = mret;
    newMaterial = nmt;
    serializeMaterialSystem = smst;
    deserializeMaterialSystem = dmst;

    componentPoolInit         = cpit;
    componentPoolAddComponent = cpact;

    allocAndSetCurrentScene = ascst;
    uninitAndFreeCurrentScene = ufcst;
    
    initCurrentScene = icst;
    setActiveCameraToCurrentScene = sacct;
    
    serializeCurrentScene = secst;
    
    newEntity = net;
    getEntity = get;
    
    removeComponent = rct;
    getComponent = gct;

    createRigidBody = crbt;
    createBoxColliderFixture = cbcft;

    getEngine = gent;
    
    isKeyDown = ikdt;
};

//cpp code which every game has to compile
#include "../game/include.hh"

namespace Game{
    EXPORT void reload();
}
