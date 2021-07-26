#pragma once
#include <SDL.h>


namespace graphics
{
    void draw_wireframe_triangle(SDL_Renderer* rend, SDL_FPoint p1, SDL_FPoint p2, SDL_FPoint p3);
    void draw_filled_triangle(uint32_t* texbuf, SDL_FPoint p1, SDL_FPoint p2, SDL_FPoint p3);

    void texbuf_reset(uint32_t* texbuf);
    void update_texture(SDL_Texture* tex, uint32_t* texbuf);
}

