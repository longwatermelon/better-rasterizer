#pragma once
#include "object.h"
#include "camera.h"
#include <SDL.h>


class Rasterizer
{
public:
    Rasterizer(const std::vector<Object>& objects);
    ~Rasterizer();

    void mainloop();
    void handle_events(SDL_Event& evt);

private:
    bool m_running{ true };

    SDL_Window* m_window{ 0 };
    SDL_Renderer* m_rend{ 0 };

    Camera m_camera;
    std::vector<Object> m_objects;

    SDL_Texture* m_screen_tex;
    uint32_t m_texbuf[800 * 800];
    float m_zbuf[800 * 800];
};

