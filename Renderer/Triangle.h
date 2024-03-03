#ifndef PAULENGINE_RENDERER_TRIANGLE_H_
#define PAULENGINE_RENDERER_TRIANGLE_H_

#include <array>
#include <glm/glm.hpp>


//////////////////////////////////////////////////////
///////// TRIANGLE /////////////////////////
/////////////////////////////////////////////////////

//Mesh --> Triangles --> Vertices coordinates ex x,y,z,w)
//		     --> Faces(vertex indices (a,b,c) ) 
//                   --> color
class Triangle {
  public:
    std::array<glm::vec3, 3> vertices;
    double color;
    // texture
    //std::array<glm::vec2,3> texture_coords;
		
};

#endif
