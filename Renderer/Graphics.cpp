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
	// TODO
	
}

void Graphics::render(){
	SDL_SetRenderDrawColor(display->renderer, 255, 0, 0, 255);
	SDL_RenderClear(display->renderer);
	
	display->clear_color_buffer(0x141414d9);
	//display->draw_filled_rect(200,200, 400, 200, 0xFF000000);
	//display->draw_line(200,700, 800, 200, 0xFF000000);
	//display->draw_unfilled_triangle(200,700, 500, 200, 800, 500, 0xFF000000);
	display->draw_filled_triangle(200,700, 500, 200, 800, 500, 0xFF000000);
	
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


