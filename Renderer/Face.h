#ifndef PAULENGINE_RENDERER_FACE_H_
#define PAULENGINE_RENDERER_FACE_H_

#include <array>
#include <glm/glm.hpp>

//////////////////////////////////////////////////////
//////////////////// FACE ///////////////////////////
/////////////////////////////////////////////////////

/**
 * @brief Face is a triangle that contrains the vertex indices
 */

class Face {
  public:
    // vetex indices
    std::array<int, 3> index;	
};


#endif
