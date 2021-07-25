#pragma once
#include "common.h"
#include <string>
#include <SDL.h>


class Object
{
public:
    Object(Point pos, const std::string& mesh_path);

    void render(SDL_Renderer* rend);

private:
    SDL_FPoint center_and_scale(SDL_FPoint p);

private:
    Point m_pos;
    Mesh m_mesh;
};

