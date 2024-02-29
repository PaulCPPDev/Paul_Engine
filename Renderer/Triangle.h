#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>
#include <glm/glm.hpp>



/*
struct Vertex{
	uint32_t index;		  // store the index of every vertex
	glm::vec3 points;	  // stores the (x,y,z,w) coordinates of each vertex vec4
	//glm::vec2 texture_coord;  // store vertex texture coordinates 
	// color for smooth shading
};*/

//////////////////////////////////////////////////////
///////// TRIANGLE /////////////////////////
/////////////////////////////////////////////////////

//Mesh --> Triangles --> Vertices coordinates ex x,y,z,w)
//		     --> Faces(vertex indices (a,b,c) ) 
//                   --> color
class Triangle {
	public:
		// vetices
		std::array<glm::vec3, 3> vertices;
		double color;
		// texture
		//std::array<glm::vec2,3> texture_coords;
		
};

#endif
