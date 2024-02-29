#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//////////////////////////////////////////////////////
///////// Camera /////////////////////////
/////////////////////////////////////////////////////

//POV - D
class Camera {
	public:
		Camera(){
			this->position = glm::vec3(0,0, 0);
			this->direction = glm::vec3(0, 0, 1);
			this->orientation = glm::vec3(0,0, 0);
		};
		glm::vec3 position;
		glm::vec3 orientation;
		glm::vec3 velocity;
		glm::vec3 direction;
		
		glm::mat4 look_at(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
		glm::vec3 get_FPS_target();

};

#endif
