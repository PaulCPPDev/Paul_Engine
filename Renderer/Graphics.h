#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <SDL2/SDL.h>
#include "Display.h"
#include "Camera.h"
#include "Clipping.h"
#include "Light.h"
#include "Mesh.h"
#include "Triangle.h"

//////////////////////////////////////////////////////
///////// Provided Interface /////////////////////////
/////////////////////////////////////////////////////

class Graphics {
	public:
		bool isRunning = true;

		Display* display = NULL;
		std::vector<Mesh> meshes;
		Camera* camera;
		Light* light;
		
		glm::mat4 proj_matrix;		
		// refactor
		std::vector<Triangle> triangles_to_render;
		int triangles_to_render_count = 0;
		

	public:
		Graphics()= default;
		~Graphics() = default;
		
		void init();
		void set_up();
		bool is_running();
                void process_input();
                void update();
                void render();
                void destroy();
                void pipeline(Mesh& mesh);
                glm::mat4 projection_matrix(float fov, float aspect, float znear, float zfar);
                
	
		
};

#endif
