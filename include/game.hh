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

sceneInitType sceneInit;
sceneUninitType sceneUninit;
sceneNewEntityType sceneNewEntity;
sceneGetEntityType sceneGetEntity;

setCurrentSceneType setCurrentScene;
getCurrentSceneType getCurrentScene;

EXPORT void setupPointers(materialInitType mit, materialUninitType mut, materialRegisterEntityType mret,
			  materialSystemInitType msit, materialSystemUninitType msut, newMaterialType nmt,
			  componentPoolInitType cpit, componentPoolNewComponentType cpnct, componentPoolRemoveComponentType cprct, componentPoolGetComponentType cpgct,
			  sceneInitType sit, sceneUninitType sut, sceneNewEntityType snet, sceneGetEntityType sget,
			  setCurrentSceneType scst,getCurrentSceneType gcst){
    
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

    sceneInit = sit;
    sceneUninit = sut;
    sceneNewEntity = snet;
    sceneGetEntity = sget;

    setCurrentScene = scst;
    getCurrentScene = gcst;
};
