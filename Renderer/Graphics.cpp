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

	// Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		// Log the error code
		std::cout << "Error Initializing SDL" << std::endl;
		this->isRunning = false;
	}
	
	// set the Window to full screen
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	this->window_width = display_mode.w;
	this->window_height = display_mode.h;
	if(SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN) != 0){
		// Log the error code
		// std::cout << "Error making the window full screen" << std::endl; // This doesn't work
	}
	
	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->window_width, this->window_height, SDL_WINDOW_BORDERLESS );
	if(window == NULL){
		// Log the error code
		std::cout << "Eror Creating SDL Window" << std::endl;
		this->isRunning = false;
	}
	
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL){
		// Log the error code
		std::cout << "Error Creating SDL Renderer" << std::endl;
		this->isRunning = false;
	}
	
	//color buffer
	this->color_buffer = new uint32_t[this->window_width * this-> window_height];
	
	// Create a color buffer texture to access every single pixel on the screen
	this->color_buffer_texture = SDL_CreateTexture(renderer, 
				SDL_PIXELFORMAT_RGBA32, 
				SDL_TEXTUREACCESS_STREAMING,
				this->window_width,
				this->window_height);
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
	// SDL_SetRenderDrawColor(this->renderer, 75, 75, 75, 255);
	// SDL_RenderClear(this->renderer);
	
	clear_color_buffer(0x22334455);
	SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, this->window_width);
	SDL_RenderCopy(this->renderer, this->color_buffer_texture, NULL, NULL);
	SDL_RenderPresent(this->renderer);
}

void Graphics::destroy(){
	delete this->color_buffer;
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}



void Graphics::clear_color_buffer(uint32_t color){
	int size = window_width * window_height;
	for (int i= 0; i < size; i++){
		color_buffer[i] = color;
	}
}
