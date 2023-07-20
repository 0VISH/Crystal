#pragma once

#define EXPORT extern "C" __declspec(dllexport)

#include "basic.hh"
#include "config.hh"

#include "utils.hh"
logType print;
EXPORT void setupUtilPointers(logType l){
    print = l;
};

#include "mem.cc"
#include "ds.hh"
#include "components.cc"
#include "material.hh"
#include "scene.cc"
#include "event.hh"

#include "gamee.hh"
materialInitType materialInit;
materialUninitType materialUninit;
materialRegisterEntityType materialRegisterEntity;

materialSystemInitType materialSystemInit;
materialSystemUninitType materialSystemUninit;
newMaterialType newMaterial;

EXPORT void setupPointers(materialInitType mit, materialUninitType mut, materialRegisterEntityType mret,
			  materialSystemInitType msit, materialSystemUninitType msut, newMaterialType nmt){
    
    materialInit = mit;
    materialUninit = mut;
    materialRegisterEntity = mret;

    materialSystemInit = msit;
    materialSystemUninit = msut;
    newMaterial = nmt;
};
