#pragma once

#define EXPORT extern "C" __declspec(dllexport)

#include "basic.hh"
#include "config.hh"

#include "utils.hh"
logType print;
getComponentUIDType getComponentUID;
setGameFolderType setGameFolder;

EXPORT void setupUtilPointers(logType l, getComponentUIDType gcut, setGameFolderType sgft){
    print = l;
    getComponentUID = gcut;
    setGameFolder = sgft;
};

#include "mem.cc"
#include "ds.hh"
#include "components.cc"
#include "material.hh"
#include "scene.hh"
#include "event.hh"

#include "gamee.hh"
materialInitType materialInit;
materialUninitType materialUninit;
materialRegisterEntityType materialRegisterEntity;

materialSystemInitType materialSystemInit;
materialSystemUninitType materialSystemUninit;
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

editorSignalType  editorSignal;

EXPORT void setupPointers(materialInitType mit, materialUninitType mut, materialRegisterEntityType mret,
			  materialSystemInitType msit, materialSystemUninitType msut, newMaterialType nmt,
			  componentPoolInitType cpit, componentPoolNewComponentType cpnct, componentPoolRemoveComponentType cprct, componentPoolGetComponentType cpgct,
			  allocSceneType ast, freeSceneType fst, sceneInitType sit, sceneUninitType sut, sceneNewEntityType snet,
			  setCurrentSceneType scst,getCurrentSceneType gcst,
			  editorSignalType est){
    
    materialInit = mit;
    materialUninit = mut;
    materialRegisterEntity = mret;

    materialSystemInit = msit;
    materialSystemUninit = msut;
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
    editorSignal = est;
};
