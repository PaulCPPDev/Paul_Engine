/**
 * @file Mesh.cpp
 * @author Paul Gregor
 * @brief Implements how meshes work
 * @version 0.1
 * @date 14.02.2024
 * @copyright University of Bern Applied Sciences
 */

#include "Mesh.h"
#include <algorithm>
#include <fstream> 
#include <iostream>
#include <sstream>
#define N_CUBE_TRIANGLES 12
#define N_CUBE_VERTEX_COORD 8


//cube vertex coords
std::array<glm::vec3, N_CUBE_VERTEX_COORD> cube_vertex_coords = {
  glm::vec3(-1, -1, -1 ), // 1
  glm::vec3(-1, 1, -1 ), // 2
  glm::vec3(1, 1, -1 ), // 3
  glm::vec3(1, -1, -1 ), // 4
  glm::vec3(1, 1, 1 ), // 5
  glm::vec3(1, -1, 1 ), // 6
  glm::vec3(-1, 1, 1 ), // 7
  glm::vec3(-1, -1, 1 )  // 8
};

/*
vec3_t cube_vertices[N_CUBE_VERTICES] = {
    { .x = -1, .y = -1, .z = -1 }, // 1
    { .x = -1, .y =  1, .z = -1 }, // 2
    { .x =  1, .y =  1, .z = -1 }, // 3
    { .x =  1, .y = -1, .z = -1 }, // 4
    { .x =  1, .y =  1, .z =  1 }, // 5
    { .x =  1, .y = -1, .z =  1 }, // 6
    { .x = -1, .y =  1, .z =  1 }, // 7
    { .x = -1, .y = -1, .z =  1 }  // 8
};
*/


//cube triangles
uint32_t cube_triangles_indices[N_CUBE_TRIANGLES][3] = {
    // front
    {1, 2, 3},
    {1, 3, 4 },
    // right
    {4, 3, 5},
    {4, 5, 6 },
    // back
    {6, 5, 7 },
    { 6, 7, 8 },
    // left
    { 8, 7, 2 },
    {8, 2, 1 },
    // top
    { 2, 7, 5 },
    { 2, 5, 3 },
    // bottom
    { 6, 8, 1 },
    {6, 1, 4 }	
};

/*
face_t cube_faces[N_CUBE_FACES] = {
    // front
    { .a = 1, .b = 2, .c = 3 },
    { .a = 1, .b = 3, .c = 4 },
    // right
    { .a = 4, .b = 3, .c = 5 },
    { .a = 4, .b = 5, .c = 6 },
    // back
    { .a = 6, .b = 5, .c = 7 },
    { .a = 6, .b = 7, .c = 8 },
    // left
    { .a = 8, .b = 7, .c = 2 },
    { .a = 8, .b = 2, .c = 1 },
    // top
    { .a = 2, .b = 7, .c = 5 },
    { .a = 2, .b = 5, .c = 3 },
    // bottom
    { .a = 6, .b = 8, .c = 1 },
    { .a = 6, .b = 1, .c = 4 }
};
*/


///******** WORKS PERFECT

void Mesh::load_cube_mesh_data(void) {
    // store all the vertices in the mesh->vertices
    for (int i = 0; i < N_CUBE_VERTEX_COORD; i++) {
        glm::vec3 cube_vertex = cube_vertex_coords[i];
        this->vertices.push_back(cube_vertex);
    }
	
    // store all triangle information in the mesht->triangles
    for (int i = 0; i < N_CUBE_TRIANGLES; i++) {
    	// Create triangle
    	Triangle cube_triangle;
    	Face cube_face;
    	//get vertex indices
    	for(int j = 0; j < 3 ; j++){
    		// store face indices
    		cube_face.index[j] = cube_triangles_indices[i][j];
    		//cube_triangle.vertices[j].index = cube_triangles_indices[i][j];
    		
    		// store the vertex coordinates in the triangle
    		cube_triangle.vertices[j] = this->vertices[cube_face.index[j] -1 ];
    		
    		// we subtract one bcz the obj file starts at 1
    		//cube_triangle.vertices[j].coord = this->vertices[ cube_triangle.vertices[j].index -1];
    	}
    	// push the triangle to the vector of triangles
    	this->triangles.push_back(cube_triangle);
    }
    
}


void Mesh::load_obj_file(const std::string& path){
  std::ifstream file(path);
    
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file " << path << std::endl;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string token;
    iss >> token;

    if (token == "v") {
      glm::vec3 vertex;
      iss >> vertex.x >> vertex.y >> vertex.z;
      vertices.push_back(vertex);
    } else if (token == "f") {
      // Create triangle
      Triangle cube_triangle;
      Face cube_face;
      //get vertex indices
      for(int j = 0; j < 3 ; j++){
        char separator;
	float garbage;
	iss >> cube_face.index[j] >> separator
	    >> garbage >> separator
	    >> garbage;
	// we subtract one bcz the obj file starts at 1
	cube_triangle.vertices[j] = this->vertices[ cube_face.index[j] -1];
	}
	// push the triangle to the vector of triangles
	triangles.emplace_back(cube_triangle);
	}
        
      else {}
  }

  file.close();
}



