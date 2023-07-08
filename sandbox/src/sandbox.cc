#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Game{
    Scene s;
    Entity s1;
    Batch::Batcher b;
    
    void init(){
	engine->r.drawWireframe();
	
	s.init();
	
	s1 = s.newEntity();
	Component::Transform *s1T = s.addComponent<Component::Transform>(s1);
	
	Material &mat = engine->ms.newMaterial();
	mat.col = glm::vec4(1.0, 0.5, 1.0, 1.0);
	mat.registerEntity(s1);
	
	b.init(engine->r.shaderProgram);
	b.setMaterial(&mat);
    };
    void render(){
	engine->fb.bind();
	engine->r.clearColourBuffer();
        s.render(engine->ms, engine->r);

	glm::mat4 t1 = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 t2 = glm::translate(glm::mat4(1.0), glm::vec3(0.0, -1.0, 0.0));
	b.beginBatch();
	b.submitQuad(t1);
	b.submitQuad(t2);
	b.endBatch();
	b.flush();
	
	engine->fb.unbind();
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
