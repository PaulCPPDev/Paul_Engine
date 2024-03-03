#ifndef PAULENGINE_CORE_APP_H
#define PAULENGINE_CORE_APP_H


#include "Renderer/IRenderer.h"
#include "Renderer/Renderer.h"

#include <memory>

#include <SDL2/SDL.h>

class App {
  private:
    std::unique_ptr<renderer::IRenderer> renderer;

  public:
    App()
    : renderer( std::make_unique<renderer::Renderer>() ){
    };
    ~App() {
    	//delete renderer;
    };

    void set_up();
    bool is_running();
    void process_input();
    void update();
    void render();
    void destroy();
};

#endif
