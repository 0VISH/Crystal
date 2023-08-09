#pragma once

//NOTE: all components need to have function 'init'
namespace Component{
    struct Camera{
	void init(Scene *s);
	void calculateViewMat();
	void updateZoomLevel(f32 zLevel);
	void initPerspective(f32 fov, f32 aRatio, const glm::vec3 &cameraStartPos);
    
	glm::vec3 pos;
	glm::mat4 view;
	glm::mat4 projection;
	f32 zoomLevel;
	f32 aspectRatio;
	f32 fieldOfView;
    };

    struct Transform{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	void init(Scene *s);
	glm::mat4 genMatrix();
    };

    struct RigidBody{
	void init(Scene *s);

	b2Body *runtimeBody;
	b2BodyType bodyType;
	bool fixedRotation;
    };

    struct BoxCollider{
	void init(Scene *s);

	glm::vec2 off;
	glm::vec2 size;
	b2FixtureDef* runtimeFixture;
    };
};
