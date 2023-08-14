#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "components.hh"

namespace Component{
    void Camera::init(Scene *s, Entity e){
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
    void Camera::initPerspective(f32 fov, f32 aRatio, const glm::vec3 &cameraStartPos){
	aspectRatio = aRatio;
	fieldOfView = fov;
	pos = cameraStartPos;
	projection = glm::mat4(1.0);
	projection = glm::perspective(glm::radians(fieldOfView+(zoomLevel*-5)), aspectRatio, 0.1f, 100.0f);
    };
};
namespace Component{
    void Transform::init(Scene *s, Entity e){
	position = {0, 0, 0};
	rotation = {0, 0, 0};
	scale    = {1, 1, 1};
    };

    glm::mat4 Transform::genMatrix(){
	glm::mat4 rot = glm::rotate(glm::mat4(1.0), rotation.x, {1, 0, 0})
	    * glm::rotate(glm::mat4(1.0), rotation.y, {0, 1, 0})
	    * glm::rotate(glm::mat4(1.0), rotation.z, {0, 0, 1});

	return glm::translate(glm::mat4(1.0), position)
	    * rot
	    * glm::scale(glm::mat4(1.0), scale);
    };
};

namespace Component{
    void RigidBody::init(Scene *s, Entity e){
	bodyType = b2_dynamicBody;
	fixedRotation = false;

	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.fixedRotation = fixedRotation;
	auto *transform = (Component::Transform*)getComponent(s, e, getID<Component::Transform>());
	if(transform == nullptr){
	    bodyDef.position.Set(0.0f, 0.0f);
	}else{
	    bodyDef.position.Set(transform->position.x, transform->position.y);
	};
	runtimeBody = createRigidBody(&bodyDef, s->physicsWorld);
    };
};

namespace Component{
    void BoxCollider::init(Scene *s, Entity e){
	friction = 1.3;
	density = 1;

	auto *rigidBody = (Component::RigidBody*)getComponent(s, e, getID<Component::RigidBody>());
	if(rigidBody == nullptr){
	    rigidBody = addComponent<Component::RigidBody>(s, e);
	};
	b2Body *body = rigidBody->runtimeBody;
	
	auto *transform = (Component::Transform*)getComponent(s, e, getID<Component::Transform>());
	if(transform == nullptr){
	    runtimeFixture = createBoxColliderFixture(0.0f, 0.0f, density, friction, body);
	}else{
	    runtimeFixture = createBoxColliderFixture(transform->position.x * transform->scale.x, transform->position.y * transform->position.y, density, friction, body);
	};
    };
};
