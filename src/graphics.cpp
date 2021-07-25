#include "graphics.h"


void graphics::draw_wireframe_triangle(SDL_Renderer* rend, SDL_FPoint p1, SDL_FPoint p2, SDL_FPoint p3)
{
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

    SDL_RenderDrawLine(rend, p1.x, p1.y, p2.x, p2.y);
    SDL_RenderDrawLine(rend, p2.x, p2.y, p3.x, p3.y);
    SDL_RenderDrawLine(rend, p3.x, p3.y, p1.x, p1.y);
}

