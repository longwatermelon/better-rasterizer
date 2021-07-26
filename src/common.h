#pragma once
#include <array>
#include <vector>
#include <random>


struct Point
{
    float x, y, z;
};

struct Triangle
{
    std::array<int, 3> indexes;
};

struct Mesh
{
    std::vector<Point> points;
    std::vector<Triangle> tris;
};

inline int randint(int min, int max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution dist(min, max);

    return dist(mt);
}

