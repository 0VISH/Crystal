#pragma once

//NOTE: all components need to have function 'init'
namespace Component{
    struct Camera{
	void init(Scene *s, Entity e);
	void calculateViewMat();
	void updateZoomLevel(f32 zLevel);
	void initPerspective(f32 fov, f32 aRatio, const glm::vec3 &cameraStartPos);

	glm::mat4 projection;
	glm::mat4 view;
	glm::vec3 pos;
	f32 zoomLevel;
	f32 aspectRatio;
	f32 fieldOfView;
    };

    struct Transform{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	void init(Scene *s, Entity e);
	glm::mat4 genMatrix();
    };

    struct RigidBody{
	void init(Scene *s, Entity e);

	b2Body *runtimeBody;
	b2BodyType bodyType;
	bool fixedRotation;
    };

    struct BoxCollider{
	void init(Scene *s, Entity e);

	//TODO: off, size
	f32 friction;
	f32 density;
	b2Fixture* runtimeFixture;
    };
};
