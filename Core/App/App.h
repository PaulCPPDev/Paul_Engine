#ifndef APP_H
#define APP_H

#include "../../Renderer/Graphics.h"
#include <SDL2/SDL.h>

class App {
	private:
		Graphics graphics;

	public:
		App() = default;
		~App() = default;

		void set_up();
		bool is_running();
                void process_input();
                void update();
                void render();
                void destroy();
};

#endif
