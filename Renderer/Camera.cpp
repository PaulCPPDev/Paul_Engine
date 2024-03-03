/**
 * @file Camera.cpp
 * @author Paul Gregor
 * @brief Implements Camera movement and making the camera look at a target
 * @version 0.1
 * @date 14.02.2024
 * @copyright University of Bern Applied Sciences
 */

#include "Renderer/Camera.h"



namespace camera {

glm::mat4 Camera::look_at(glm::vec3 eye, glm::vec3 target, glm::vec3 up){
  // Compute the forward (z), right (x), and up (y) vectors
  glm::vec3 z = glm::normalize(target - eye);
  glm::vec3 x = glm::normalize(glm::cross(up, z));
  glm::vec3 y = glm::normalize(glm::cross(z, x));

  // | x.x   x.y   x.z  -dot(x,eye) |
  // | y.x   y.y   y.z  -dot(y,eye) |
  // | z.x   z.y   z.z  -dot(z,eye) |
  // |   0     0     0            1 |
    
  glm::mat4 view_matrix(
    x.x, y.x, z.x, 0.0f,
    x.y, y.y, z.y, 0.0f,
    x.z, y.z, z.z, 0.0f,
    -glm::dot(x, eye), -glm::dot(y, eye), -glm::dot(z, eye), 1.0f
  );
    
  return view_matrix;
}

glm::vec3 Camera::get_FPS_target(){
  // Initialize the target looking at the positive z-axis
  glm::vec3 target(0, 0, 1 );
    
  glm::mat4 camera_pitch_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(this->orientation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 camera_yaw_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(this->orientation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 camera_rotation = camera_yaw_rotation * camera_pitch_rotation;

  // Update camera direction based on the rotation
  this->direction = glm::vec3(camera_rotation *  glm::vec4(target, 1.0f));
    
  // Offset the camera position in the direction where the camera is pointing at
  target = this->position + this->direction;

  return target;
}

} // namespace camera
