#pragma once

#include "crystal.hh"
#include "log.hh"
#include "mem.hh"
#include "ds.hh"
#include "components.hh"
#include "material.hh"
#include "scene.hh"
#include "renderer.hh"
#include "event.hh"
#include "shaderSystem.hh"

namespace Cry{
    ShaderSystem &getShaderSystemRef();
    MaterialSystem &getMaterialSystemRef();
};

namespace Game{
    Scene **engineScenePointer;
    
    void setCurrentScene(Scene *s){
	*engineScenePointer = s;
    };

    //char *gameName
};
