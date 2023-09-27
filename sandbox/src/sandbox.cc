#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "game.hh"

namespace Game{
    EXPORT void init(){
	Crystal *engine = getEngine();
	allocAndSetCurrentScene();
	initCurrentScene(5);
	
	Entity sq = sceneNewEntity("spinny quad");
	addComponent<Component::Transform>(sq, ComponentID::TRANSFORM);

	Material &mat = newMaterial("spinny mat", 1);
	
	mat.col = glm::vec4(1.0, 0.5, 1.0, 1.0);
	materialRegisterEntity(mat, sq);

	Component::PCamera *cam = addComponent<Component::PCamera>(sq, ComponentID::CAMERA);
        cam->initPerspective(45, 1280/720, glm::vec3(0.0f, 0.0f, 3.0f));
    };
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
