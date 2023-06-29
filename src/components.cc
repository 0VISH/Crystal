#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

typedef u32 Entity;

//NOTE: all components need to have function 'init'
namespace Component{
    struct Camera{
	void init(){
	    zoomLevel = 1;
	};
	void calculateViewMat(){
	    glm::mat4 t = glm::translate(glm::mat4(1.0f), pos);
	    view = glm::inverse(t);
	};
	void updateZoomLevel(f32 zLevel){
	    zoomLevel += zLevel;
	    projection = glm::perspective(glm::radians(fieldOfView+(zoomLevel*-5)), aspectRatio, 0.1f, 100.0f);
	};
	void initPerspective(f32 fov, f32 aRatio, glm::vec3 &cameraStartPos){
	    aspectRatio = aRatio;
	    fieldOfView = fov;
	    pos = cameraStartPos;
	    projection = glm::mat4(1.0);
	    projection = glm::perspective(glm::radians(fieldOfView+(zoomLevel*-5)), aspectRatio, 0.1f, 100.0f);
	};
    
	glm::vec3 pos;
	glm::mat4 view;
	glm::mat4 projection;
	f32 zoomLevel;
	f32 aspectRatio;
	f32 fieldOfView;
    };

    struct Transform{
	glm::mat4 mat;

	void init(){mat = glm::mat4(1.0);};
	void move(glm::vec3 &pos){
	    mat = glm::translate(mat, pos);
	};
	void rotate(f32 val, glm::vec3 &axis){
	    mat = glm::rotate(mat, glm::radians(val), axis);
	};
    };
};
