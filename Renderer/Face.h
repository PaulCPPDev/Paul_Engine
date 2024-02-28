#ifndef FACE_H
#define FACE_H

#include <array>
#include <glm/glm.hpp>

//////////////////////////////////////////////////////
//////////////////// FACE ///////////////////////////
/////////////////////////////////////////////////////

//Mesh --> Triangles --> Vertices --> (index.(a,b,c), coordinates ex x,y,z,w)
//                   --> color
class Face {
	public:
		// vetex indices
		std::array<int, 3> index;
		
};

#endif
