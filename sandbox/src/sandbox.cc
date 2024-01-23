#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "game.hh"
Crystal *engine; 

namespace Game{
    EXPORT void init(){
	setMaterialSystem("sandbox/runtime/woa.ms");
	setScene("sandbox/runtime/trial.scn");
    };
    EXPORT bool trialUpdate(Event e, f64 dt){
	Entity sq = getEntity("quad");
	if(sq == -1){return false;};
	auto *cam = (Component::PCamera*)getComponent(sq, ComponentID::PCAMERA);
	setActiveCameraToCurrentScene(sq);
	auto *s1T = (Component::Transform*)getComponent(sq, ComponentID::TRANSFORM);
	if(s1T == nullptr){return false;};
	s1T->rotation.x += dt;
	return false;
    };
};
