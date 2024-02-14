/**
 * @file App.cpp
 * @author Paul Gregor
 * @brief the App that uses the provided interface from the Renderer Component
 * @version 0.1
 * @date 14.02.2024
 * @copyright University of Bern Applied Sciences
 */

#include "App.h"


void App::set_up(){
	graphics.set_up();
}

bool App::is_running(){
	return graphics.is_running();
}


void App::process_input(){
	graphics.process_input();
}


void App::update(){
	graphics.update();
}

void App::render(){
	graphics.render();
}

void App::destroy(){
	// destroy what needs to be destroyed
	graphics.destroy();
}
