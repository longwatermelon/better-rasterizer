#include "graphics.h"
#include <vector>
#include <iostream>


void graphics::draw_wireframe_triangle(SDL_Renderer* rend, SDL_FPoint p1, SDL_FPoint p2, SDL_FPoint p3)
{
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

    SDL_RenderDrawLine(rend, p1.x, p1.y, p2.x, p2.y);
    SDL_RenderDrawLine(rend, p2.x, p2.y, p3.x, p3.y);
    SDL_RenderDrawLine(rend, p3.x, p3.y, p1.x, p1.y);
}


void graphics::draw_filled_triangle(SDL_Renderer* rend, SDL_FPoint p1, SDL_FPoint p2, SDL_FPoint p3)
{
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

    if (p1.y > p2.y)
        std::swap(p1, p2);

    if (p1.y > p3.y)
        std::swap(p1, p3);

    if (p2.y > p3.y)
        std::swap(p2, p3);

    auto interpolate = [](float y1, float x1, float y2, float x2) {
        if (y1 == y2)
            return std::vector<float>{ x1 };

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

    if (x01.empty())
        return;

    x01.pop_back();
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
}

