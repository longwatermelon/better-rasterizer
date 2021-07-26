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

#if 0
    auto interpolate = [](float y1, float x1, float y2, float x2) {
        if (y1 == y2)
            return std::vector<float>{ x2 };

        std::vector<float> values;
        float slope = (x2 - x1) / (y2 - y1);
        float x = x1;

        for (int i = y1; i < y2; ++i)
        {
            values.emplace_back(x);
            x += slope;
        }

        return values;
    };

    std::vector<float> x01 = interpolate(p1.y, p1.x, p2.y, p2.x);
    std::vector<float> x12 = interpolate(p2.y, p2.x, p3.y, p3.x);
    std::vector<float> x02 = interpolate(p1.y, p1.x, p3.y, p3.x);

    if (x01.empty() || x12.empty() || x02.empty())
        return;

    x01.insert(x01.end(), x12.begin(), x12.end());

    int middle = (int)(x01.size() / 2);

    std::vector<float>* x_left;
    std::vector<float>* x_right;

    if (x02[middle] < x01[middle])
    {
        x_left = &x02;
        x_right = &x01;
    }
    else
    {
        x_left = &x01;
        x_right = &x02;
    }

    for (int y = p1.y; y <= p3.y; ++y)
    {
        SDL_RenderDrawLine(rend, (*x_left)[(int)(y - p1.y)], y, (*x_right)[(int)(y - p1.y)], y);
    }
#endif
}

