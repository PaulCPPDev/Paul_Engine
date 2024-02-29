/**
 * @file Graphics.cpp
 * @author Paul Gregor
 * @brief the the Specific details of the Graphics are implemented in this class
 * @version 0.1
 * @date 14.02.2024
 * @copyright University of Bern Applied Sciences
 */

#include "Graphics.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#define FOV_SCALING_FACTOR 512


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
	
	// Projection Matrix information
	// Initialize the perspective projection matrix
    	float aspect_y = (float)display->window_height / (float)display->window_width;
    	float aspect_x = (float)display->window_width / (float)display->window_height;
    	float fov_y = 3.141592 / 3.0; // the same as 180/3, or 60deg
    	float fov_x = atan(tan(fov_y / 2) * aspect_x) * 2;
    	float znear = 1.0;
    	float zfar = 20.0;
    	//proj_matrix = this->projection_matrix(fov_y, aspect_y, znear, zfar);
    	proj_matrix = glm::perspective(fov_y, aspect_x, znear, zfar);
    	

    	// Initialize frustum planes with a point and a normal
    	// init_frustum_planes(fov_x, fov_y, znear, zfar);
    	
    	
    	// Global ilumination
    	light = new Light(glm::vec3(0,0,1));
    	
	// initialize camera
	camera = new Camera();
	
	
	// load cube mesh data
	// load .obj files
	Mesh* mesh = new Mesh();
	
	//mesh->load_cube_mesh_data();
	mesh->load_obj_file("./Dev/crab.obj");
	meshes.push_back(*mesh);
	
	// new code
	meshes[0].scale = glm::vec3(1,1,1);
	meshes[0].rotate  = glm::vec3(0,0,0);
	meshes[0].translate = glm::vec3(0,0,5);
	
	
		
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
				
				
				// BEGIN CAMERA MOVEMENT	
				if (event.key.keysym.sym == SDLK_w) {
				    this->camera->orientation.x -= (0.5);
				    break;
				}
				if (event.key.keysym.sym == SDLK_s) {
				    this->camera->orientation.x += (0.5);
				    break;
				}
				if (event.key.keysym.sym == SDLK_d) {
				    this->camera->orientation.y -= (0.5);
				    break;
				}
				if (event.key.keysym.sym == SDLK_a) {
				    this->camera->orientation.y += (0.5);
				    break;
				}
				
				if (event.key.keysym.sym == SDLK_UP) {
					this->camera->velocity = (this->camera->direction * glm::vec3(0.5,0.5,0.5) );
					this->camera->position += this->camera->velocity;
				   	break;
				}
				if (event.key.keysym.sym == SDLK_DOWN) {
					this->camera->velocity = (this->camera->direction * glm::vec3(0.5,0.5,0.5) );
					this->camera->position -= this->camera->velocity;
				   	break;
				}
				// END CAMERA MOVEMENT
                
				break;
		}
	}
}


void Graphics::update(){
	triangles_to_render.clear();
	// update the rotation of the mesh
	meshes[0].rotate  += glm::vec3(0.2, 0.2, 0);
	//loop all meshes
	for(auto& mesh : meshes)
		pipeline(mesh);
	
}

void Graphics::render(){
	SDL_SetRenderDrawColor(display->renderer, 255, 0, 0, 255);
	SDL_RenderClear(display->renderer);
	display->clear_color_buffer(0x141414d9);
	
	// loop all triangles to render
	for (auto triangle : triangles_to_render){
		// draw Filled Triangle
		display->draw_filled_triangle(triangle.vertices[0].x, triangle.vertices[0].y, 
						triangle.vertices[1].x, triangle.vertices[1].y, 
						triangle.vertices[2].x, triangle.vertices[2].y,
						light->apply_light_intensity(0xFFFFFFFF, triangle.color));
		// draw Triangle
		display->draw_unfilled_triangle(triangle.vertices[0].x, triangle.vertices[0].y, 
						triangle.vertices[1].x, triangle.vertices[1].y, 
						triangle.vertices[2].x, triangle.vertices[2].y, 
						0x79949ced);
	}
	
	//render the color buffer
	SDL_UpdateTexture(display->color_buffer_texture, NULL, display->color_buffer, (this->display->window_width * sizeof(uint32_t)) );
	SDL_RenderCopy(this->display->renderer, this->display->color_buffer_texture, NULL, NULL);
	SDL_RenderPresent(this->display->renderer);
	
	
	
}

void Graphics::destroy(){
	delete this->camera;
	delete this->display->color_buffer;
	display->destroy();
	delete this->display;
	SDL_Quit();
}




