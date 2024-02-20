#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>
#include <glm/glm.hpp>




struct Vertex{
	uint32_t index;		  // store the index of every vertex
	glm::vec3 coord;	  // stores the (x,y,z,w) coordinates of each vertex vec4
	//glm::vec2 texture_coord;  // store vertex texture coordinates 
	// color for smooth shading
};

//////////////////////////////////////////////////////
///////// TRIANGLE /////////////////////////
/////////////////////////////////////////////////////

//Mesh --> Triangles --> Vertices --> (index.(a,b,c), coordinates ex x,y,z,w)
//                   --> color
class Triangle {
	public:
		// vetices
		std::array<Vertex, 3> vertices;
		// color
		
};

#endif
