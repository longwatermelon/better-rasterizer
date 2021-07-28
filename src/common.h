#pragma once
#include <array>
#include <vector>
#include <random>
#include <SDL.h>


inline int randint(int min, int max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution dist(min, max);

    return dist(mt);
}


struct Point
{
    float x, y, z;
};

struct Triangle
{
    std::array<int, 3> indexes;
    SDL_Color color{ (Uint8)randint(200, 255), (Uint8)randint(200, 255), (Uint8)randint(200, 255) };
};

struct Mesh
{
    std::vector<Point> points;
    std::vector<Triangle> tris;
};

