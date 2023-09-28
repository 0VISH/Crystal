#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "game.hh"

namespace Game{
    EXPORT void uninit(){
	uninitAndFreeCurrentScene();
    };
    EXPORT bool update(Event e, f64 dt){
	Entity sq = getEntity("spinny quad");
	auto *cam = (Component::PCamera*)getComponent(sq, (u32)ComponentID::CAMERA);
	setActiveCameraToCurrentScene(sq);
	auto *s1T = (Component::Transform*)getComponent(sq, (u32)ComponentID::TRANSFORM);
	if(s1T == nullptr){return false;};
	s1T->rotation.x += dt;
	return false;
    };
};
