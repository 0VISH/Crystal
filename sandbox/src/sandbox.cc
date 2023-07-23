#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "game.hh"

namespace Game{
    Scene *s;
    Entity sq;

    EXPORT void init(){
	s = allocScene();
	sceneInit(s, 5);
	setCurrentScene(s);
		
	sq = sceneNewEntity(s);
        s->addComponent<Component::Transform>(sq);

	MaterialSystem *ms = getMaterialSystem();
	Material &mat = newMaterial(ms, 0);
	
	mat.col = glm::vec4(1.0, 0.5, 1.0, 1.0);
	materialRegisterEntity(mat, sq);

	Renderer *r = getRenderer();
	useMaterial(r, &mat);
    };
    EXPORT void render(){
	Renderer *r = getRenderer();
	Component::Transform *s1T = s->getComponent<Component::Transform>(sq);
	submitQuad(r, s1T->genMatrix());

	r->bufferEmpty = false;
    };
    EXPORT void uninit(){

    };
    EXPORT bool update(Event e, f64 dt){
	Component::Transform *s1T = s->getComponent<Component::Transform>(sq);
	s1T->rotation.x += dt;
	return false;
    };
};
