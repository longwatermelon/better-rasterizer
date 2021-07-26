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

    auto get_x_values = [](SDL_FPoint p1, SDL_FPoint p2) {
        if (p1.y == p2.y)
            return std::vector<float>{ p2.x };

        std::vector<float> values;
        float slope = (p2.x - p1.x) / (p2.y - p1.y);
        float x = p1.x;

        for (int i = p1.y; i <= p2.y; ++i)
        {
            values.emplace_back(x);
            x += slope;
        }

        return values;
    };

    std::vector<float> x12 = get_x_values(p1, p2);
    std::vector<float> x23 = get_x_values(p2, p3);
    std::vector<float> x13 = get_x_values(p1, p3);

    if (x12.empty() || x13.empty() || x23.empty())
        return;

    x12.pop_back();
    x12.insert(x12.end(), x23.begin(), x23.end());

    int middle = (int)(x12.size() / 2);
    std::vector<float> *left, *right;

    if (x12[middle] < x13[middle])
    {
        left = &x12;
        right = &x13;
    }
    else
    {
        left = &x13;
        right = &x12;
    }

    for (int y = p1.y; y <= p3.y; ++y)
    {
        SDL_RenderDrawLine(rend, (*left)[(int)(y - p1.y)], y, (*right)[(int)(y - p1.y)], y);
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

