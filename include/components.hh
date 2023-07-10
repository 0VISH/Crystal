#pragma once

typedef u32 Entity;

//NOTE: all components need to have function 'init'
namespace Component{
    struct Camera{
	void init();
	void calculateViewMat();
	void updateZoomLevel(f32 zLevel);
	void initPerspective(f32 fov, f32 aRatio, glm::vec3 &cameraStartPos);
    
	glm::vec3 pos;
	glm::mat4 view;
	glm::mat4 projection;
	f32 zoomLevel;
	f32 aspectRatio;
	f32 fieldOfView;
    };

    struct Transform{
	glm::mat4 mat;

	void init();
	void move(glm::vec3 &pos);
	void rotate(f32 val, glm::vec3 &axis);
    };
};
