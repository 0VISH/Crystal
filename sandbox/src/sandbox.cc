#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "game.hh"

namespace Game{
    Scene s;

    EXPORT void init(){
	s.init();
    };
    EXPORT void render(){
    };
    EXPORT void uninit(){
	s.uninit();
    };
    EXPORT bool update(Event e, f64 dt){
	return false;
    };
};
