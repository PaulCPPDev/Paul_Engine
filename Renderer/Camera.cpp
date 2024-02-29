/**
 * @file Camera.cpp
 * @author Paul Gregor
 * @brief Implements Camera movement and making the camera look at a target
 * @version 0.1
 * @date 14.02.2024
 * @copyright University of Bern Applied Sciences
 */

#include "Camera.h"

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
