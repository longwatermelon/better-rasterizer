#pragma once
#include <array>
#include <vector>


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

