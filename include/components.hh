#pragma once

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
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	void init();
	glm::mat4 genMatrix();
    };
};
