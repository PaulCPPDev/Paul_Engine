/**
 * @file App.cpp
 * @author Paul Gregor
 * @brief the App that uses the provided interface from the Renderer Component
 * @version 0.1
 * @date 14.02.2024
 * @copyright University of Bern Applied Sciences
 */

#include "App.h"

#define FPS 60
#define TARGET_FRAME_TIME (1000/FPS)

void App::set_up() {
  renderer->set_up();
}

bool App::is_running() {
  return renderer->is_running();
}


void App::process_input() {
  renderer->process_input();
}


void App::update() {
  // fix the time step
  static int previous_frame_time;
  int time_to_wait = TARGET_FRAME_TIME - (SDL_GetTicks() - previous_frame_time);
  if (time_to_wait > 0 && time_to_wait < TARGET_FRAME_TIME)
    SDL_Delay(time_to_wait);
  int delta_time = (SDL_GetTicks()-previous_frame_time)/1000;
  previous_frame_time = SDL_GetTicks();
  // update the physics
}

void App::render() {
  // update the graphics
  renderer->update();
  renderer->render();
}

void App::destroy() {
  // destroy what needs to be destroyed
  renderer->destroy();
}
