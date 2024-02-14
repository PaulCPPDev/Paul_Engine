/**
 * @file main.cpp
 * @author Paul Holderbaum
 * @brief main module of the game engine where the program starts
 * @version 0.1
 * @date 13 Feb 2023
 * @Copyright University of Bern Applied Sciences
 */

#include <iostream>
#include "./App/App.h"

int main() {

	App app;

	app.set_up();

	while(app.is_running()){
		app.process_input();
		app.update();
		app.render();
	}
	app.destroy();
}
