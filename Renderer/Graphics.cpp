/**
 * @file Graphics.cpp
 * @author Paul Gregor
 * @brief the the Specific details of the Graphics are implemented in this class
 * @version 0.1
 * @date 14.02.2024
 * @copyright University of Bern Applied Sciences
 */

#include "Graphics.h"
#include <iostream>

#define FOV_SCALING_FACTOR 128


void Graphics::init(){
	
	// Initialize the display object
	this->display = new Display();
		
	// Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		// Log the error code
		std::cout << "Error Initializing SDL" << std::endl;
		this->isRunning = false;
	}
	
	// Get the Full screen resolution of the current display(0)
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	this->display->window_width = display_mode.w;
	this->display->window_height = display_mode.h;

	
	display->window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->display->window_width, this->display->window_height, SDL_WINDOW_BORDERLESS );
	if(display->window == NULL){
		// Log the error code
		std::cout << "Eror Creating SDL Window" << std::endl;
		this->isRunning = false;
	}
	
	display->renderer = SDL_CreateRenderer(display->window, -1, 0);
	if (display->renderer == NULL){
		// Log the error code
		std::cout << "Error Creating SDL Renderer" << std::endl;
		this->isRunning = false;
	}
	
	// Make the window true full screen 
	if(SDL_SetWindowFullscreen(this->display->window, SDL_WINDOW_FULLSCREEN) != 0){
		// Log the error code
		// std::cout << "Error making the window full screen" << std::endl; // This doesn't work
	}
	
	//color buffer
	this->display->color_buffer = new uint32_t[this->display->window_width * this->display->window_height];
	
	// Create a color buffer texture to access every single pixel on the screen
	this->display->color_buffer_texture = SDL_CreateTexture(display->renderer, 
				SDL_PIXELFORMAT_RGBA8888, 
				SDL_TEXTUREACCESS_STREAMING,
				this->display->window_width,
				this->display->window_height);
}

void Graphics::set_up(){
	this->init();
	
	// initialize camera
	Camera* camera = new Camera();
	camera->position = glm::vec3(0,0, -5);
	camera->direction = glm::vec3(0, 0, 1);
	
	// load cube mesh data
	// load .obj files
	
	
	// initialize cube values
	Mesh* mesh = new Mesh();
	mesh->load_cube_mesh_data();
	meshes.push_back(*mesh);
	
	// new code
	meshes[0].rotate  = glm::vec3(0,0,0);
		
}

bool Graphics::is_running(){
	return isRunning;
}


void Graphics::process_input(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
				this->isRunning = false;
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
					this->isRunning = false;
				break;
		}
	}
}


void Graphics::update(){
	triangles_to_render.clear();
	// update the rotation of the mesh
	meshes[0].rotate  += glm::vec3(0, 0.1, 0);
	//loop all meshes
	for(auto& mesh : meshes)
		pipeline(mesh);
	
}

void Graphics::render(){
	SDL_SetRenderDrawColor(display->renderer, 255, 0, 0, 255);
	SDL_RenderClear(display->renderer);
	display->clear_color_buffer(0x141414d9);
	
	
	//display->draw_filled_rect(200,200, 400, 200, 0xFF000000);
	//display->draw_line(200,700, 800, 200, 0xFF000000);
	//display->draw_unfilled_triangle(200,700, 500, 200, 800, 500, 0xFF000000);
	//display->draw_filled_triangle(200,700, 500, 200, 800, 500, 0xFF000000);
	
	// loop all triangles to render
	for (auto triangle : triangles_to_render){
		// draw Triangle
		display->draw_unfilled_triangle(triangle.vertices[0].coord.x, triangle.vertices[0].coord.y, 
						triangle.vertices[1].coord.x, triangle.vertices[1].coord.y, 
						triangle.vertices[2].coord.x, triangle.vertices[2].coord.y, 
						0xFF000000);
	}
	
	//render the color buffer
	SDL_UpdateTexture(display->color_buffer_texture, NULL, display->color_buffer, (this->display->window_width * sizeof(uint32_t)) );
	SDL_RenderCopy(this->display->renderer, this->display->color_buffer_texture, NULL, NULL);
	SDL_RenderPresent(this->display->renderer);
	
	
	
}

void Graphics::destroy(){
	delete this->display->color_buffer;
	display->destroy();
	delete this->display;
	SDL_Quit();
}




// Graphics pipeline applied to every mesh
void Graphics::pipeline(Mesh& mesh){
	// Create world Matrix Scale Rotate Translate
	// Create View/Camera Matrix
	// Loop all triangles in Mesh
	for(auto triangle: mesh.triangles){
		// array to store the transformed triangle vertices
		std::array<glm::vec3, 3> transformed_vertices;
		// loop all 3 vertices in a triangle
		for(int v = 0; v<3 ; v++){
			glm::vec3 transformed_vertex = triangle.vertices[v].coord;
			// apply the world Matrix
				// Rotate
				// Create a rotation matrix around the y-axis
    				glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(mesh.rotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
				// Apply the rotation to the point
    				glm::vec3 rotatedPoint = glm::vec3(rotationMatrix * glm::vec4(transformed_vertex, 1.0f));
				//transformed_vertex += mesh.rotate;
			// apply the view Matrix
			  
			// push to the transformed vertices
			transformed_vertices[v] = rotatedPoint; //transformed_vertex;
			}
		
		// Back face cull
		
		
		
		// Clip Polygons
		// Loop all Clipped Triangles
			// lop 3 vertices
				//projectionMatrix
		
		
		// create the triangle to be rendered
		Triangle triangle_to_render;
		for (int v = 0; v<3 ; v++){
			triangle_to_render.vertices[v].index = triangle.vertices[v].index;
			triangle_to_render.vertices[v].coord = transformed_vertices[v];
			
			// Perspective divide
			
			// Scale into the view (zoom into the objects)
                	triangle_to_render.vertices[v].coord.x *= FOV_SCALING_FACTOR;
			triangle_to_render.vertices[v].coord.y *= FOV_SCALING_FACTOR;
			// Translate to middle of the screen
			triangle_to_render.vertices[v].coord.x += (display->window_width / 2.0);
			triangle_to_render.vertices[v].coord.y += (display->window_height / 2.0);
		}
		
		
		
		// add to triangles to render;
		triangles_to_render.push_back(triangle_to_render);
	}
}


