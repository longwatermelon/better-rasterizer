#include "object.h"
#include "file.h"
#include "graphics.h"


Object::Object(Point pos, const std::string& mesh_path)
    : m_pos(pos), m_mesh(file::read_facet(mesh_path)) {}


void Object::render(SDL_Renderer* rend)
{
    std::vector<SDL_FPoint> projected_points(m_mesh.points.size());
    std::vector<Point> real_points(m_mesh.points.size());

    for (int i = 0; i < m_mesh.points.size(); ++i)
    {
        Point real = m_mesh.points[i];
        SDL_FPoint projected;

        real.x += m_pos.x;
        real.y += m_pos.y;
        real.z += m_pos.z;

        real_points[i] = real;

        if (real.z != 0.f)
        {
            projected.x = real.x / real.z;
            projected.y = real.y / real.z;
        }

        projected_points[i] = center_and_scale(projected);
    }

    for (auto& tri : m_mesh.tris)
    {
        if (real_points[tri.indexes[0]].z >= 1.f && real_points[tri.indexes[1]].z >= 1.f && real_points[tri.indexes[2]].z >= 1.f)
        {
            graphics::draw_wireframe_triangle(rend, projected_points[tri.indexes[0]], projected_points[tri.indexes[1]], projected_points[tri.indexes[2]]);
        }
    }
}


SDL_FPoint Object::center_and_scale(SDL_FPoint p)
{
    p.x += 1.f;
    p.y += 1.f;

    // 800 is screen width and height
    p.x *= 0.5f * 800.f;
    p.y *= 0.5f * 800.f;

    return p;
}

