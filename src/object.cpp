#include "object.h"
#include "file.h"
#include "graphics.h"


Object::Object(Point pos, const std::string& mesh_path)
    : m_pos(pos), m_mesh(file::read_facet(mesh_path)) {}


void Object::render(uint32_t* texbuf, float* zbuf, const Camera& camera, float rotx[3][3], float roty[3][3])
{
    std::vector<SDL_FPoint> projected_points(m_mesh.points.size());
    std::vector<Point> real_points(m_mesh.points.size());

    for (int i = 0; i < m_mesh.points.size(); ++i)
    {
        Point real = m_mesh.points[i];
        SDL_FPoint projected;

        real.x += m_pos.x - camera.x();
        real.y += m_pos.y - camera.y();
        real.z += m_pos.z - camera.z();

        real = matrix_multiply(roty, real);
        real = matrix_multiply(rotx, real);

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
            graphics::draw_filled_triangle(texbuf, zbuf,
                    { projected_points[tri.indexes[0]].x, projected_points[tri.indexes[0]].y, real_points[tri.indexes[0]].z },
                    { projected_points[tri.indexes[1]].x, projected_points[tri.indexes[1]].y, real_points[tri.indexes[1]].z },
                    { projected_points[tri.indexes[2]].x, projected_points[tri.indexes[2]].y, real_points[tri.indexes[2]].z }, tri.color);
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


Point Object::matrix_multiply(float mat[3][3], Point p)
{
    Point ret;

    ret.x = p.x * mat[0][0] + p.y * mat[1][0] + p.z * mat[2][0];
    ret.y = p.x * mat[0][1] + p.y * mat[1][1] + p.z * mat[2][1];
    ret.z = p.x * mat[0][2] + p.y * mat[1][2] + p.z * mat[2][2];

    return ret;
}

