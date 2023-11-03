#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "components.hh"
#include "componentID.hh"

namespace Component{
    void PCamera::calculateProjectionMat(){
	projection = glm::perspective(glm::radians(fieldOfView+(zoomLevel*-5)), aspectRatio, 0.1f, 100.0f);
    };
    void PCamera::initPerspective(f32 fov, f32 aRatio, const glm::vec3 &cameraStartPos){
	aspectRatio = aRatio;
	fieldOfView = fov;
	pos = cameraStartPos;
	calculateProjectionMat();
    };
    void PCamera::init(Scene *s, Entity e){
	zoomLevel = 1;
	initPerspective(45, (f32)engine->windowX/(f32)engine->windowY, glm::vec3(0.0f, 0.0f, 3.0f));
    };
    void PCamera::calculateViewMat(){
	glm::mat4 t = glm::translate(glm::mat4(1.0f), pos);
	view = glm::inverse(t);
    };
    void PCamera::changeZoomLevel(f32 zLevel){
	zoomLevel = zLevel;
	calculateProjectionMat();
    };
    void PCamera::changeFOV(f32 fov){
	fieldOfView = fov;
	calculateProjectionMat();
    };
    void PCamera::changeARatio(f32 aRatio){
	aspectRatio = aRatio;
	calculateProjectionMat();
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
    void RigidBody::initMore(Scene *s, Entity e){
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.fixedRotation = fixedRotation;
	auto *transform = (Component::Transform*)getComponent(e, (u32)ComponentID::TRANSFORM);
	if(transform == nullptr){
	    bodyDef.position.Set(0.0f, 0.0f);
	}else{
	    bodyDef.position.Set(transform->position.x, transform->position.y);
	};
	runtimeBody = createRigidBody(&bodyDef, s->physicsWorld);
    };
    void RigidBody::init(Scene *s, Entity e){
	bodyType = b2_dynamicBody;
	fixedRotation = false;
	initMore(s, e);
    };
};

template<typename T>
T *addComponent(Entity e, ComponentID id);

namespace Component{
    void BoxCollider::initMore(Scene *s, Entity e){
	auto *rigidBody = (Component::RigidBody*)getComponent(e, (u32)ComponentID::RIGIDBODY);
	if(rigidBody == nullptr){
	    rigidBody = addComponent<Component::RigidBody>(e, ComponentID::RIGIDBODY);
	};
	b2Body *body = rigidBody->runtimeBody;
	auto *transform = (Component::Transform*)getComponent(e, (u32)ComponentID::RIGIDBODY);
	//TODO: change x,y
	if(transform == nullptr){
	    runtimeFixture = createBoxColliderFixture(5.0f, 5.0f, density, friction, body);
	}else{
	    runtimeFixture = createBoxColliderFixture(5, 5, density, friction, body);
	};
    };
    void BoxCollider::init(Scene *s, Entity e){
	friction = 0.3f;
	density = 1.0f;
	initMore(s, e);
    };
};

