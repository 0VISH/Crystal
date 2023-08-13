#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "game.hh"

namespace Game{
    Scene *s;

    EXPORT void reload(){
	s = getCurrentScene();
    };
    
    EXPORT void init(){
	s = allocScene();
	sceneInit(s, 5);
	setCurrentScene(s);
		
	Entity sq = sceneNewEntity(s, "spinny quad");
	addComponent<Component::Transform>(s, sq);

	MaterialSystem *ms = getMaterialSystem();
	Material &mat = newMaterial(ms, 1);
	
	mat.col = glm::vec4(1.0, 0.5, 1.0, 1.0);
	materialRegisterEntity(mat, sq);

	Renderer *r = getRenderer();

	Component::Camera *cam = addComponent<Component::Camera>(s, sq);
        cam->initPerspective(45, 1280/720, glm::vec3(0.0f, 0.0f, 3.0f));
    };
    EXPORT void render(){
	Renderer *r = getRenderer();
	MaterialSystem *ms = getMaterialSystem();

	Entity sq = getEntity(s, "spinny quad");
	Component::Camera *cam = s->getComponent<Component::Camera>(sq);
	cam->calculateViewMat();
	
	fillRenderBufferHeader(r, cam->projection * cam->view);
	fillRenderBufferWithGivenMS(r, ms, s);
    };
    EXPORT void uninit(){
	sceneUninit(s);
	freeScene(s);
    };
    EXPORT bool update(Event e, f64 dt){
	Entity sq = getEntity(s, "spinny quad");
	Component::Transform *s1T = s->getComponent<Component::Transform>(sq);
	if(s1T == nullptr){return false;};
	s1T->rotation.x += dt;
	return false;
    };
};
