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
		Camera() = default;
		glm::vec3 position;
		glm::vec3 orientation;
		glm::vec3 view;
		glm::vec3 direction;
		
		void look_at(glm::vec3 target, glm::vec3 up);

};

#endif
