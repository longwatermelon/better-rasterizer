#pragma once
#include "object.h"
#include <SDL.h>


class Rasterizer
{
public:
    Rasterizer(const std::vector<Object>& objects);
    ~Rasterizer();

    void mainloop();

private:
    bool m_running{ true };

    SDL_Window* m_window{ 0 };
    SDL_Renderer* m_rend{ 0 };

    std::vector<Object> m_objects;
};

