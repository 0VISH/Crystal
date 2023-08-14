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

allocSceneType allocScene;
freeSceneType  freeScene;
sceneInitType sceneInit;
sceneUninitType sceneUninit;
sceneNewEntityType sceneNewEntity;
getEntityType getEntity;
removeComponentType removeComponent;
getComponentType getComponent;

setCurrentSceneType setCurrentScene;
getCurrentSceneType getCurrentScene;

createRigidBodyType createRigidBody;
createBoxColliderFixtureType createBoxColliderFixture;

getRendererType     getRenderer;
getMaterialSystemType getMaterialSystem;

isKeyDownType    isKeyDown;

EXPORT void setupPointers(materialRegisterEntityType mret, newMaterialType nmt,
			  componentPoolInitType cpit, componentPoolAddComponentType cpact,
			  allocSceneType ast, freeSceneType fst,
			  sceneInitType sit, sceneUninitType sut, sceneNewEntityType snet, getEntityType get,
			  removeComponentType rct, getComponentType gct,
			  setCurrentSceneType scst, getCurrentSceneType gcst,
			  createRigidBodyType crbt, createBoxColliderFixtureType cbcft,
			  getRendererType grt, getMaterialSystemType gmst,
			  isKeyDownType ikdt){
    
    materialRegisterEntity = mret;
    newMaterial = nmt;

    componentPoolInit         = cpit;
    componentPoolAddComponent = cpact;

    allocScene = ast;
    freeScene = fst;
    sceneInit = sit;
    sceneUninit = sut;
    sceneNewEntity = snet;
    getEntity = get;
    removeComponent = rct;
    getComponent = gct;

    setCurrentScene = scst;
    getCurrentScene = gcst;

    createRigidBody = crbt;
    createBoxColliderFixture = cbcft;
    
    getRenderer = grt;
    getMaterialSystem = gmst;
    
    isKeyDown = ikdt;
};

//cpp code which every game has to compile
#include "../game/include.hh"

namespace Game{
    EXPORT void reload();
}
