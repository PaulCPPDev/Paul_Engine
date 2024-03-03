#ifndef PAULENGINE_RENDERER_DISPLAY_H_
#define PAULENGINE_RENDERER_DISPLAY_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//////////////////////////////////////////////////////
///////// Provided Interface /////////////////////////
/////////////////////////////////////////////////////

namespace display {
class Display {
  public:
    int window_width = 1920;
    int window_height = 1080;
   		
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    uint32_t* color_buffer = NULL;
    float* z_buffer = NULL;
    SDL_Texture* color_buffer_texture = NULL;
		
		
  public:
    Display() = default;
    ~Display() = default;
    void destroy();
                
    void clear_color_buffer(uint32_t color);
    void clear_z_buffer();
    void draw_pixel(int pos_x, int pos_y, uint32_t color);
    void draw_triangle_pixel(int pos_x, int pos_y, uint32_t color);
    void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
                
    void draw_filled_rect(int pos_x, int pos_y, int width, int height, uint32_t color);
                
                
    void draw_circle(int x, int y, int radius, float angle, uint32_t color); // does not work
    void draw_filled_circle(int x, int y, int radius, uint32_t color); // does not work
                
    void draw_unfilled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
    void draw_filled_triangle(int x0, int y0, int z0, int x1, int y1, int z1, int x2, int y2, int z2, uint32_t color); //TODO
                            
  private:
    void sortVerticesByY(int& x0, int& y0,  int& z0, int& x1, int& y1,  int& z1, int& x2, int& y2, int& z2);  //TODO
    void draw_flat_bottom_triangle(int& x0, int& y0, int& x1, int& y1, int& x2, int& y2, uint32_t color);  
    void draw_flat_top_triangle(int& x0, int& y0, int& x1, int& y1, int& x2, int& y2, uint32_t color);  
		
};

}

#endif
