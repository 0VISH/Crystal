#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "game.hh"

namespace Game{
    Scene s;

    void init(){
	engine->curScene = &s;
	
	s.init();
	
	Entity s1 = s.newEntity("spinny quad");
	Component::Transform *s1T = s.addComponent<Component::Transform>(s1);
	
	Material &mat = engine->ms.newMaterial(engine->ss.getDefaultShader());
	mat.col = glm::vec4(1.0, 0.5, 1.0, 1.0);
	mat.registerEntity(s1);
    };
    void render(){
        s.render(engine->ms, engine->fb);
    };
    void uninit(){
	s.uninit();
    };
    bool update(Event e, f64 dt){
	Entity s1 = s.getEntity("spinny quad");
	Component::Transform *s1T = s.getComponent<Component::Transform>(s1);
	s1T->rotation.x += dt;
	return false;
    };

    char *gameName = "Sandbox";
};
