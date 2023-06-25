#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

struct Camera{
    void calculateViewMat(){
	glm::mat4 t = glm::translate(glm::mat4(1.0f), pos);
	view = glm::inverse(t);
    };
    void initPerspective(f32 fov, f32 aspectRatio, f32 near, f32 far, glm::vec3 &cameraStartPos){
	pos = cameraStartPos;
	projection = glm::mat4(1.0);
	projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
    };
    
    glm::vec3 pos;
    glm::mat4 view;
    glm::mat4 projection;
};
