#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Game{
    void init(){
	engine->r.drawWireframe();
    };
    void render(){
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	engine->r.setMat4Uniform(model, "uModel");

	engine->r.drawQuad();
    };
    void uninit(){
    };
    bool update(Event e){
	return false;
    };

    char* gameName  = "Sandbox";
};
