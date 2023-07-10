#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "components.hh"

namespace Component{
    void Camera::init(){
	zoomLevel = 1;
    };
    void Camera::calculateViewMat(){
	glm::mat4 t = glm::translate(glm::mat4(1.0f), pos);
	view = glm::inverse(t);
    };
    void Camera::updateZoomLevel(f32 zLevel){
	zoomLevel += zLevel;
	projection = glm::perspective(glm::radians(fieldOfView+(zoomLevel*-5)), aspectRatio, 0.1f, 100.0f);
    };
    void Camera::initPerspective(f32 fov, f32 aRatio, glm::vec3 &cameraStartPos){
	aspectRatio = aRatio;
	fieldOfView = fov;
	pos = cameraStartPos;
	projection = glm::mat4(1.0);
	projection = glm::perspective(glm::radians(fieldOfView+(zoomLevel*-5)), aspectRatio, 0.1f, 100.0f);
    };
};
namespace Component{
    void Transform::init(){mat = glm::mat4(1.0);};
    void Transform::move(glm::vec3 &pos){
	mat = glm::translate(mat, pos);
    };
    void Transform::rotate(f32 val, glm::vec3 &axis){
	mat = glm::rotate(mat, glm::radians(val), axis);
    };
};
