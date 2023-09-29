#pragma once

#define EXPORT extern "C" __declspec(dllexport)

#include "basic.hh"

#include "utils.hh"
logType print;
setGameCodeType  setGameCode;
setSceneType     setScene;
setMaterialSystemType setMaterialSystem;
editorSignalType editorSignal;

EXPORT void setupUtilPointers(logType l, setGameCodeType sgct, setSceneType sct, setMaterialSystemType smst, editorSignalType est){
    print = l;
    setGameCode = sgct;
    setScene = sct;
    setMaterialSystem = smst;

    editorSignal = est;
};

#include "map.hh"
#include "ds.hh"
#include "event.hh"
#include "layer.hh"
#include "scene.hh"
#include "material.hh"
#include "event.hh"
#include "renderer.hh"

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
sceneNewEntityType sceneNewEntity;
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
			  sceneNewEntityType snet, getEntityType get,
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
    
    sceneNewEntity = snet;
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
