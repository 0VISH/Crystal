#pragma once

#define EXPORT extern "C" __declspec(dllexport)

#include "basic.hh"

#include "utils.hh"
logType print;
setGameFolderType setGameFolder;
editorSignalType editorSignal;

EXPORT void setupUtilPointers(logType l, setGameFolderType sgft, editorSignalType est){
    print = l;
    setGameFolder = sgft;

    editorSignal = est;
};

#include "map.hh"
#include "ds.hh"
#include "scene.hh"
#include "material.hh"
#include "event.hh"
#include "renderer.hh"

#include "enginePointers.hh"


materialRegisterEntityType materialRegisterEntity;
newMaterialType newMaterial;

componentPoolInitType         componentPoolInit;
componentPoolAddComponentType componentPoolAddComponent;

allocAndSetCurrentSceneType allocAndSetCurrentScene;
uninitAndFreeCurrentSceneType uninitAndFreeCurrentScene;
serializeCurrentSceneType serializeCurrentScene;
deserializeToCurrentSceneType deserializeToCurrentScene;
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

EXPORT void setupPointers(materialRegisterEntityType mret, newMaterialType nmt,
			  componentPoolInitType cpit, componentPoolAddComponentType cpact,
			  allocAndSetCurrentSceneType ascst, uninitAndFreeCurrentSceneType ufcst,
			  initCurrentSceneType icst, setActiveCameraToCurrentSceneType sacct,
			  serializeCurrentSceneType secst, deserializeToCurrentSceneType dcst,
			  sceneNewEntityType snet, getEntityType get,
			  removeComponentType rct, getComponentType gct,
			  createRigidBodyType crbt, createBoxColliderFixtureType cbcft,
			  getEngineType gent,
			  isKeyDownType ikdt){
    
    materialRegisterEntity = mret;
    newMaterial = nmt;

    componentPoolInit         = cpit;
    componentPoolAddComponent = cpact;

    allocAndSetCurrentScene = ascst;
    uninitAndFreeCurrentScene = ufcst;
    
    initCurrentScene = icst;
    setActiveCameraToCurrentScene = sacct;
    
    serializeCurrentScene = secst;
    deserializeToCurrentScene = dcst;
    
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
