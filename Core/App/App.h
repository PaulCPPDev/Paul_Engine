#ifndef CORE_APP_APP_H_
#define CORE_APP_APP_H_



#include <SDL2/SDL.h>

#include <memory>

#include "Renderer/IRenderer.h"
#include "Renderer/Renderer.h"

class App {
    private:
      std::unique_ptr<renderer::IRenderer> renderer;

    public:
      App()
      : renderer(std::make_unique<renderer::Renderer>()) {
      }
      ~App() {
      // delete renderer;
      }

      void set_up();
      bool is_running();
      void process_input();
      void update();
      void render();
      void destroy();
};

#endif  // CORE_APP_APP_H_
