#pragma once
#include "common.h"
#include "camera.h"
#include <string>
#include <SDL.h>


class Object
{
public:
    Object(Point pos, const std::string& mesh_path);

    void render(uint32_t* texbuf, float* zbuf, const Camera& camera, float rotx[3][3], float roty[3][3]);

private:
    SDL_FPoint center_and_scale(SDL_FPoint p);
    Point matrix_multiply(float mat[3][3], Point p);

private:
    Point m_pos;
    Mesh m_mesh;
};

