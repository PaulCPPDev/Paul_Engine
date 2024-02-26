#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Triangle.h"
// #include "Face.h"

//////////////////////////////////////////////////////
///////// Mesh /////////////////////////
/////////////////////////////////////////////////////

//Mesh --> Triangles --> Vertices --> (index, coordinates ex x,y,z,w);
class Mesh {
	public:
		std::vector<glm::vec3> vertices;
		std::vector<Triangle> triangles;
		glm::vec3 scale;
		glm::vec3 rotate;
		glm::vec3 translate;
		
		
		Mesh() = default;
		void load_cube_mesh_data(void);
		void load_obj_file(const std::string& path);
		

};

#endif
