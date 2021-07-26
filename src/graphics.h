#pragma once
#include "common.h"
#include <SDL.h>


namespace graphics
{
    void draw_wireframe_triangle(SDL_Renderer* rend, SDL_FPoint p1, SDL_FPoint p2, SDL_FPoint p3);
    // x and y values of points should be projected values, z should be real z value
    void draw_filled_triangle(uint32_t* texbuf, float* zbuf, Point p1, Point p2, Point p3, SDL_Color col);

    void texbuf_reset(uint32_t* texbuf, float* zbuf);
    void update_texture(SDL_Texture* tex, uint32_t* texbuf);
}

