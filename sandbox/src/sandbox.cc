#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "game.hh"

namespace Game{
    EXPORT void init(){
	allocAndSetCurrentScene();
	initCurrentScene(5);
	
	Entity sq = sceneNewEntity("spinny quad");
	addComponent<Component::Transform>(sq);

	Material &mat = newMaterial(1);
	
	mat.col = glm::vec4(1.0, 0.5, 1.0, 1.0);
	materialRegisterEntity(mat, sq);

	Component::Camera *cam = addComponent<Component::Camera>(sq);
        cam->initPerspective(45, 1280/720, glm::vec3(0.0f, 0.0f, 3.0f));
    };
    EXPORT void render(){
	
    };
    EXPORT void uninit(){
	uninitAndFreeCurrentScene();
    };
    EXPORT bool update(Event e, f64 dt){
	Entity sq = getEntity("spinny quad");
	auto *cam = (Component::Camera*)getComponent(sq, getID<Component::Camera>());
	setActiveCameraToCurrentScene(cam);
	auto *s1T = (Component::Transform*)getComponent(sq, getID<Component::Transform>());
	if(s1T == nullptr){return false;};
	s1T->rotation.x += dt;
	return false;
    };
};
