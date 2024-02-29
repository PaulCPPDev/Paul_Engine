/**
 * @file Light.cpp
 * @author Paul Gregor
 * @brief Implements Global ilumination
 * @version 0.1
 * @date 14.02.2024
 * @copyright University of Bern Applied Sciences
 */

#include "Light.h"
#include <SDL2/SDL.h>



/*
uint32_t Light::apply_light_intensity(uint32_t original_color, float factor) {
    if (factor < 0) factor = 0;
    if (factor > 1) factor = 1;

    uint32_t a = (original_color & 0xFF000000) * factor;
    uint32_t r = (original_color & 0x00FF0000) * factor;
    uint32_t g = (original_color & 0x0000FF00) * factor;
    uint32_t b = (original_color & 0x000000FF) ;

    uint32_t new_color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);

    return new_color;
}*/

uint32_t Light::apply_light_intensity(uint32_t original_color, float factor) {
    // Extract individual color components
    unsigned char alpha = (original_color >> 24) & 0xFF;
    unsigned char red = (original_color >> 16) & 0xFF;
    unsigned char green = (original_color >> 8) & 0xFF;
    unsigned char blue = original_color & 0xFF;

    // Adjust each color component based on the intensity factor
    red = static_cast<unsigned char>(red * factor);
    green = static_cast<unsigned char>(green * factor);
    blue = static_cast<unsigned char>(blue * factor);

    // Combine the components into a new color
    // return (alpha << 24) | (red << 16) | (green << 8) | blue;
    
    return SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), red, green, blue, alpha);
}