// Graphics pipeline applied to every mesh
void Graphics::pipeline(Mesh& mesh){
	// Create world Matrix Scale Rotate Translate
		// scaling matrix
		glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(mesh.scale.x, mesh.scale.y, mesh.scale.z) );
		
		// Rotation matrix
		// X - axis Rotation
		glm::mat4 rotation_x = glm::rotate(glm::mat4(1.0f), glm::radians(mesh.rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
		// y-axis Rotation
    		glm::mat4 rotation_y = glm::rotate(glm::mat4(1.0f), glm::radians(mesh.rotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
    		// z-axis Rotation 
    		glm::mat4 rotation_z = glm::rotate(glm::mat4(1.0f), glm::radians(mesh.rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));	
    		// Make rotation Matrix
    		glm::mat4 rotation_matrix = rotation_z * rotation_y * rotation_x;
    		
    		// translation matrix
    		glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(mesh.translate.x, mesh.translate.y, mesh.translate.z) );
    	// World Matrix
    	glm::mat4 world_matrix = translation_matrix * rotation_matrix * scaling_matrix;
    			
	// Create View/Camera Matrix (look at camera model)
	// Create an FPS based Target (Target changes according to the FPS Movement)
	glm::vec3 target = camera->get_FPS_target(); //mesh.translate;
	glm::vec3 up_direction(0,1,0);
	// Make the camrera look at the target
	glm::mat4 view_matrix = camera->look_at(camera->position,target, up_direction);
	
	// Loop all triangles in Mesh
	for(auto triangle: mesh.triangles){
		// array to store the transformed triangle vertices
		std::array<glm::vec3, 3> transformed_vertices;
		// loop all 3 vertices in a triangle
		for(int v = 0; v<3 ; v++){
		
			glm::vec3 transformed_vertex = triangle.vertices[v];
			// apply the world Matrix
    			glm::vec3 world_point = glm::vec3(world_matrix * glm::vec4(transformed_vertex, 1.0f));
				
			// apply the view/camera Matrix
			glm::vec3 viewed_point = glm::vec3(view_matrix * glm::vec4(world_point, 1.0f));
			  
			// push to the transformed vertices
			transformed_vertices[v] = viewed_point; //transformed_vertex;
			}
		
		// TODO Back face cull
        	/*  1A   */
        	/*  / \  */
        	/*0C---2B */
        	
        	// Find the vectors (B-A) & (C-A)
        	glm::vec3 vec_ab = glm::normalize(transformed_vertices[2] - transformed_vertices[1]);
                glm::vec3 vec_ac = glm::normalize(transformed_vertices[0] - transformed_vertices[1]);
                
                // Normal vector N = (B -A) X (C -A)
                glm::vec3 normal = glm::normalize(glm::cross(vec_ab, vec_ac));
                
                // define the oringin of my space
                glm::vec3 origin(0,0,0);
                // Camera ray vector
                glm::vec3 camera_ray = - glm::normalize((transformed_vertices[1] - origin)) ;
		
		// find the dot product
		float dot_face_normal = glm::dot(normal, camera_ray);
		
		if(dot_face_normal < 0)
			continue;
		
		
		// TODO FLAT SHADING DOES NOT WORK
		 
		// Calculate the shade intensity based on how aliged is the normal with the flipped light direction ray
            	float light_intensity_factor = -glm::dot(normal, light->direction);
            	

            	// Calculate the triangle color based on the light angle
            	triangle.color = light_intensity_factor;// light->apply_light_intensity(0xFFFFFFFF, 1);
            	
		
		
		// Clip Polygons
		// Loop all Clipped Triangles
			// lop 3 vertices
				//projectionMatrix
		
		
		// create the triangle to be rendered
		Triangle triangle_to_render;
		for (int v = 0; v<3 ; v++){
		
			// Get the color
			triangle_to_render.color = triangle.color;
			//Projection Matrix
			triangle_to_render.vertices[v] = glm::vec3(proj_matrix * glm::vec4(transformed_vertices[v], 1.0f));
			// triangle_to_render.vertices[v] = transformed_vertices[v];
			
			// Perspective divide
			if (triangle_to_render.vertices[v].z != 0){
				triangle_to_render.vertices[v].x /= triangle_to_render.vertices[v].z;  
				triangle_to_render.vertices[v].y /= triangle_to_render.vertices[v].z;  
			}
			
			// Flip the coordinates vertically
			//triangle_to_render.vertices[v].y *= -1;
			
			// Scale into the view (zoom into the objects)
                	triangle_to_render.vertices[v].x *= (display->window_width / 2.0);
			triangle_to_render.vertices[v].y *= (display->window_height / 2.0);
			// Translate to middle of the screen
			triangle_to_render.vertices[v].x += (display->window_width / 2.0);
			triangle_to_render.vertices[v].y += (display->window_height / 2.0);
		}
		
		
		
		// add to triangles to render;
		triangles_to_render.push_back(triangle_to_render);
	}
}



glm::mat4  Graphics::projection_matrix(float fov, float aspect, float znear, float zfar){
	// | (h/w)*1/tan(fov/2)             0              0                 0 |
    	// |                  0  1/tan(fov/2)              0                 0 |
   	// |                  0             0     zf/(zf-zn)  (-zf*zn)/(zf-zn) |
    	// |                  0             0              1                 0 |
    	glm::mat4 projection_matrix(0.0f);
   	projection_matrix[0][0] = aspect * (1 / tan(fov / 2));
    	projection_matrix[1][1] = 1 / tan(fov / 2);
    	projection_matrix[2][2] = zfar / (zfar - znear);
    	projection_matrix[2][3] = (-zfar * znear) / (zfar - znear);
    	projection_matrix[3][2] = 1.0;
    return projection_matrix;
}




