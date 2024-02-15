#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

//////////////////////////////////////////////////////
///////// Provided Interface /////////////////////////
/////////////////////////////////////////////////////

class Graphics {
	private:
		bool isRunning = true;
		int window_width = 800;
		int window_height = 600;
		
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;
		uint32_t* color_buffer = NULL;
		SDL_Texture* color_buffer_texture = NULL;

	public:
		Graphics() = default;
		~Graphics() = default;
		
		void init();
		void set_up();
		bool is_running();
                void process_input();
                void update();
                void render();
                void destroy();
                
                void clear_color_buffer(uint32_t color);
};

#endif
