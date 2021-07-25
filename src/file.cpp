#include "file.h"
#include <fstream>
#include <sstream>


Mesh file::read_facet(const std::string& path)
{
    std::ifstream ifs(path);
    std::stringstream ss;
    std::string buf;

    for (int i = 0; i < 5; ++i) std::getline(ifs, buf);
    
    int point_count = -1;
    std::stringstream(buf) >> point_count;

    std::vector<Point> points;
    for (int i = 0; i < point_count; ++i)
    {
        std::getline(ifs, buf);
        std::stringstream ss(buf);

        double tmp[3];
        for (int j = 0; j < 3; ++j)
        {
            ss >> tmp[j];
        }

        points.emplace_back(Point{ (float)tmp[0], (float)tmp[1], (float)tmp[2] });
    }

    for (int i = 0; i < 3; ++i) std::getline(ifs, buf);

    int triangle_count = -1;
    std::stringstream(buf) >> triangle_count;

    std::vector<Triangle> triangles;
    for (int i = 0; i < triangle_count; ++i)
    {
        std::getline(ifs, buf);
        std::stringstream ss(buf);

        Triangle tmp;
        for (int j = 0; j < 3; ++j)
        {
            ss >> tmp.indexes[j];
            tmp.indexes[j] -= 1;
        }

        triangles.emplace_back(tmp);
    }

    ifs.close();

    return { points, triangles };
}

