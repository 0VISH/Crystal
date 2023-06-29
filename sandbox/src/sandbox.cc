#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Game{
    Scene s;
    Entity s1;
    
    void init(){
	engine->r.drawWireframe();
	
	s.init();
	
	s1 = s.newEntity();
	Component::Transform *s1T = s.addComponent<Component::Transform>(s1);
	
	Material &mat = engine->ms.newMaterial();
	mat.col = glm::vec4(1.0, 0.5, 1.0, 1.0);
	mat.registerEntity(s1);
    };
    void render(){
	s.render(engine->ms, engine->r);
    };
    void uninit(){
	s.uninit();
    };
    bool update(Event e, f64 dt){
	Component::Transform *s1T = s.getComponent<Component::Transform>(s1);
	s1T->rotate(5, glm::vec3(1, 0.0, 0.0));
	return false;
    };

    char* gameName  = "Sandbox";
};
