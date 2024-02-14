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

	public:
		Graphics() = default;
		~Graphics() = default;

		void set_up();
		bool is_running();
                void process_input();
                void update();
                void render();
                void destroy();
};

#endif
