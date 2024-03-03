#ifndef PAULENGINE_RENDERER_LIGHT_H_
#define PAULENGINE_RENDERER_LIGHT_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//////////////////////////////////////////////////////
///////// LIGHT /////////////////////////
/////////////////////////////////////////////////////

/**
 * @brief For Global illumination in our game world.
 */
class Light {
  public:	
    glm::vec3 direction;
    glm::vec3 position;
		
    Light(glm::vec3 direction){
    this->direction = direction;
    this->position = glm::vec3(0,0,0);
    }
		
    uint32_t apply_light_intensity(uint32_t original_color, float factor);
};

#endif
