#pragma once

#define EXPORT extern "C" __declspec(dllexport)

#include "basic.hh"
#include "config.hh"

#include "utils.hh"
logType print;
getComponentUIDType getComponentUID;
setGameFolderType setGameFolder;
editorSignalType editorSignal;

EXPORT void setupUtilPointers(logType l, getComponentUIDType gcut, setGameFolderType sgft,
			      editorSignalType est){
    print = l;
    getComponentUID = gcut;
    setGameFolder = sgft;

    editorSignal = est;
};

#include "ds.hh"
#include "scene.hh"
#include "material.hh"
#include "event.hh"
#include "renderer.hh"

//cpp code which every game has to compile
#include "../game/include.hh"

#include "enginePointers.hh"
materialRegisterEntityType materialRegisterEntity;
newMaterialType newMaterial;

componentPoolInitType         componentPoolInit;
componentPoolNewComponentType componentPoolNewComponent;
componentPoolRemoveComponentType componentPoolRemoveComponent;
componentPoolGetComponentType componentPoolGetComponent;

allocSceneType allocScene;
freeSceneType  freeScene;
sceneInitType sceneInit;
sceneUninitType sceneUninit;
sceneNewEntityType sceneNewEntity;

setCurrentSceneType setCurrentScene;
getCurrentSceneType getCurrentScene;

getRendererType     getRenderer;
getMaterialSystemType getMaterialSystem;

isKeyDownType    isKeyDown;

EXPORT void setupPointers(materialRegisterEntityType mret, newMaterialType nmt,
			  componentPoolInitType cpit, componentPoolNewComponentType cpnct, componentPoolRemoveComponentType cprct, componentPoolGetComponentType cpgct,
			  allocSceneType ast, freeSceneType fst, sceneInitType sit, sceneUninitType sut, sceneNewEntityType snet,
			  setCurrentSceneType scst, getCurrentSceneType gcst,
			  getRendererType grt, getMaterialSystemType gmst,
			  isKeyDownType ikdt){
    
    materialRegisterEntity = mret;
    newMaterial = nmt;

    componentPoolInit         = cpit;
    componentPoolNewComponent = cpnct;
    componentPoolRemoveComponent = cprct;
    componentPoolGetComponent = cpgct;

    allocScene = ast;
    freeScene = fst;
    sceneInit = sit;
    sceneUninit = sut;
    sceneNewEntity = snet;

    setCurrentScene = scst;
    getCurrentScene = gcst;

    getRenderer = grt;
    getMaterialSystem = gmst;
    
    isKeyDown = ikdt;
};
