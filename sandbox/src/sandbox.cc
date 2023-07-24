#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "game.hh"

namespace Game{
    Scene *s;
    Entity sq;
    Component::Camera cam;

    EXPORT void init(){
	s = allocScene();
	sceneInit(s, 5);
		
	sq = sceneNewEntity(s);
        auto t = s->addComponent<Component::Transform>(sq);

	MaterialSystem *ms = getMaterialSystem();
	Material &mat = newMaterial(ms, 1);
	
	mat.col = glm::vec4(1.0, 0.5, 1.0, 1.0);
	materialRegisterEntity(mat, sq);

	Renderer *r = getRenderer();

	cam.init();
        cam.initPerspective(45, 1280/720, glm::vec3(0.0f, 0.0f, 3.0f));
    };
    EXPORT void render(){
	Renderer *r = getRenderer();
	MaterialSystem *ms = getMaterialSystem();
	
	cam.calculateViewMat();
	
	fillRenderBufferHeader(r, cam.projection * cam.view);
	fillRenderBufferWithGivenMS(r, ms, s);
    };
    EXPORT void uninit(){
	sceneUninit(s);
	freeScene(s);
    };
    EXPORT bool update(Event e, f64 dt){
	Component::Transform *s1T = s->getComponent<Component::Transform>(sq);
	s1T->rotation.x += dt;
	return false;
    };
};
