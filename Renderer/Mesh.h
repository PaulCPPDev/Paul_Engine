#ifndef PAULENGINE_RENDERER_MESH_H_
#define PAULENGINE_RENDERER_MESH_H_

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Triangle.h"
#include "Face.h"

//////////////////////////////////////////////////////
///////// Mesh /////////////////////////
/////////////////////////////////////////////////////

class Mesh {
  public:
    std::vector<glm::vec3> vertices;
    std::vector<Triangle> triangles;
    std::vector<Face> faces;
    glm::vec3 scale;
    glm::vec3 rotate;
    glm::vec3 translate;
		
		
    Mesh() = default;
    void load_cube_mesh_data(void);
    void load_obj_file(const std::string& path);
};

#endif
