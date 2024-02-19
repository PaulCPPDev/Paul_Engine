#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "Display.h"

//////////////////////////////////////////////////////
///////// Provided Interface /////////////////////////
/////////////////////////////////////////////////////

class Graphics {
	private:
		bool isRunning = true;

		Display* display = NULL;

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
};

#endif
