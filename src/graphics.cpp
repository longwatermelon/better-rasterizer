#include "graphics.h"
#include <vector>
#include <iostream>


void graphics::draw_wireframe_triangle(SDL_Renderer* rend, SDL_FPoint p1, SDL_FPoint p2, SDL_FPoint p3)
{
    SDL_RenderDrawLine(rend, p1.x, p1.y, p2.x, p2.y);
    SDL_RenderDrawLine(rend, p2.x, p2.y, p3.x, p3.y);
    SDL_RenderDrawLine(rend, p3.x, p3.y, p1.x, p1.y);
}


void graphics::draw_filled_triangle(SDL_Renderer* rend, SDL_FPoint p1, SDL_FPoint p2, SDL_FPoint p3)
{
    if (p1.y > p2.y)
        std::swap(p1, p2);

    if (p1.y > p3.y)
        std::swap(p1, p3);

    if (p2.y > p3.y)
        std::swap(p2, p3);
    
    auto interpolate = [](SDL_FPoint p1, SDL_FPoint p2, std::vector<float>& values) {
        if ((int)p1.y < (int)p2.y)
        {
            float slope = (p2.x - p1.x) / (p2.y - p1.y);
            
            for (float y = p1.y; y < p2.y; ++y)
            {
                if (y < 0)
                    continue;

                if (y > 800)
                    break;

                float x = p1.x + (slope * (y - p1.y));
                x = std::min(std::max(0.f, x), 800.f);

                values[(int)y] = x;
            }
        }
    };

    std::vector<float> xl(800);
    std::vector<float> xr(800);

    interpolate(p1, p2, xl);
    interpolate(p2, p3, xl);
    interpolate(p1, p3, xr);

    for (int y = (int)p1.y; y < (int)p3.y; ++y)
    {
        if (y < 0)
            continue;

        if (y > 800)
            break;

        int min = std::min(xl[y], xr[y]);
        int max = std::max(xl[y], xr[y]);
        SDL_RenderDrawLine(rend, min, y, max, y);
    }
}

