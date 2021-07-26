#include "graphics.h"
#include "common.h"
#include <vector>
#include <iostream>
#include <SDL.h>


void graphics::draw_wireframe_triangle(SDL_Renderer* rend, SDL_FPoint p1, SDL_FPoint p2, SDL_FPoint p3)
{
    SDL_RenderDrawLine(rend, p1.x, p1.y, p2.x, p2.y);
    SDL_RenderDrawLine(rend, p2.x, p2.y, p3.x, p3.y);
    SDL_RenderDrawLine(rend, p3.x, p3.y, p1.x, p1.y);
}


void graphics::draw_filled_triangle(uint32_t* texbuf, float* zbuf, Point p1, Point p2, Point p3, SDL_Color col)
{
    if (p1.y > p2.y)
        std::swap(p1, p2);

    if (p1.y > p3.y)
        std::swap(p1, p3);

    if (p2.y > p3.y)
        std::swap(p2, p3);
    
    auto interpolate = [](Point p1, Point p2, std::vector<float>& xvalues, std::vector<float>& zvalues) {
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

                xvalues[(int)y] = x;
                zvalues[(int)y] = p1.z + (y - p1.y) * ((p2.z - p1.z) / (p2.y - p1.y));
            }
        }
    };

    std::vector<float> xl(800);
    std::vector<float> xr(800);
    std::vector<float> zl(800);
    std::vector<float> zr(800);

    interpolate(p1, p2, xl, zl);
    interpolate(p2, p3, xl, zl);
    interpolate(p1, p3, xr, zr);

    for (int y = (int)p1.y; y < (int)p3.y; ++y)
    {
        if (y < 0)
            continue;

        if (y > 800)
            break;

        int min = std::min(xl[y], xr[y]);
        int max = std::max(xl[y], xr[y]);

        for (int i = min; i < max; ++i)
        {
            if (i > 800)
                break;

            if (i < 0)
                continue;

            if (y * 800 + i >= 800 * 800)
                break;

            float iz = zl[y] + (i - xl[y]) * ((zr[y] - zl[y]) / (xr[y] - xl[y]));

            if (iz < zbuf[y * 800 + i])
            {
                texbuf[y * 800 + i] = 0x00000000 | col.r << 16 | col.g << 8 | col.b;
                zbuf[y * 800 + i] = iz;
            }
        }
    }
}


void graphics::texbuf_reset(uint32_t* texbuf, float* zbuf)
{
    for (int i = 0; i < 800 * 800; ++i)
    {
        texbuf[i] = 0x000000;
        zbuf[i] = 1e5;
    }
}


void graphics::update_texture(SDL_Texture* tex, uint32_t* texbuf)
{
    SDL_UpdateTexture(tex, 0, texbuf, 800 * sizeof(uint32_t));
}

