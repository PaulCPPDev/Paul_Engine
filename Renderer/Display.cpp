/**
 * @file Display.cpp
 * @author Paul Gregor
 * @brief holds information about the color buffer and how to manipulate every single pixel of the display
 * @version 0.1
 * @date 14.02.2024
 * @copyright University of Bern Applied Sciences
 */

#include "Display.h"
#include <algorithm>

/**
 * @brief function that changes the color of all pixels on the display
 * @param uint32_t color
 */
void Display::clear_color_buffer(uint32_t color){
	int size = window_width * window_height;
	for (int i= 0; i < size; i++){
		color_buffer[i] = color;
	}
}

/**
 * @brief function to draw/change the color of a pixel at position (pos_x, pos_y) of the display
 * @param[in] pos_x the x position of the pixel on the display.
 * @param[in] pos_y the y position of the pixel on the display.
 */
void Display::draw_pixel(int pos_x, int pos_y, uint32_t color){
	if(pos_x > 0 && pos_y > 0 && pos_x < window_width && pos_y < window_height)
		color_buffer[(pos_y * window_width) + pos_x] = color;
}


/**
 * @brief function to draw a line between 2 points on the display, 
 using the DDA (Digital Differential Analyser) line drawing algorithm.
 * @param[in] x0 the x position of the first point on the display.
 * @param[in] y0 the y position of the first point on the display.
 * @param[in] x1 the x position of the second point on the display.
 * @param[in] y1 the y position of the second point on the display.
 * @param[in] color the color.
 */
void Display::draw_line(int x0, int y0, int x1, int y1, uint32_t color){
	// DDA algorithm
	// Rise and run (dx and dy)
	int dx = (x1 - x0);
	int dy = (y1 - y0);
	
	// steps
	int steps = std::max(abs(dx), abs(dy));
	
	// x and y increments
	float x_increment = dx/ static_cast<float>(steps);
	float y_increment = dy/ static_cast<float>(steps);
	
	// set the starting points to x0, y0
	float curr_x = x0;
	float curr_y = y0;
	
	// loop steps times and draw pixels and increment x and y
	for(int i= 0; i<= steps; i++){
		draw_pixel(round(curr_x), round(curr_y), color);
		curr_x += x_increment;
		curr_y += y_increment;
	}
}

/**
 * @brief function to draw a rectangle on the display
 * @param[in] pos_x the x position of the top left of the rectangle on the display.
 * @param[in] pos_y the y position of the top left of the rectangle on the display.
 * @param[in] width the width of the rectangle.
 * @param[in] height the height of the rectangle.
 * @param[in] color the color.
 */
void Display::draw_filled_rect(int pos_x, int pos_y, int width, int height, uint32_t color){
	for(int i = 0; i< width; i++){
		for(int j = 0; j < height; j++){
			int current_x = pos_x + i;
			int current_y = pos_y + j;
			draw_pixel(current_x, current_y, color);
			}
	}
}


/**
 * @brief function to draw an unfilled circle on the display
 * @param[in] pos_x the x position of the center of the circle.
 * @param[in] pos_y the y position of the center of the circle.
 * @param[in] radius the radius of the circle.
 * @param[in] color the color.
 */
void Display::draw_circle(int x, int y, int radius, float angle, uint32_t color){
	circleColor(renderer, x, y, radius, color);
	lineColor(renderer, x, y, x + cos(angle) * radius, y + sin(angle) * radius, color);
}

/**
 * @brief function to draw a filled circle on the display
 * @param[in] pos_x the x position of the center of the circle.
 * @param[in] pos_y the y position of the center of the circle.
 * @param[in] radius the radius of the circle.
 * @param[in] color the color.
 */
void Display::draw_filled_circle(int x, int y, int radius, uint32_t color){
	filledCircleColor(renderer, x, y, radius, color);
}


/**
 * @brief function to draw an Unfilled triangle between 3 points on the display.
 * @param[in] x0 the x position of the first point on the display.
 * @param[in] y0 the y position of the first point on the display.
 * @param[in] x1 the x position of the second point on the display.
 * @param[in] y1 the y position of the second point on the display.
 * @param[in] x1 the x position of the second point on the display.
 * @param[in] y1 the y position of the second point on the display.
 * @param[in] color the color. 
 */
void Display::draw_unfilled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color){
	// P0 --> P1
	draw_line(x0, y0, x1, y1, color);
	// P1 --> P2
	draw_line(x1, y1, x2, y2, color);
	// P2 --> P0
	draw_line(x2, y2, x0, y0, color);
}


/**
 * @brief function to draw a filled triangle between 3 points on the display, 
 using FlatBottomFlatTop technique.
 * @param[in] x0 the x position of the first point on the display.
 * @param[in] y0 the y position of the first point on the display.
 * @param[in] x1 the x position of the second point on the display.
 * @param[in] y1 the y position of the second point on the display.
 * @param[in] x1 the x position of the second point on the display.
 * @param[in] y1 the y position of the second point on the display.
 * @param[in] color the color. 
 */
void Display::draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color){
	// Flat bottom Flat Top Technique
	// Sort the vertices by y
	Display::sortVerticesByY(x0, y0, x1, y1, x2, y2);
	// Divide the triangle into 2
	int x_mid = ((x2-x0)*(y1-y0)/ (float) (y2-y0)) + x0;
	int y_mid = y1;
	// Draw flat bottom triangle
	draw_flat_bottom_triangle(x0, y0, x1, y1, x_mid, y_mid, color);
	// Draw flat top triangle
	draw_flat_top_triangle(x_mid, y_mid, x1, y1, x2, y2, color);
}


void Display::destroy(){
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
}


// Function to sort the vertices of a triangle by y-coordinates
void Display::sortVerticesByY(int& x0, int& y0, int& x1, int& y1, int& x2, int& y2) {
    // Create arrays to hold the vertices
    int x[3] = {x0, x1, x2};
    int y[3] = {y0, y1, y2};

    // Sort the vertices based on y-coordinates
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2 - i; ++j) {
            if (y[j] > y[j + 1]) {
                std::swap(y[j], y[j + 1]);
                std::swap(x[j], x[j + 1]);
            }
        }
    }

    // Update the input values with the sorted values
    x0 = x[0];
    y0 = y[0];
    x1 = x[1];
    y1 = y[1];
    x2 = x[2];
    y2 = y[2];
}



void Display::draw_flat_bottom_triangle(int& x0, int& y0, int& x1, int& y1, int& x2, int& y2, uint32_t color){
	// start at the top
	float x_start = x0;
	float x_end = x0;
	// inverse slopes
	float inv_m1 = (x1-x0) / (float) (y1-y0);
	float inv_m2 = (x2-x0) / (float) (y2-y0);
	
	// loop from y0 to y1
	for(int y = (int) y0 ; y < (int) y2 ; y++){
		draw_line((int)x_start, y, (int) x_end,  y, color );
		x_start += inv_m1;
		x_end += inv_m2;
	}
}


void Display::draw_flat_top_triangle(int& x0, int& y0, int& x1, int& y1, int& x2, int& y2, uint32_t color){
	// start at the bottom
	float x_start = x2;
	float x_end = x2;
	// inverse slopes
	float inv_m1 = (x2-x0) / (float) (y2-y0);
	float inv_m2 = (x2-x1) / (float) (y2-y1);
	
	// loop from y2 to y1
	for(int y = (int) y2 ; y >= (int) y0 ; y--){
		draw_line((int)x_start, y, (int) x_end,  y, color );
		x_start -= inv_m1;
		x_end -= inv_m2;
	}
}


          

